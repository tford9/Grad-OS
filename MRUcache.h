#ifndef MRU_CACHE
#define MRU_CACHE

#include <deque>

#include "cacheBase.h"

using namespace std;

class MRUcache : public Cache 
{
	public:
		MRUcache(int cacheSize, int pageSize);
	
		virtual void updateMiss(int page);

		virtual void updateHit(int page);
		
	private:
		// MRUQueue contains MRU queue (using a vector for removes in the middle)
		deque<int> MRUQueue;
};

#endif