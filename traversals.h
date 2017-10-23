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
        BFStrav();
        BFStrav(GraphData *graphPtr); 
        void runTraversal(int Source);
};

class DFStrav : public Traverse
{
    private:
        stack<int> s;

    public:
        DFStrav();
        DFStrav(GraphData *graphPtr);
        void runTraversal(int Source);
};

#endif