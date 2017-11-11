#ifndef OPT_CACHE
#define OPT_CACHE

#include <vector>

#include "cacheBase.h"

using namespace std;

class OPTcache : public Cache 
{
	public:
		OPTcache(int cacheSize, int pageSize);
	
		virtual void updateMiss(int page);
		
		virtual void optimalSim();
		
	private:
		vector<int> access_history;		//list of page accesses, in order
};

#endif
