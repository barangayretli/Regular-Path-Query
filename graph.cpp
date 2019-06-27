#include "graph.h"

// Adds an edge to a directed graph 
void graph::addEdge(string start, string relation, string target) 
{ 
	edge temp;
	targetVertex tar;
	tar.targets.insert(target);
	temp.edgeLabel.insert(make_pair(relation, tar.targets));
	
	if(adjList.count(start)) // if it is already in the hashmap for starting edges
	{
		if(adjList[start].edgeLabel.count(relation)) // if the edge is already in the hashmap for the starting edge 
		{
			adjList[start].edgeLabel[relation].insert(target);
		}
		else // if the edge is not in the hashmap for starting edge
		{
			adjList[start].edgeLabel.insert(make_pair(relation,tar.targets));
		}

	}
	else // if the starting vertex does not exist in the hashtable for starting edges
	{
		adjList.insert(make_pair(start,temp));
	}
}

int graph::getSize()
{
	return adjList.size();
}

void graph::printTargetWithLabel(string start, string relation) 
{ 
	unordered_set<string> s = targetSet(start,relation);
	std::copy(s.begin(),s.end(),std::ostream_iterator<std::string>(std::cout, "\n"));
}   

bool graph::hasLabel(string start,string relation)
{
	return (adjList[start].edgeLabel.count(relation));
}

unordered_set<string> graph::targetSet(string start, string relation)
{
	return adjList[start].edgeLabel[relation];
}

bool graph::hasStartingVertex(string start)
{
	return adjList.count(start);
}

bool graph::hasTarget(string start, string relation, string target)
{
	return adjList[start].edgeLabel[relation].count(target);
}
