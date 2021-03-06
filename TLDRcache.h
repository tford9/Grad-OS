#ifndef TLDR_CACHE
#define TLDR_CACHE

#include <unordered_map>
#include <utility>
#include <cmath>
#include <iostream>

#include "cacheBase.h"

using namespace std;

class TLDRcache : public Cache 
{
	public:
		TLDRcache(int cacheSize, int pageSize);
	
		virtual void updateMiss(int page);

		virtual void updateHit(int page);
		
	private:
		//int page key -> (true = priv | false = unpriv), int hit
		unordered_map<int, pair<bool,int> > cacheLocation;
		int privCount = 0;
		int unprivCount = 0;
		int maxPriv = ceil(limit/2);
		int maxUnpriv = floor(limit/2);
};

#endif
