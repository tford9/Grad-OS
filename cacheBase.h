#ifndef CACHE_BASE
#define CACHE_BASE

#include <map>
#include <set>

using namespace std;

class Cache
{
	private:
		int size, page;		//size of cache and pages
		unsigned long long hit, miss;		//number of cache hits and misses
		int n;				//number of pages
		map<unsigned long, int> pageBoundary;	//key - starting address of page
													//value - page number
		//given a page table hit, update any necessary metadata (only override if necessary)
		//note that the base class already tallies the hit, so this is just for tracking
		//references to pages (ie, for LRU)
		virtual void updateHit(int page);
		
		//given a page table miss, load the page and update any metadata according
		//to cache replacement policy (must override this function)
		virtual void updateMiss(int page) = 0;

	protected:
		set<int> table;		//set of pages in cache
		int limit;			//number of pages that will fit in cache
		void setCounts(int newHit, int newMiss);	//setter for optimal cache
	public:	
		/* Base Class Constructor */ 
		Cache(int cacheSize, int pageSize) 
			: size(cacheSize), page(pageSize), hit(0), miss(0), limit(cacheSize/pageSize) { };
		
		//given a range of addresses (and assuming they are contiguous), allocate
		//the page boundaries
		void allocatePages(unsigned long beginAddress, unsigned long endAddress);
		
		//given a data object address, find what page it is in and 
		//determine if this page results in a cache hit or miss
		void lookup(unsigned long address);
		
		void printResults();
};

#endif
