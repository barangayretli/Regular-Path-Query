#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>
#include <ostream>
#include "graph.h"

using namespace std;

typedef pair<string, int> pairs; 

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
	struct temp;
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
	}

	productGraph p;
	p.buildPG(g,au);
	p.results(make_pair("ten",0));

	return 0;
}