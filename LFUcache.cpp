#include <vector>
#include <algorithm>

#include "cacheBase.h"
#include "LFUcache.h"

#define INF 65536

using namespace std;

LFUcache::LFUcache(int cacheSize, int pageSize) : Cache(cacheSize, pageSize) { }

void LFUcache::updateMiss(int page) 
{
	//if the queue/table is full
	if ((int)LFUQueue.size() == limit) 
	{
		// Evict the page with the lowest counter
		int min_page = LFUQueue.begin() -> first; 
		int min_count = LFUQueue.begin() -> second;
		for (auto item: LFUQueue)
		{
			int page = item.first, count = item.second;
			if (count == 1) // this is the min count, so just push it out
			{
				min_page = page;
				break;
			}
			if (min_count > count)
			{
				min_count = count;
				min_page = page;
			}
		}
		table.erase(min_page);
		LFUQueue.erase(min_page);
	}
	
	// Insert new page in the queue with frequency 1
	LFUQueue[page] = 1;	

	// Insert page into page table
	table.insert(page);
}

void LFUcache::updateHit(int page) 
{
	//update counter for the page
	LFUQueue[page] += 1;
}
