#pragma once

#include <iostream>
#include <unordered_map>
#include <string>
#include <unordered_set>

using namespace std;

class graph{

public: 

void addEdge(string start, string relation, string target);
int getSize();
void printTargetWithLabel(string start, string relation); 
bool hasLabel(string start,string relation);
unordered_set<string>targetSet(string start, string relation);
bool hasStartingVertex(string start);
bool hasTarget(string start, string relation, string target);

private:

struct targetVertex
{
unordered_set<string>targets;
};

struct edge
{	
	unordered_map<string, unordered_set<string>> edgeLabel;
};

unordered_map<string, edge> adjList;

};

	

