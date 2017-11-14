#include <map>
#include <set>
#include <iostream>

#include "utils.h"
#include "cacheBase.h"

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
	if (DEBUG)
	{
		cerr << "Simulator Results" << endl;
		cerr << hit + miss << " table lookups" << endl;
		cerr << hit << " hits" << endl;
		cerr << miss << " misses" << endl;
	}
	else
		cout << hit << " " << miss << endl;
}

void Cache::setCounts(int newHit, int newMiss)
{
	hit = newHit;
	miss = newMiss;
}

//given a page table hit, update any necessary metadata (only override if necessary)
//note that the base class already tallies the hit, so this is just for tracking
//references to pages (ie, for LRU)
//some strategies may not need this, so empty implementation here
void Cache::updateHit(int page) { }

