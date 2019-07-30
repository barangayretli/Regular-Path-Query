#pragma once

#include <iostream>
#include <unordered_map>
#include <string>
#include <unordered_set>
#include <boost/functional/hash.hpp>
#include <list>
#include "automata.h"


using namespace std;

class productGraph{

private:
	struct adjVert{
	unordered_set<pair<string,int>,boost::hash<pair<string, int>>> adjacentVertices;	 //hash table is not neccessary
	};	
	unordered_map<pair<string,int>,adjVert,boost::hash<pair<string,int>>>ProductMap;
    
public:
	void printSet(unordered_set<pair<string,int>,boost::hash<pair<string, int>>>);
    void addEdge(automata q, string start, string label, string end);
	unordered_set<pair<string,int>,boost::hash<pair<string, int>>> results(pair<string,int>, int maxState);
};

class adjListVect{
    
private:
    vector<pair<string,vector<string>>>adjVect;
    friend class CSR;
    
public:
    void addEdge(string edge1, string edge2);
    void buildProductGraph(automata q, string start, string label, string end);
    void BFS(string edge1, int maxState);
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
    void BFS(string startVertex, int maxState);
    void printArr(vector<string>arr);
    void getInterval(int currvertex,int & start, int & end);
};
