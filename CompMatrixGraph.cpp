#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>

#include "utils.h"
#include "CompMatrixGraph.h"
#include "cacheBase.h"

CompMatrixGraph::CompMatrixGraph() { }
CompMatrixGraph::CompMatrixGraph(Cache *cachePtr) : GraphData(cachePtr) { }	

//helper method: given two node numbers a and b, find the vector and bit indexes
//to access the bit storing the edge from a->b
//returns a pair, where first entry is vector index, second is bit index
pair<int, int> CompMatrixGraph::getBitLocation(int a, int b)
{
	pair<int, int> res;
	
	//find index of correct integer to bit-twiddle
	res.first = (a*n + b) / bits_per_int;
	//get index of bit in that integer to twiddle
	res.second = (a*n + b) % bits_per_int;
	
	return res;
}
			
//read graph data from file, store in *consecutive* memory
//memory needs to be consecutive or cache sim will not work!
//also needs to call cache->allocatePages once graph data
//is stored to init page divisions

//input file assumptions: list of edges, one per line
//nodes numbered however they want, but we don't know how many yet
//edges are directed, so if you want it both ways you have to list
//both in the input file
bool CompMatrixGraph::loadFromFile(string filename)
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
	
	//compute actual size of vector needed, assuming one bit per matrix entry
	bits_per_int = sizeof(int) * 8;
	int mat_size = n * n / bits_per_int;
	
	//now, convert the data to a contiguous vector
	graph.resize(mat_size, 0);	//allocate space for a square 2D bit matrix, set to 0	
	//now, loop nodes and build matrix
	for (auto it = data.begin(); it != data.end(); it++)
	{
		//and loop edges
		for (auto tt = it->second.begin(); tt != it->second.end(); tt++)
		{
			//set the correct bit to 1 
			//it->first is row index, *tt is column index
			auto idx = getBitLocation(it->first, *tt);
			graph[idx.first] |= 1 << idx.second;
		}
	}	
	
	//DEBUG: print the vector to make sure it's right
	//(this prints decimal numbers, so have to check bits manually)
	if (DEBUG)
	{
		cerr << "vector: ";
		for (int i = 0; i < (int)graph.size(); i++)
		{
			if (i % n == 0) cout << endl;
			cerr << graph[i] << " ";
		}
		cerr << " (size " << graph.size() << ")" << endl;
	}
	
	//signal cache to allocate pages
	unsigned long start = address(&graph[0]);
	unsigned long end = start + sizeof(int) * graph.size();
	cache->allocatePages(start, end);
	
	return true;
}

//given a node identifier, returns the next neighbor of this node
//returns -1 if there are no more neighbors left
int CompMatrixGraph::getNextNeighbor(int id)
{
	int num;		//node number of neighbor to return
	
	//check if alreay at the end of this node's neighbors
	if (lastNeighbor.find(id) != lastNeighbor.end() && lastNeighbor[id] == -1)
		return -1;		//reached end previously, return -1	

	//find node number of next potential neighbor to return
	//have returned neighbor before, move to next
	if (lastNeighbor.find(id) != lastNeighbor.end())
		num = lastNeighbor[id] + 1;
	//have not returned a neighbor - set it up
	else
		num = 0;		//start with node 0 and move up from there!
	
	//loop along row of matrix until we find a real neighbor
	for (num = num; num < n; num++)
	{
		//find location of info in compressed matrix
		auto idx = getBitLocation(id, num);
		if (((getItem(idx.first) >> idx.second) & 1) == 1)
			break;		//found a neighbor, quit looping
	}
	//check if we ran off the end, reset idx if we did
	if (num == n)
		num = -1;
	
	//have a valid index (or sentinel), update the tracking data before returning
	lastNeighbor[id] = num;		//lastNeighbor for next time is the current one now

	//return node number that this '1' value belongs to (or -1 if no more)
	return num;
}
