#include "graphBase.h"
#include "cacheBase.h"

GraphData::GraphData() { }

GraphData::GraphData(Cache *cachePtr) : cache(cachePtr) { }	

//get item at [index] from 1D vector being used as 2D (dynamic) array
//different depending on storage schema being used
//ideally, all data accesses will be through this method, so you only
//have to trigger a cache lookup in one place
int GraphData::getItem(int index)
{
	cache->lookup(address(&graph[index]));

	return graph[index];
}
	
unsigned long GraphData::address(int *val)
{
	return reinterpret_cast<unsigned long>(val);
}
