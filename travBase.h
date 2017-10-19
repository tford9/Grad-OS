#ifndef TRAV_BASE
#define TRAV_BASE

#include "graphBase.h"
using namespace std;

class Traverse
{
	private:
		vector<bool> visited;	//mark nodes as visited (assume nodes numbered 0 to n-1)
		int n;					//number of nodes
		GraphData *graph;		//pointer to graph layer
		
	public:
		Traverse() {};
		Traverse(GraphData *graphPtr);
		virtual void runTraversal(int source) = 0;	//pure virtual function
};

#endif
