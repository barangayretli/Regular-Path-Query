#include <iostream>
#include <fstream>
#include "graph.h"

using namespace std;

struct QueryGraph{// automata edge
	int first;
	int second;
	string label;
};

int main(){
    automata au;
    ///////////////////////
	ifstream graphRead;
    ifstream automataFile;
    ///////////////////////
    graphRead.open("relations.txt");
    automataFile.open("QueryGraph.txt");
    ///////////////////////
	vector<QueryGraph> automataContainer;
    ///////////////////////
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
    ///////////////////////
    productGraph p;
    adjListVect v;
    ///////////////////////
	while(graphRead >> start >> edge >> target)// reading the vertices and edges line by line from the txt file
	{
        p.addEdge(au, start, edge, target);
        v.buildProductGraph(au, start, edge, target);
	}
    ////////////////
	p.results(make_pair("ten",0),maxState);
    //////////////// Adjacency List Representation using vector
    v.BFS("ten0", maxState);
    //////////////// CSR Matrix Representation
    CSR c(v.vertexNum,v.neighborNum);
    c.buildMap(v);
    c.buildIndexArr(v);
    c.buildCSR(v);
    c.BFS("ten0",maxState);
    
	return 0;
}
