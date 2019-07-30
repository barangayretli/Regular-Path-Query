#include <iostream>
#include <unordered_map>
#include <vector>

class automata{
public:
    
    void addEdge(int start, std::string label, int target);// adds an edge to the automata graph
    friend class productGraph;
    friend class adjListVect;
private:
    struct VertexPairSet{
        std::vector<std::pair<int,int>> VertexNeighbors; // starting and ending edges
    };
    std::unordered_map<std::string, VertexPairSet> automataGraph; // maps from relation to edges
};
