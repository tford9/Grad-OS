//library includes
#include <iostream>
#include <string>

#include "utils.h"

//base class includes
#include "travBase.h"
#include "graphBase.h"
#include "cacheBase.h"

//module includes
#include "ListGraph.h"
#include "MatrixGraph.h"
#include "traversals.h"
#include "FIFOcache.h"
#include "RRcache.h"
#include "LRUcache.h"
#include "LFUcache.h"
#include "MRUcache.h"
#include "LIFOcache.h"

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

	//get cache parameters
	cerr << "Enter cache size in KB: ";
	cin >> cacheSize;
	cacheSize *= 1024;		//convert to bytes
	
	cerr << "Enter page size in KB: ";
	cin >> pageSize;
	pageSize *= 1024;
	
	//if page size does not evenly divide cache size, display a warning message
	if (cacheSize % pageSize != 0)
		cerr << "Warning: page size does not evenly divide cache size" << endl;
		
	//pick one (and only one) traversal algorithm
	cerr << endl << "Traversal Algorithms" << endl;
	cerr << BFS << " Breadth-first search" << endl;
	cerr << DFS << " Depth-first search" << endl;
	cerr << "Select one traversal algorithm: ";
	cin >> alg;
	
	//pick one, or both, graph data representations
	cerr << endl << "Graph Data Representations" << endl;
	cerr << "1 Adjacency List" << endl;
	cerr << "2 Adjacency Matrix" << endl;
	cerr << "Select graph data option: ";
	cin >> graphData;
	
	//pick as many cache replacement policies as you want!
	cerr << endl << "Cache Replacement Policies" << endl;
	cerr << "1 LRU" << endl;
	cerr << "2 FIFO" << endl;
	cerr << "3 LFU" << endl;
	cerr << "4 RR" << endl;
	cerr << "5 MRU" << endl;
	cerr << "6 LIFO" << endl;
	cerr << "Select cache replacement policy: ";
	cin >> policy;
	
	//enter filename containing graph data
	cerr << endl << "Enter filename for test graph data: ";
	cin >> filename;
	
	//for now, let's set the source at 0
	source = 0;
	
	//declare and initialize the layers from the bottom up
	
	//cache layer
	if (policy == LRU)
		cache = new LRUcache(cacheSize, pageSize);
	else if (policy == FIFO)							
		cache = new FIFOcache(cacheSize, pageSize);
	else if (policy == LFU)
		cache = new LFUcache(cacheSize, pageSize);
	else if (policy == MRU)
		cache = new MRUcache(cacheSize, pageSize);
	else if (policy == LIFO)
		cache = new LIFOcache(cacheSize, pageSize);
	else //if (policy == RR)		//use an else to prevent initialization warnings
		cache = new RRcache(cacheSize, pageSize);

	
	//graph data layer
	if (graphData == LIST)
		graph = new ListGraph(cache);
	else //if (graphData == MAT)	//use an else to prevent initialization warnings
		graph = new MatrixGraph(cache);
	if (graph->loadFromFile(filename) == false)
		return 0;	
	
	//traversal layer	
	if (alg == BFS)
		trav = new BFStrav(graph);
	else //if (alg == DFS)		//use an else to prevent initialization warnings
		trav = new DFStrav(graph);
	
	//run the simulator!
	trav->runTraversal(source);
	
	//print final results for parsing/analysis (pretty print)
	if (!DEBUG)
	{
		cout << cacheSize / 1024 << " " << pageSize / 1024 << " ";
		//cache layer
		if (policy == LRU) cout << "LRU";
		else if (policy == FIFO) cout << "FIFO";
		else if (policy == LFU) cout << "LFU";
		else if (policy == MRU) cout << "MRU";
		else if (policy == LIFO) cout << "LIFO";
		else cout << "RR";
		cout << " ";
		//graph data layer
		if (graphData == LIST) cout << "LIST";
		else cout << "MAT";
		cout << " ";
		//traversal layer
		if (alg == BFS) cout << "BFS";
		else cout << "DFS";
		cout << " " << filename << " ";
		//the cache will finish printing results
	}
	
	cache->printResults();
}