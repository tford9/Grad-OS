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
		// LRUQueue contains LRU queue (using a vector for removes in the middle)
		vector<int> LRUQueue;
};

#endif
