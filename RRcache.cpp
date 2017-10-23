#include "cacheBase.h"
#include "RRcache.h"
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

RRcache::RRcache(int cacheSize, int pageSize) : Cache(cacheSize, pageSize) 
{
	srand (time(NULL)); 	//seed the randomizer
}

void RRcache::updateMiss(int page) 
{
	//if the table is full, randomly evict one
	if ((int)table.size() == limit) 
	{
		//generate a random number from 0 to limit-1
		int offset = rand() % limit;
		auto it = table.begin();
		advance(it, offset);
		
		//erase that page
		table.erase(it);
	}
	
	//insert new page
	table.insert(page);	
}
