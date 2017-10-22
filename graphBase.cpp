#include "graphBase.h"
#include "cacheBase.h"

GraphData::GraphData() { }

GraphData::GraphData(Cache *cachePtr) : cache(cachePtr) { }	
	
unsigned long GraphData::address(int *val)
{
	return reinterpret_cast<unsigned long>(val);
}
