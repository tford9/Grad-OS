#ifndef FIFO_CACHE
#define FIFO_CACHE

#include "cacheBase.h"
#include <vector>
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
