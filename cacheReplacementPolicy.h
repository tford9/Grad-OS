
#include "cacheBase.h"
#include <vector> 

using namespace std;

class RoundRobinPolicy : public Cache 
{
public:
	void updateMiss(int page);
private:
	// FIFOQueue contains FIFO queue
	std::vector<int> FIFOQueue;
};

void updateMiss(int page) {
	// If the queue/table is full
	if (FIFOQueue.size() == Cache::limit) {
		// Evict the head of the queue 
		Cache::table.erase(FIFOQueue.pop_back());
	}

	// Insert new page at back of queue
	FIFOQueue.insert(page);
	// Insert page into page table
	Cache::table.insert(page);
}