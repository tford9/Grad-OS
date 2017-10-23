#ifndef CACHE_REPLACEMENT_POLICIES
#define CACHE_REPLACEMENT_POLICIES

#include <vector>

#include "cacheBase.h"

using namespace std;

class FIFOcache : public Cache 
{
	public:
		FIFOcache(int cacheSize, int pageSize);
	
		virtual void updateMiss(int page);
		
	private:
		// FIFOQueue contains FIFO queue
		vector<int> FIFOQueue;
};

#endif
