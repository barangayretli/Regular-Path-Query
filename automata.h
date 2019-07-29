#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <boost/functional/hash.hpp>

using namespace std;

class automata{
public:
    
    void addEdge(int start, string label, int target);
    void setMaxState(int maxState);
    unordered_map<string,pair<int,int>>getMap(automata au);
    int maxS;
    friend class productGraph;
    friend class adjListVect;
    
private:
    struct VertexPairSet{
        unordered_multiset<pair<int,int>,boost::hash<pair<int, int>>> VertexSetautomata;
    };
    unordered_map<string, VertexPairSet> map1;
};
