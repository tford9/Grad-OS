#include <algorithm>
#include <cmath>
#include <iostream>

#include "cacheBase.h"
#include "MLQcache.h"

using namespace std;

MLQcache::MLQcache(int cacheSize, int pageSize) : Cache(cacheSize, pageSize) { }

void MLQcache::updateMiss(int page)
{
	int minUnprivValue = -1;
	int minUnprivPage;

	int maxUnprivValue = -1;
	int maxUnprivPage;

	//both caches are full - evict from unprivilege cache and add new page to it
	if (unprivCount == maxUnpriv && privCount == maxPriv)
	{
		for(auto i = cacheLocation.begin(); i != cacheLocation.end(); ++i)
		{
			if(((i->second).first == false && minUnprivValue == -1) || 
				((i->second).first == false && (i->second).second < minUnprivValue))
			{
				minUnprivPage = i->first;
				minUnprivValue = (i->second).second;
			}
		}
		table.erase(minUnprivPage);
		table.insert(page);
		cacheLocation.erase(minUnprivPage);
		cacheLocation[page].first = false;
		cacheLocation[page].second = 1;
	}
	//unprivilege is full, privilege is not - promote to privilege and then add to unprivilege
	else if(unprivCount == maxUnpriv && privCount < maxPriv)
	{	
		//iterate from end to begin - find max unprivilege page - promote
		for(auto i = cacheLocation.begin(); i != cacheLocation.end(); ++i)
		{
			if(((i->second).first == false && maxUnprivValue == -1) || 
				((i->second).first == false && (i->second).second > maxUnprivValue))
			{
				maxUnprivPage = i->first;
				maxUnprivValue = (i->second).second;
			}
		}
		cacheLocation[maxUnprivPage].first = true; //promote
		table.insert(page);
		cacheLocation[page].first = false;
		cacheLocation[page].second = 1;
		++privCount; //have one more in privilege
	}
	//unprivilege is not full
	else
	{
		table.insert(page);
		cacheLocation[page].first = false;
		cacheLocation[page].second = 1;
		++unprivCount;
	}

	//if there is a miss, decrement all privilege frequency by one (unless it is 0)
	//age the unpriv 2x as much as the priv
	for(auto i = cacheLocation.begin(); i != cacheLocation.end(); ++i)
	{
		//upper level - decrement 1
		if ((i->second).first == true))
			(i->second).second -= 1;
		//decrement lower by 2
		if((i->second).first == false))
			(i->second).second -= 2;
		//cap to min of 0
		if ((i->second).second < 0)
			(i->second).second = 0;
	}
	return;
}

void MLQcache::updateHit(int page)
{
	//increment hit counter
	(cacheLocation[page].second) += 1;
	
	//in upper level, quit
	if (cacheLocation[page].first == true)
		return;

	int minPrivValue = -1;
	int minPrivPage;

	int maxUnprivValue = -1;
	int maxUnprivPage;

	//find the min in priv and max in unpriv
	for(auto i = cacheLocation.begin(); i != cacheLocation.end(); ++i)
	{
		if(((i->second).first == true) && ((minPrivValue == -1) || (i->second).second < minPrivValue))
		{
			minPrivValue = (i->second).second;
			minPrivPage = i->first;
		}
		if(((i->second).first == false) && ((maxUnprivValue == -1) || (i->second).second > maxUnprivValue))
		{
			maxUnprivValue = (i->second).second;
			maxUnprivPage = i->first;
		}
	}

	//if minPriv < maxUnpriv, swap the two
	//choose to make the frequency of the new page in unPriv to 
	if(minPrivValue != -1 && maxUnprivValue != -1 && minPrivValue < maxUnprivValue)
	{		
		cacheLocation[maxUnprivPage].first = true;	//always promote
		//if upper level full, do a demotion
		if (privCount == maxPriv)
			cacheLocation[minPrivPage].first = false;
		//not full, update counts
		else
		{
			privCount++;
			unprivCount--;
		}
	}
}
