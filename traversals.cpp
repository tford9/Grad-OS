#include <queue>
#include <stack>

#include "traversals.h"

BFStrav::BFStrav() {}
BFStrav::BFStrav(GraphData *graphPtr) : Traverse(graphPtr) {}

DFStrav::DFStrav() {}
DFStrav::DFStrav(GraphData *graphPtr) : Traverse(graphPtr) {}


void BFStrav::runTraversal(int source)
{
    q.push(source);
    Traverse::visited[source] = true;
    while (q.size() != 0)
    {
        int u = q.front();
        q.pop();
        while (true)
        {
            int v = Traverse::graph -> getNextNeighbor(u);
            if (v == -1) // the sentinel value which indicates the end of neighbors
                break;
            if (not Traverse::visited[v])
            {
                Traverse::visited[v] = true;
                q.push(v);
            }
        }
    }
}

void DFStrav::runTraversal(int source)
{
   	if (Traverse::visited[source] == true)
   		return;
   		
    Traverse::visited[source] = true;
    for (int v = Traverse::graph->getNextNeighbor(source); v != -1; v = Traverse::graph->getNextNeighbor(source))
    {
    	if (Traverse::visited[v] == false)
    		runTraversal(v);
    }
    return;
}
