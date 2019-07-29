#include <iostream>
#include <fstream>
#include "graph.h"

using namespace std;

struct relation{// graph edge
	string start;
	string edge;
	string target;
};

struct QueryGraph{// automata edge
	int first;
	int second;
	string label;
};

int main(){

    graph g;
    automata au;
    ///////////////////////
	ifstream graphRead;
    ifstream automataFile;
    ///////////////////////
    graphRead.open("relations.txt");
    automataFile.open("QueryGraph.txt");
    ///////////////////////
	vector<relation> graphContainer;
	vector<QueryGraph> automataContainer;
    ///////////////////////
    relation r;
    QueryGraph q;
    ///////////////////////
	string start;
	string edge;
	string target;
	// Temporary containers
    string f;
    string s;
    string label;
    int maxState = 0;
    ///////////////////////
	while(graphRead >> start >> edge >> target)// reading the vertices and edges line by line from the txt file
	{
		r.start=start;
		r.edge=edge;
		r.target=target;
		graphContainer.push_back(r);
	}
	for(unsigned int i=0; i<graphContainer.size();i++)// insert vertices and edges to the graph
	{
		g.addEdge(graphContainer[i].start,graphContainer[i].edge,graphContainer[i].target);
	}
    ////////////////////////
	while(automataFile >> f >> label >> s)// reading automata from a txt file
	{
		q.first=stoi(f);
		q.label=label;
		q.second=stoi(s);
		automataContainer.push_back(q);
	}
	for(unsigned int i=0; i<automataContainer.size();i++)//insert states and calculate the maximum state
	{
        au.addEdge(automataContainer[i].first,automataContainer[i].label,automataContainer[i].second);
        if(automataContainer[i].first > maxState)
            maxState = automataContainer[i].first;
        if(automataContainer[i].second > maxState)
            maxState = automataContainer[i].second;
	}
    au.setMaxState(maxState);
    //////////////// Adjacency List Representation using HashMap and HashTable
    productGraph p;
	p.buildPG(g,au);
	p.results(make_pair("ten",0),maxState);
    //////////////// Adjacency List Representation using vector
    adjListVect v;
    v.buildPG( g,au);
    v.results("ten0", maxState);
    //////////////// CSR Matrix Representation
    CSR c(v.vertexNum,v.neighborNum);
    c.buildMap(v);
    c.buildIndexArr(v);
    c.buildCSR(v);
    c.results("ten0",maxState);
    
	return 0;
}
