#ifndef LIST_GRAPH
#define LIST_GRAPH

#include <map>

#include "graphBase.h"
#include "cacheBase.h"

using namespace std;

class ListGraph : public GraphData
{
	private:			
		map<int, int> index;	//key = node number
								//value = index of that node in graph vector
								
		map<int, int> lastNeighbor;		//key = node number
										//value = index of last node given as neighbor
										//		(where index is vector index)
		
	public:		
		ListGraph();
		ListGraph(Cache *cachePtr);
	
		//read graph data from file, store in *consecutive* memory
		//memory needs to be consecutive or cache sim will not work!
		//also needs to call cache->allocatePages once graph data
		//is stored to init page divisions
		virtual bool loadFromFile(string filename);
		
		//given a node identifier, returns the next neighbor of this node
		virtual int getNextNeighbor(int id);
};

#endif
