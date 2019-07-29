#pragma once

#include <iostream>
#include <unordered_map>
#include <string>
#include <unordered_set>
#include <boost/functional/hash.hpp>
#include <list>
#include "automata.h"


using namespace std;

template <typename VT>
class testGraph{
    testGraph(VT obj1, VT obj2);
    testGraph(string str, VT strPair);
private:
    struct Neighbor{
        unordered_set<VT> NeighborSet;
    };
    unordered_map<VT,Neighbor> Vertices;
public:
    void addEdge(VT obj1, VT obj2);
    void addEdge(string str, VT obj2);
    void buildPg(automata au);
    void BFS(unordered_set<pair<string,int>,boost::hash<pair<string, int>>>);
};

class graph{

private:
struct Vertices{
	unordered_multiset<pair<string,string>,boost::hash<pair<string, string>>> VertexSetgraph;
};
unordered_map<string, Vertices> adjList;
friend class productGraph;
friend class adjListVect;

public:
void addEdge(string start, string relation, string target);

};

class productGraph{

private:
	struct adjVert{
	unordered_set<pair<string,int>,boost::hash<pair<string, int>>> adjacentVertices;	 //ash table is not neccessary
	};	
	unordered_map<pair<string,int>,adjVert,boost::hash<pair<string,int>>>ProductMap;
    
public:
	void printSet(unordered_set<pair<string,int>,boost::hash<pair<string, int>>>);
	void buildPG(graph g, automata q);
	unordered_set<pair<string,int>,boost::hash<pair<string, int>>> results(pair<string,int>, int maxState);
};

class adjListVect{
    
private:
    vector<pair<string,vector<string>>>adjVect;
    friend class CSR;
    
public:
    void addEdge(string edge1, string edge2);
    void buildPG(graph g, automata q);
    void results(string edge1, int maxState);
    void printArr(vector<string> arr);
    int vertexNum=0;
    int neighborNum=0;
    friend class CSR;
};

class CSR{
    
private:
    int n, m;
    int count=0;
    int* CSRmatrix;
    int* indices;
    bool* visited;
    unordered_map<string, int> mapValues;
    string* inverted;
    
public:
    CSR(int n, int m);
    void buildIndexArr(adjListVect v);
    void buildCSR(adjListVect v);
    void buildMap(adjListVect v);
    void results(string startVertex, int maxState);
    void printArr(vector<string>arr);
    void getInterval(int currvertex,int & start, int & end);
};
