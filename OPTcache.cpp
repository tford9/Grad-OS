#include <vector>
#include <algorithm>
#include <iostream>

#include "cacheBase.h"
#include "OPTcache.h"

using namespace std;

OPTcache::OPTcache(int cacheSize, int pageSize) : Cache(cacheSize, pageSize) { }

//Since we need precognition for this, we're going to hack the base class
//framework by not inserting pages into the table during the simulation.
//This will force every page access to trigger a miss down to the derived class,
//at which point we'll just add the page number to the in-order list of accesses.
//Then, when the optimalSim method gets called, we'll use this access history
//to reconstruct the cache accesses and always choose the optimal replacement.

void OPTcache::updateMiss(int page) 
{
	access_history.push_back(page);		//add to list of accesses
}

void OPTcache::optimalSim()
{
	//declare some local counters (will send to base class at the end)
	int hit = 0, miss = 0;
	
	//loop the access pattern
	for (int i = 0; i < (int)access_history.size(); i++)
	{
		//page already in table, log a hit
		if (table.find(access_history[i]) != table.end())
			hit++;
		//page not in table, find the optimal victim and insert it
		else
		{
			miss++;
			//find page currently in table that is next accessed furthest
			//in the future
			int far = -5;
			int far_page;
			for (auto pg = table.begin(); pg != table.end(); pg++)	//loop table
			{
				//find next instance of page
				int j = -1;
				for (j = i+1; j < (int)access_history.size(); j++)
				{
					if (access_history[j] == *pg)
						break;
				}
				
				//if page not accessed at all in the future, don't need it ever
				//again - kick it out!
				if (j == -1)
				{
					far_page = *pg;
					break;
				}
				
				//keep track of furthest out access
				if (j > far)
				{
					far = j;
					far_page = *pg;
				}				
			}
			
			//evict farthest-out page in favor of new page
			table.erase(far_page);
			table.insert(access_history[i]);
		}
	}
}
