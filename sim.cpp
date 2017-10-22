//library includes
#include <iostream>
#include <string>

#include "utils.cpp"

//base class includes
#include "travBase.h"
#include "graphBase.h"
#include "cacheBase.h"

//module includes
#include "ListGraph.h"

using namespace std;

int main()
{
	//simulator parameters
	int cacheSize;
	int pageSize;	
	int alg;		//traversal algorithm
	int graphData;	//graph data representation
	int policy;		//cache replacement policies (set)
	string filename;	//filename of file containing graph data
	int source;		//source node for traversal algorithms
	
	//module layer objects
	Traverse *trav;
	GraphData *graph;
	Cache *cache;
	
	int temp;

	//get cache parameters
	cout << "Enter cache size in KB: ";
	cin >> cacheSize;
	cacheSize *= 1024;		//convert to bytes
	
	cout << "Enter page size in KB: ";
	cin >> pageSize;
	pageSize *= 1024;
	
	//if page size does not evenly divide cache size, display a warning message
	if (cacheSize % pageSize != 0)
		cout << "Warning: page size does not evenly divide cache size" << endl;
		
	//pick one (and only one) traversal algorithm
	cout << endl << "Traversal Algorithms" << endl;
	cout << BFS << " Breadth-first search" << endl;
	cout << DFS << " Depth-first search" << endl;
	cout << "Select one traversal algorithm: ";
	cin >> alg;
	
	//pick one, or both, graph data representations
	cout << endl << "Graph Data Representations" << endl;
	cout << "1 Adjacency List" << endl;
	cout << "2 Adjacency Matrix" << endl;
	cout << "Select graph data option: ";
	cin >> graphData;
	
	//pick as many cache replacement policies as you want!
	cout << endl << "Cache Replacement Policies" << endl;
	cout << "1 LRU" << endl;
	cout << "2 FIFO" << endl;
	cout << "3 RR" << endl;
	cout << "Select cache replacement policy: ";
	cin >> policy;
	
	//enter filename containing graph data
	cout << endl << "Enter filename for test graph data: ";
	cin >> filename;
	
	//for now, let's set the source at 0
	source = 0;
	
	//declare and initialize the layers from the bottom up
	
	//commented out for now, because none of the inherited classes exist yet
	/*
	//cache layer
	if (policy == LRU)
		cache = &(new LRUcache(cacheSize, pageSize));
	else if (policy == FIFO)
		cache = &(new FIFOcache(cacheSize, pageSize));
	else if (policy == RR)
		cache = &(new RRcache(cacheSize, pageSize));
	*/
	
	//graph data layer
	if (graphData == LIST)
		graph = new ListGraph(cache);
	/*
	else if (graphData == MAT)
		graph = &(new MatrixGraph(cache));
	*/
	if (graph->loadFromFile(filename) == false)
		return 0;
	
	/*
	//traversal layer
	if (alg == BFS)
		trav = &(new BFStrav(graph));
	else if (alg == DFS)
		trav = &(new DFStrav(graph));
	*/
	
	//run the simulator!
	trav->runTraversal(source);
	cache->printResults();
}
