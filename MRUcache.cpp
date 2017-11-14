#include <deque>
#include <algorithm>

#include "cacheBase.h"
#include "MRUcache.h"

using namespace std;

MRUcache::MRUcache(int cacheSize, int pageSize) : Cache(cacheSize, pageSize) { }

void MRUcache::updateMiss(int page) 
{
	//if the queue/table is full
	if ((int)MRUQueue.size() == limit) 
	{
		// Evict the tail of the queue (front of the vector)
		table.erase(MRUQueue.front());
		MRUQueue.pop_front();
	}
	
	// Insert new page at back of queue (front of the vector)
	MRUQueue.insert(MRUQueue.begin(), page);
	
	// Insert page into page table
	table.insert(page);
}

void MRUcache::updateHit(int page) 
{
	//remove from current position of queue
	MRUQueue.erase(find(MRUQueue.begin(), MRUQueue.end(), page));		
	MRUQueue.insert(MRUQueue.begin(), page);	//insert page at back of queue
}
