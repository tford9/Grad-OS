#ifndef LRU_CACHE
#define LRU_CACHE

#include <vector>

#include "cacheBase.h"

using namespace std;

class LRUcache : public Cache 
{
	public:
		LRUcache(int cacheSize, int pageSize);
	
		virtual void updateMiss(int page);

		virtual void updateHit(int page);
		
	private:
		// FIFOQueue contains FIFO queue
		vector<int> LRUQueue;
};

#endif
