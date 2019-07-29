#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>
#include <ostream>
#include "graph.h"


using namespace std;

struct relation{
	string start;
	string edge;
	string target;
};

struct QueryGraph{
	int first;
	int second;
	string label;
};

int main(){

	ifstream myReadFile;
	vector<relation> graphContainer;
	vector<QueryGraph> automataContainer;
	myReadFile.open("relations.txt");
	string start;
	string edge;
	string target;
	relation temp;
	while(myReadFile >> start >> edge >> target)
	{
		temp.start=start;
		temp.edge=edge;
		temp.target=target;
		graphContainer.push_back(temp);
	}
	graph g;
	for(unsigned int i=0; i<graphContainer.size();i++)
	{
		g.addEdge(graphContainer[i].start,graphContainer[i].edge,graphContainer[i].target);
	}
	string f;
	string s;
	string label;
    int maxState = 0;
	QueryGraph q;
	ifstream readFile;
	readFile.open("QueryGraph.txt");
    automata au;
	while(readFile >> f >> label >> s)
	{
		q.first=stoi(f);
		q.label=label;
		q.second=stoi(s);
		automataContainer.push_back(q);
	}
	for(unsigned int i=0; i<automataContainer.size();i++)
	{
        au.addEdge(automataContainer[i].first,automataContainer[i].label,automataContainer[i].second);
        if(automataContainer[i].first > maxState)
            maxState = automataContainer[i].first;
        if(automataContainer[i].second > maxState)
            maxState = automataContainer[i].second;
	}
    au.setMaxState(maxState);
    
    productGraph p;
	p.buildPG(g,au);
	p.results(make_pair("ten",0),maxState);
    
    adjListVect v;
    v.buildPG( g,au);
    v.results("ten0", maxState);
    
    CSR c(v.vertexNum,v.neighborNum);
    c.buildMap(v);
    c.buildIndexArr(v);
    c.buildCSR(v);
    c.results("ten0",maxState);
    
	return 0;
}
