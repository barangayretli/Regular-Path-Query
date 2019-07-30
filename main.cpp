#include <iostream>
#include <fstream>
#include "graph.h"

using namespace std;

int main(){
   
    ifstream graphRead, automataFile;
    ///////////////////////
    graphRead.open("relations.txt");
    automataFile.open("QueryGraph.txt");
    ///////////////////////
	string start,edge,target,f,s,label;
    int maxState = 0,first,second;
    ///////////////////////
    automata au;
    while(automataFile >> f >> label >> s)// reading automata from a txt file
    {
        first = stoi(f);
        second = stoi(s);
        au.addEdge(first, label, second);
        if(first > maxState)
            maxState = first;
        if(second > maxState)
            maxState = second;
    }
    /////////////////
    productGraph p;
    adjListVect v;
    /////////////////
	while(graphRead >> start >> edge >> target)// reading the vertices and edges line by line from the txt file
	{
        p.addEdge(au, start, edge, target);
        v.buildProductGraph(au, start, edge, target);
	}
    ////////////////
	p.BFS(make_pair("ten",0),maxState);
    ////////////////
    v.BFS("ten0", maxState);
    //////////////// CSR Matrix Representation
    CSR c(v.vertexNum+v.neighborNum,v.neighborNum);
    c.buildMap(v);
    c.buildIndexArr(v);
    c.buildCSR(v);
    c.BFS("ten0",maxState);
    
	return 0;
}
