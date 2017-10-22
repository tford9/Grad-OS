#include "ListGraph.h"
#include "cacheBase.h"
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>

ListGraph::ListGraph() { }
ListGraph::ListGraph(Cache *cachePtr) : GraphData(cachePtr) { }	
			
//read graph data from file, store in *consecutive* memory
//memory needs to be consecutive or cache sim will not work!
//also needs to call cache->allocatePages once graph data
//is stored to init page divisions

//input file assumptions: list of edges, one per line
//nodes numbered however they want, but we don't know how many yet
//edges are directed, so if you want it both ways you have to list
//both in the input file
bool ListGraph::loadFromFile(string filename)
{
	ifstream fin(filename);
	
	if (!fin)
	{
		cout << "Error opening input file. Quitting";
		return false; 
	}
	
	//some temporary variables
	map<int, set<int> > data;
	int a, b;
	int edgeCount = 0;
	
	//read edges and store in map, will convert to contiguous vector later
	while (fin >> a)
	{
		fin >> b;
		edgeCount++;
		
		//add edge to map
		data[a].insert(b);
	}
	
	//extract node count
	n = data.size();
	
	//now, convert the data to a contiguous vector
	graph.resize(n + edgeCount);	//allocate space
	int i = 0;
	for (auto it = data.begin(); it != data.end(); it++)
	{
		index[it->first] = i;		//store index for later
		graph[i] = it->first;
		i++;
		
		for (auto tt = it->second.begin(); tt != it->second.end(); tt++)
		{
			graph[i] = *tt;
			i++;
		}
	}	
	
	//DEBUG: print the vector to make sure it's right
	/*
	cout << "vector: ";
	for (int i = 0; i < (int)graph.size(); i++)
		cout << graph[i] << " ";
	cout << " (size " << graph.size() << ")" << endl << "indexes: ";
	for (auto it = index.begin(); it != index.end(); it++)
		cout << it->first << "->" << it->second << " ";
	cout << endl;
	*/
	
	//signal cache to allocate pages
	unsigned long start = address(&graph[0]);
	unsigned long end = start + sizeof(int) * graph.size();
	cache->allocatePages(start, end);
	
	return true;
}

//given a node identifier, returns the next neighbor of this node
//returns -1 if there are no more neighbors left
int ListGraph::getNextNeighbor(int id)
{
	int idx;		//index of neighbor to return
	
	//check if alreay at the end of this node's neighbors
	if (lastNeighbor.find(id) != lastNeighbor.end() && lastNeighbor[id] == -1)
		return -1;		//reached end previously, return -1	

	//find index of next neighbor to return
	//have returned neighbor before
	if (lastNeighbor.find(id) != lastNeighbor.end())
		idx = lastNeighbor[id] + 1;
	//have not returned a neighbor - set it up
	else
		idx = index[id] + 1;	
	
	//double-check that we're not overstepping this node's neighbor list
	if (idx > index.upper_bound(id)->second)
	{
		lastNeighbor[id] = -1;		//set value so we know for next time
		return -1;		//no more neighbors, return -1
	}
	
	//have a valid index, update the tracking data before returning
	lastNeighbor[id] = idx;		//lastNeighbor for next time is the current one now

	return getItem(idx);
}
