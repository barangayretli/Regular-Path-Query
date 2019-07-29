#include "automata.h"

using namespace  std;

typedef pair<int, int> pairs;

static int maxsta = 0;

void automata::addEdge(int start, string label, int target)
{
    VertexPairSet s;
    pairs p = make_pair(start,target);
    s.VertexSetautomata.insert(p);
    if(map1.count(label))
    {
        map1[label].VertexSetautomata.insert(p);
    }
    else
    {
        map1.insert(make_pair(label,s));
    }
}


void automata::setMaxState(int maxState)
{
    maxsta = maxState;
    maxS = maxState;
}
