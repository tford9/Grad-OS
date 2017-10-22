#include "MatrixGraph.h"
#include "cacheBase.h"
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>

MatrixGraph::MatrixGraph() { }
MatrixGraph::MatrixGraph(Cache *cachePtr) : GraphData(cachePtr) { }	
			
//read graph data from file, store in *consecutive* memory
//memory needs to be consecutive or cache sim will not work!
//also needs to call cache->allocatePages once graph data
//is stored to init page divisions

//input file assumptions: list of edges, one per line
//nodes numbered however they want, but we don't know how many yet
//edges are directed, so if you want it both ways you have to list
//both in the input file
bool MatrixGraph::loadFromFile(string filename)
{
	ifstream fin(filename);
	
	if (!fin)
	{
		cout << "Error opening input file. Quitting";
		return false; 
	}
	
	//some temporary variables
	map<int, set<int> > data;
	readGraphData(fin, data);		//read actual file data
	
	//extract node count
	n = data.size();
	
	//now, convert the data to a contiguous vector
	graph.resize(n * n, 0);	//allocate space for a square 2D matrix, set to all 0	
	//now, loop nodes and build matrix
	for (auto it = data.begin(); it != data.end(); it++)
	{
		//and loop edges
		for (auto tt = it->second.begin(); tt != it->second.end(); tt++)
		{
			graph[it->first*n + *tt] = 1;
		}
	}	
	
	//DEBUG: print the vector to make sure it's right
	/*
	cout << "vector: ";
	for (int i = 0; i < (int)graph.size(); i++)
	{
		if (i % n == 0) cout << endl;
		cout << graph[i] << " ";
	}
	cout << " (size " << graph.size() << ")" << endl;
	*/
	
	//signal cache to allocate pages
	unsigned long start = address(&graph[0]);
	unsigned long end = start + sizeof(int) * graph.size();
	cache->allocatePages(start, end);
	
	return true;
}

//given a node identifier, returns the next neighbor of this node
//returns -1 if there are no more neighbors left
int MatrixGraph::getNextNeighbor(int id)
{
	int idx;		//index of neighbor to return
	
	//check if alreay at the end of this node's neighbors
	if (lastNeighbor.find(id) != lastNeighbor.end() && lastNeighbor[id] == -1)
		return -1;		//reached end previously, return -1	

	//find index of next potential neighbor to return
	//have returned neighbor before, move to next
	if (lastNeighbor.find(id) != lastNeighbor.end())
		idx = lastNeighbor[id] + 1;
	//have not returned a neighbor - set it up
	else
		idx = id * n;		//index of first element in row for desired node
	
	//loop along row of matrix until we find a real neighbor
	for (idx = idx; idx < (id+1)*n; idx++)
	{
		if (getItem(idx) == 1)
			break;		//found a neighbor, quit looping
	}
	//check if we ran off the end, reset idx if we did
	if (idx == (id+1)*n)
		idx = -1;
	
	//have a valid index (or sentinel), update the tracking data before returning
	lastNeighbor[id] = idx;		//lastNeighbor for next time is the current one now

	//return node number that this '1' value belongs to
	if (idx != -1)
		return idx - (id * n);
	else
		return -1;
}
