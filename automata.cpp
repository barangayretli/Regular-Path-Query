#include "automata.h"

typedef std::pair<int, int> pairs;

void automata::addEdge(int start, std::string label, int target)// adds an edge to the automata graph
{
    VertexPairSet s;
    pairs p = std::make_pair(start,target);
    s.VertexNeighbors.push_back(p);
    if(automataGraph.count(label))
    {
        automataGraph[label].VertexNeighbors.push_back(p);
    }
    else
    {
        automataGraph.insert(make_pair(label,s));
    }
}

