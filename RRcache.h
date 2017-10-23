#ifndef RR_CACHE
#define RR_CACHE

#include "cacheBase.h"
using namespace std;

class RRcache : public Cache 
{
	public:
		RRcache(int cacheSize, int pageSize);
	
		virtual void updateMiss(int page);
};

#endif
