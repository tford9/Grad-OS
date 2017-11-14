#include <vector>

#include "cacheBase.h"
#include "LIFOcache.h"

using namespace std;

LIFOcache::LIFOcache(int cacheSize, int pageSize) : Cache(cacheSize, pageSize) { }

void LIFOcache::updateMiss(int page) 
{
	// If the queue/table is full
	if ((int)LIFOQueue.size() == limit) 
	{
		// Evict the head of the queue 
		table.erase(LIFOQueue.back());
		LIFOQueue.pop_back();
	}
	
	// Insert new page at back of queue
	LIFOQueue.insert(LIFOQueue.end(), page);
	
	// Insert page into page table
	table.insert(page);
}
