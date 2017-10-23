#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "cacheBase.h"
#include "LRUcache.h"

using namespace std;

LRUcache::LRUcache(int cacheSize, int pageSize) : Cache(cacheSize, pageSize) 
{
}

void LRUcache::updateMiss(int page) 
{
		// If the queue/table is full
	if ((int)LRUQueue.size() == limit) 
	{
		// Evict the head of the queue 
		table.erase(LRUQueue.back());
		LRUQueue.pop_back();
	}
	
	// Insert new page at back of queue
	LRUQueue.insert(LRUQueue.begin(), page);
	
	// Insert page into page table
	table.insert(page);
}

void LRUcache::updateHit(int page) 
{
	LRUQueue
}
