#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <boost/functional/hash.hpp>

using namespace std;

class automata{
public:
    
    void addEdge(int start, string label, int target);// adds an edge to the automata graph
    void setMaxState(int maxState);// sets the max state of automata
    unordered_map<string,pair<int,int>>getMap(automata au);// returns to the automata graph
    int maxS; // max state
    friend class productGraph;
    friend class adjListVect;
    
private:
    struct VertexPairSet{
        unordered_multiset<pair<int,int>,boost::hash<pair<int, int>>> VertexSetautomata; // starting and ending edges
    };
    unordered_map<string, VertexPairSet> map1; // maps from relation to edges
};
