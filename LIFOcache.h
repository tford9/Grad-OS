#ifndef LIFO_CACHE
#define LIFO_CACHE

#include <vector>

#include "cacheBase.h"

using namespace std;

class LIFOcache : public Cache 
{
	public:
		LIFOcache(int cacheSize, int pageSize);
	
		virtual void updateMiss(int page);
		
	private:
		// LIFOQueue contains LIFO stack
		//this queue is treated like a stack
		vector<int> LIFOQueue;
};

#endif
