#include "graphBase.h"
#include "cacheBase.h"
#include <fstream>
#include <map>
#include <set>

GraphData::GraphData() { }

GraphData::GraphData(Cache *cachePtr) : cache(cachePtr) { }	

//get item at [index] from 1D vector being used as 2D (dynamic) array
//different depending on storage schema being used
//ideally, all data accesses will be through this method, so you only
//have to trigger a cache lookup in one place
int GraphData::getItem(int index)
{
	cache->lookup(address(&graph[index]));

	return graph[index];
}
	
unsigned long GraphData::address(int *val)
{
	return reinterpret_cast<unsigned long>(val);
}

//reads graph data from a file and stores into temporary map
//for later conversion to contiguous vector
//returns number of edges in graph
int GraphData::readGraphData(ifstream &fin, map<int, set<int> > &data)
{
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
	
	return edgeCount;
}
