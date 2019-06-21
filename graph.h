#include <iostream>
#include <unordered_map>
#include <string>
#include <unordered_set>


using namespace std;



struct edge{

	unordered_set<string>targets;
	unordered_map<string, unordered_set<string>> edgeLabel;
	
};

typedef unordered_map<string, edge>::iterator umit; 

class graph{

private:
		unordered_map<std::string, edge> adjList;
		
public:
// Adds an edge to a directed graph 
void addEdge(string start, string relation, string target) 
{ 
	edge temp;
	temp.targets.insert(target);
	temp.edgeLabel.insert(make_pair(relation, temp.targets));
	
	
	if(adjList.count(start)) // if it is already in the hashmap for starting edges
	{
		if(adjList[start].edgeLabel.count(relation)) // if the edge is already in the hashmap for the starting edge 
		{
			adjList[start].edgeLabel[relation].insert(target);
		}
		else // if the edge is not in the hashmap for starting edge
		{
			adjList[start].edgeLabel.insert(make_pair(relation,temp.targets));
		}

	}
	else // if it does not exist in the hashtable for starting edges
	{
		adjList.insert(make_pair(start,temp));
	}
}

int getSize()
{
	return adjList.size();
}

void printTargetWithLabel(string start, string relation) 
{ 
	copy(targetSet(start, relation).begin(), targetSet(start, relation).end(), ostream_iterator<string>(cout, " "));
}   

bool hasLabel(string start,string relation)
{
	return (adjList[start].edgeLabel.count(relation));
}

unordered_set<string> targetSet(string start, string relation)
{
	return adjList[start].edgeLabel[relation];
}


};
	

