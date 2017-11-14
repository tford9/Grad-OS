#ifndef COMP_MAT_GRAPH
#define COMP_MAT_GRAPH

#include <map>

#include "graphBase.h"
#include "cacheBase.h"

using namespace std;

//assumes nodes numbered 0 to n-1, or things will go sideways
class CompMatrixGraph : public GraphData
{
	private:				
		int bits_per_int;		//number of bits per int entry in graph vector
								
		map<int, int> lastNeighbor;		//key = original node number
										//value = node number of last node
										//		  given as neighbor (not and index!)
										
		pair<int, int> getBitLocation(int a, int b);
		
	public:		
		CompMatrixGraph();
		CompMatrixGraph(Cache *cachePtr);
	
		//read graph data from file, store in *consecutive* memory
		//memory needs to be consecutive or cache sim will not work!
		//also needs to call cache->allocatePages once graph data
		//is stored to init page divisions
		virtual bool loadFromFile(string filename);
		
		//given a node identifier, returns the next neighbor of this node
		virtual int getNextNeighbor(int id);
};

#endif
