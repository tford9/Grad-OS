#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>

#include "cacheBase.h"
#include "MLQcache.h"

//QUESTION: When should we demote from pivilege to unprivilege

using namespace std;

MLQcache::MLQcache(int cacheSize, int pageSize) : Cache(cacheSize, pageSize) {}

void MLQcache::updateMiss(int page)
{
	int minUnprivValue = -1;
	int minUnprivPage;

	int maxUnprivValue = -1;
	int maxUnprivPage;

	cerr << "MAX UNPRIV: " << maxUnpriv;
	cerr << "MAX PRIV: "  << maxPriv;

	//both caches are full - evict from unprivilege cache and add new page to it
	if (unprivCount == maxUnpriv && privCount == maxPriv)
	{
		for(auto i = cacheLocation.begin(); i != cacheLocation.end(); ++i)
		{
			if(((i->second).first == false && minUnprivValue == -1) || ((i->second).first == false && (i->second).second < minUnprivValue))
			{
				minUnprivPage = i->first;
				minUnprivValue = (i->second).second;
			}
		}
		table.erase(minUnprivPage);
		table.insert(page);
		cacheLocation.erase(minUnprivPage);
		cacheLocation[page].first = false;
		cacheLocation[page].second = 0;
		cerr << "BOTH FULL";
	}
	//unprivilege is full, privilege is not - promote to privilege and then add to unprivilege
	else if(unprivCount == maxUnpriv && privCount < maxPriv)
	{	
		//iterate from end to begin - find max unprivilege page - promote
		for(auto i = cacheLocation.begin(); i != cacheLocation.end(); ++i)
		{
			if(((i->second).first == false && maxUnprivValue == -1) || ((i->second).first == false && (i->second).second > maxUnprivValue))
			{
				maxUnprivPage = i->first;
				maxUnprivValue = (i->second).second;
			}
		}
		cacheLocation[maxUnprivPage].first = true; //promote
		table.insert(page);
		cacheLocation[page].first = false;
		cacheLocation[page].second = 0;
		++privCount; //have one more in privilege
		cerr << "UNPRIV FULL | PRIV NOT FULL";
	}
	//unprivilege is not full, but privilege is full
	else
	{
		table.insert(page);
		cacheLocation[page].first = false;
		cacheLocation[page].second = 0;
		++unprivCount;
		cerr << "UNPRIV NOT FULL";
	}

	for(auto i = cacheLocation.begin(); i != cacheLocation.end(); ++i)
	{
		if((i->second).first == true && (i->second).second > 0)
		{
			(i->second).second -= 1;
			cerr << "DECREMENT";
		}
	}
}

void MLQcache::updateHit(int page)
{
	(cacheLocation[page].second) += 1;
	
	cerr << "UPDATE HIT!!!";

	int minPrivValue = -1;
	int minPrivPage;

	int maxUnprivValue = -1;
	int maxUnprivPage;

	for(auto i = cacheLocation.begin(); i != cacheLocation.end(); ++i)
	{
		if(((i->second).first == true) || ((minPrivValue == -1) && (i->second).second > minPrivValue))
		{
			minPrivValue = (i->second).second;
			minPrivPage = i->first;
		}
		if(((i->second).first == false) || ((maxUnprivValue == -1) && (i->second).second < maxUnprivValue))
		{
			maxUnprivValue = (i->second).second;
			maxUnprivPage = i->first;
		}
	}
	if(minPrivValue != -1 && maxUnprivValue != -1 && minPrivValue < maxUnprivValue)
	{
		cacheLocation[minPrivValue].first = false;
		cacheLocation[minPrivValue].second = 0;
		cacheLocation[maxUnprivPage].first = true;
		cacheLocation[maxUnprivPage].second = 1;
	}
}
