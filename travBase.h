#ifndef TRAV_BASE
#define TRAV_BASE

#include "graphBase.h"
using namespace std;

class Traverse
{
	protected:
		vector<bool> visited;	//mark nodes as visited (assume nodes numbered 0 to n-1)		
		GraphData *graph;		//pointer to graph layer
		int n;					//number of nodes
		
	public:
		Traverse() {};
		Traverse(GraphData *graphPtr);
		virtual void runTraversal(int source) = 0;	//pure virtual function
};

#endif
