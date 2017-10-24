#include <vector>
#include <algorithm>

#include "cacheBase.h"
#include "LRUcache.h"

using namespace std;

LRUcache::LRUcache(int cacheSize, int pageSize) : Cache(cacheSize, pageSize) { }

void LRUcache::updateMiss(int page) 
{
	//if the queue/table is full
	if ((int)LRUQueue.size() == limit) 
	{
		// Evict the head of the queue (back of the vector)
		table.erase(LRUQueue.back());
		LRUQueue.pop_back();
	}
	
	// Insert new page at back of queue (front of the vector)
	LRUQueue.insert(LRUQueue.begin(), page);
	
	// Insert page into page table
	table.insert(page);
}

void LRUcache::updateHit(int page) 
{
	//remove from current position of queue
	LRUQueue.erase(find(LRUQueue.begin(), LRUQueue.end(), page));		
	LRUQueue.insert(LRUQueue.begin(), page);	//insert page at back of queue
}
