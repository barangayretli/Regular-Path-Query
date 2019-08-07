#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <string>
#include <boost/functional/hash.hpp>
#include <list>
#include <chrono>
#include "automata.h"

typedef std::chrono::high_resolution_clock Clock;
typedef Clock::time_point ClockTime;


class productGraph{
    
private:
    struct adjVert{
        std::vector<std::pair<std::string,int>> adjacentVertices; // vector of adjacent vertices of a vertex
    };
    std::unordered_map<std::pair<std::string,int>,adjVert,boost::hash<std::pair<std::string,int>>> ProductMap; // starting vertex map
    friend class CSR;
    
public:
    void printArr(std::vector<std::pair<std::string,int>>); // prints the result array
    void addEdge(automata q, std::string start, std::string label, std::string end); // adds an edge to the graph

    void BFS(std::pair<std::string,int>, int maxState, int & vertexNumCheck, std::chrono::duration<long long, std::ratio<1, 1000000000> > & visitedTime, std::chrono::duration<long long, std::ratio<1, 1000000000> > & ifCheckTime);// BFS on product graph
    std::vector<std::pair<std::string,int>> getVertex0 ();
    int vertexNum=0;
    int neighborNum=0;

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
    void buildIndexArr(productGraph p); // Construct the index array
    void buildCSR(productGraph p); // Construct CSR matrix
    void buildMap(productGraph p); // Handles mapping of strings

    void BFS(std::string startVertex, int maxState, int & vertexNumCheck, std::chrono::duration<long long, std::ratio<1, 1000000000> > & visitedTime, std::chrono::duration<long long, std::ratio<1, 1000000000> > & ifCheckTime); // BFS on product graph
    void getInterval(int currvertex,int & start, int & end); // interval of neighbors of a vertex in CSR matrix
    void setFalse();
    std::vector<std::string> getVertex0();
};

#endif 
