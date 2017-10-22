#ifndef TRAVS
#define TRAVS

#include "travBase.h"
#include <queue>
#include <stack>

using namespace std;

class BFStrav : public Traverse
{
    private:
        queue<int> q;
    public:
        void runTraversal(int Source);
};

class DFStrav : public Traverse
{
    private:
        stack<int> s;

    public:
        void runTraversal(int Source);
};

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
#endif