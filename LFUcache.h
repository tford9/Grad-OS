#ifndef LFU_CACHE
#define LFU_CACHE

#include <unordered_map>

#include "cacheBase.h"

using namespace std;

class LFUcache : public Cache 
{
	public:
		LFUcache(int cacheSize, int pageSize);
	
		virtual void updateMiss(int page);

		virtual void updateHit(int page);
		
	private:
		// LFUQueue contains LFU map - the key is a page and the value the frequency
		unordered_map<int,int> LFUQueue;
};

#endif
