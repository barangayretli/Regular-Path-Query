#pragma once

#include <iostream>
#include <unordered_map>
#include <string>
#include <unordered_set>
#include <boost/functional/hash.hpp>
#include <list>

using namespace std;

class graph{

private:
struct Vertices{
	unordered_multiset<pair<string,string>,boost::hash<pair<string, string>>> VertexSetgraph;
};
unordered_map<string, Vertices> adjList;
friend class productGraph;
friend class adjListVect;

public: 
int getLabelSize();
void addEdge(string start, string relation, string target);

};


class automata{
public:
	
void addEdge(int start, string label, int target);
friend class productGraph;
friend class adjListVect;
    
private:
struct VertexPairSet{

unordered_multiset<pair<int,int>,boost::hash<pair<int, int>>> VertexSetautomata;
};

unordered_map<string, VertexPairSet> map1;

};


class productGraph{

private:
	struct adjVert{
	unordered_set<pair<string,int>,boost::hash<pair<string, int>>> adjacentVertices;	
	};	
	unordered_map<pair<string,int>,adjVert,boost::hash<pair<string,int>>>ProductMap;
public:
	void printSet(unordered_set<pair<string,int>,boost::hash<pair<string, int>>>);
	void buildPG(graph g, automata q);
	unordered_set<pair<string,int>,boost::hash<pair<string, int>>> results(pair<string,int>);
};


class adjListVect{
private:
    vector<pair<string,vector<string>>>adjVect;
    friend class CSR;
public:
    void addEdge(string edge1, string edge2);
    void buildPG(graph g, automata q);
    void results(string edge1);
    void printArr(vector<string> arr);
};

class CSR{
private:
    int currIndex=0;
    int count=0;
    vector<int> CSRmatrix;
    vector<pair<int,int>> indices;
    unordered_map<string, int> mapValues;
    vector<string> inverted;
public:
    void buildIndexArr(adjListVect v);
    void buildCSR(adjListVect v);
    void buildMap(adjListVect v);
    void results(string edge1);
    void printArr(vector<string>arr);
    int getInterval(vector<pair<int,int>> temp, int currvertex,int& i);
    
};
