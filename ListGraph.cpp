#include "ListGraph.h"
#include "cacheBase.h"
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>

ListGraph::ListGraph() { }
ListGraph::ListGraph(Cache *cachePtr) : GraphData(cachePtr) { }	

//get item at [row][col] from 1D vector being used as 2D (dynamic) array
//different depending on storage schema being used
//ideally, all data accesses will be through this method, so you only
//have to trigger a cache lookup in one place
int ListGraph::getItem(int row, int col)
{
	return 0;
}
			
//read graph data from file, store in *consecutive* memory
//memory needs to be consecutive or cache sim will not work!
//also needs to call cache->allocatePages once graph data
//is stored to init page divisions

//input file assumptions: list of edges, one per line
//nodes numbered 0 to n-1, but we don't know n yet
//edges are directed, so if you want it both ways you have to list
//both in the input file
bool ListGraph::loadFromFile(string filename)
{
	ifstream fin(filename);
	
	if (!fin)
	{
		cout << "Error opening input file. Quitting";
		return false; 
	}
	
	//some temporary variables
	map<int, set<int> > data;
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
	
	//extract node count
	n = data.size();
	
	//now, convert the data to a contiguous vector
	graph.resize(n + edgeCount);	//allocate space
	int i = 0;
	for (auto it = data.begin(); it != data.end(); it++)
	{
		index[it->first] = i;		//store index for later
		graph[i] = it->first;
		i++;
		
		for (auto tt = it->second.begin(); tt != it->second.end(); tt++)
		{
			graph[i] = *tt;
			i++;
		}
	}
	
	/*
	//DEBUG: print the vector to make sure it's right
	cout << "vector: ";
	for (int i = 0; i < (int)graph.size(); i++)
		cout << graph[i] << " ";
	cout << endl << "indexes: ";
	for (auto it = index.begin(); it != index.end(); it++)
		cout << it->first << "->" << it->second << " ";
	cout << endl;
	*/
	
	return true;
}

//given a node identifier, returns the next neighbor of this node
int ListGraph::getNextNeighbor(int id)
{
	return 0;
}
