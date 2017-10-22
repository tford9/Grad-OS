#ifndef LIST_GRAPH
#define LIST_GRAPH

#include "graphBase.h"
#include "cacheBase.h"
#include <string>
#include <vector>
#include <map>
using namespace std;

class ListGraph : public GraphData
{
	private:			
		//get item at [row][col] from 1D vector being used as 2D (dynamic) array
		//different depending on storage schema being used
		//ideally, all data accesses will be through this method, so you only
		//have to trigger a cache lookup in one place
		int getItem(int row, int col);
		
	public:		
		//read graph data from file, store in *consecutive* memory
		//memory needs to be consecutive or cache sim will not work!
		//also needs to call cache->allocatePages once graph data
		//is stored to init page divisions
		void loadFromFile(string filename);
		
		//given a node identifier, returns the next neighbor of this node
		int getNextNeighbor(int id);
};

#endif
