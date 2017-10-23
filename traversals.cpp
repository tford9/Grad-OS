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
    s.push(source);
    Traverse::visited[source] = true;
    while (s.size() != 0)
    {
        int u = s.top();
        s.pop();
        while (true)
        {
            int v = Traverse::graph -> getNextNeighbor(u);
            if (v == -1) // the sentinel value which indicates the end of neighbors
                break;
            if (not Traverse::visited[v])
            {
                Traverse::visited[v] = true;
                s.push(v);
            }
        }
    }
}
