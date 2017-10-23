#include "cacheBase.h"
#include "FIFOcache.h"
#include <vector>
using namespace std;

FIFOcache::FIFOcache(int cacheSize, int pageSize) : Cache(cacheSize, pageSize) { }

void FIFOcache::updateMiss(int page) 
{
	// If the queue/table is full
	if ((int)FIFOQueue.size() == limit) 
	{
		// Evict the head of the queue 
		table.erase(FIFOQueue.back());
		FIFOQueue.pop_back();
	}
	
	// Insert new page at back of queue
	FIFOQueue.insert(FIFOQueue.begin(), page);
	
	// Insert page into page table
	table.insert(page);
}
