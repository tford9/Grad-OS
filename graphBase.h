#ifndef GRAPH_BASE
#define GRAPH_BASE

#include "cacheBase.h"
#include <string>
#include <vector>
#include <map>
using namespace std;

// we're going to make a couple of key assumptions here:
//
// 	1.  graph data is stored contiguously, so we can use the addresses to 
//		query the cache; this is accomplished using a 1D vector to store
//		whatever graph representation we're interested in
//	2.	nodes are numbered 0 to n-1, because that makes the array/matrix
//		indexing quick and easy
//
// obviously this isn't ideal, but it should give us a bit of simulated locality,
// without making the cache layer impossible to write

class GraphData
{
	protected:
		vector<int> graph;	//graph data stored as one big vector,
							//regardless of actual storage schema
	
		map<int, int> nextNeighbor;	//key - node number
											//value - INDEX of next neighbor (not node id!)			
		
		Cache *cache;		//pointer to cache layer
		
		//get item at [row][col] from 1D vector being used as 2D (dynamic) array
		//different depending on storage schema being used
		//ideally, all data accesses will be through this method, so you only
		//have to trigger a cache lookup in one place
		int getItem(int index);
		
		//convert address of item to unsigned long for query to cache
		unsigned long address(int *val);
		
	public:
		int n;		//number of nodes		
	
		GraphData();	
		GraphData(Cache *cachePtr);
		
		//read graph data from file, store in *consecutive* memory
		//memory needs to be consecutive or cache sim will not work!
		//also needs to call cache->allocatePages once graph data
		//is stored to init page divisions
		virtual bool loadFromFile(string filename) = 0;
		
		//given a node identifier, returns the next neighbor of this node
		virtual int getNextNeighbor(int id) = 0;
};

#endif
