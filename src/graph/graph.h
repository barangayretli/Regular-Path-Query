#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <string>
#include <boost/functional/hash.hpp>
#include <list>
#include "automata/automata.h"

class productGraph{
    
private:
    struct adjVert{
        std::vector<std::pair<std::string,int>> adjacentVertices; // vector of adjacent vertices of a vertex
    };
    std::unordered_map<std::pair<std::string,int>,adjVert,boost::hash<std::pair<std::string,int>>> ProductMap; // starting vertex map
    friend class CSR;
    
public:
    void addEdge(automata q, std::string start, std::string label, std::string end); // adds an edge to the graph
    int vertexNum=0;
    int neighborNum=0;
    unsigned long edgeNumber=0;
};
class CSR{
    
private:
    int n, m; // size of vertex and neighbors
    int count=0;
    int* CSRmatrix; // CSRMatrix that contains only the neighbors
    int* indices; // index of the starting vertices
    bool* visited; // boolean array to check if a vertex is visited during BFS
    std::unordered_map<std::string, int> mapValues; // map of string vertices
    std::string* inverted; // inverse of mapValues
    std::vector<std::string> Vertex0;
    
public:
    CSR(int n, int m); // CSRMatrix constructor
    void buildIndexArr(productGraph *p); // Construct the index array
    void buildCSR(productGraph *p); // Construct CSR matrix
    void buildMap(productGraph *p); // Handles mapping of strings

    void BFS(std::string startVertex, int maxState, int & vertexNumCheck); // BFS on product graph
    void getInterval(int currvertex,int & start, int & end); // interval of neighbors of a vertex in CSR matrix
    std::vector<std::string> getVertex0();
};

#endif 
