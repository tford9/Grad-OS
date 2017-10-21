#include "cacheBase.h"
#include <map>
#include <set>
#include <iostream>

using namespace std;

//given a range of addresses (and assuming they are contiguous), allocate
//the page boundaries
void Cache::allocatePages(unsigned long beginAddress, unsigned long endAddress)
{
	n = 0;		//number pages starting from 0
	unsigned long curr = beginAddress;
	
	//insert starting address of pages into table map
	pageBoundary[curr] = n;
	n++;
	while (curr + page < endAddress)
	{
		curr += page;
		pageBoundary[curr] = n;
		n++;
	}
}

//given a data object address, find what page it is in and 
//determine if this page results in a cache hit or miss
void Cache::lookup(unsigned long address)
{
	//find page containing this address
	int page = (pageBoundary.lower_bound(address))->second;
	
	//check if page in cache
	if (table.find(page) != table.end())
	{
		//log the hit
		hit++;
		updateHit(page);
	}
	//page not in cache, log a miss and pass control to derived class to handle it
	else
	{
		miss++;
		updateMiss(page);
	}
}

//print results of cache sim
void Cache::printResults()
{
	cout << "Simulator Results" << endl;
	cout << hit + miss << " table lookups" << endl;
	cout << hit << " hits" << endl;
	cout << miss << " misses" << endl;
	
}
