#ifndef MAT_GRAPH
#define MAT_GRAPH

#include <map>

#include "graphBase.h"
#include "cacheBase.h"

using namespace std;

//assumes nodes numbered 0 to n-1, or things will go sideways
class MatrixGraph : public GraphData
{
	private:											
		map<int, int> lastNeighbor;		//key = original node number
										//value = index of last node given as neighbor
										//		(where index is vector index)
		
	public:		
		MatrixGraph();
		MatrixGraph(Cache *cachePtr);
	
		//read graph data from file, store in *consecutive* memory
		//memory needs to be consecutive or cache sim will not work!
		//also needs to call cache->allocatePages once graph data
		//is stored to init page divisions
		virtual bool loadFromFile(string filename);
		
		//given a node identifier, returns the next neighbor of this node
		virtual int getNextNeighbor(int id);
};

#endif
