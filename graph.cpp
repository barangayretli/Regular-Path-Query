#include "graph.h"

using namespace std;

typedef pair<string, string> edgePairs; 
typedef pair<int, int> pairs; 
typedef pair<string,int> strInt;

// Adds an edge to a directed graph 
void graph::addEdge(string start, string relation, string target) 
{ 
	Vertices v;
	edgePairs e = make_pair(start,target);

	v.VertexSetgraph.insert(e);

	if(adjList.count(relation)) // if it is already in the hashmap for starting edges
	{
		adjList[relation].VertexSetgraph.insert(e);
	}
	else // if the starting vertex does not exist in the hashtable for starting edges
	{
		adjList.insert(make_pair(relation,v));
	}

}

int graph::getLabelSize()
{
	return adjList.size();
}

void automata::addEdge(int start, string label, int target) 
{ 
	VertexPairSet s;
	pairs p = make_pair(start,target);
	s.VertexSetautomata.insert(p);
	if(map1.count(label))
	{
		map1[label].VertexSetautomata.insert(p);
	}
	else
	{
		map1.insert(make_pair(label,s));
	}
}




void productGraph::buildPG(graph g, automata q)
{
	int f; 
	int s;
	string fstr;
	string sstr;
	for (  const auto& it : q.map1)
	{

		for (auto itr = q.map1[it.first].VertexSetautomata.begin(); itr != q.map1[it.first].VertexSetautomata.end(); ++itr) 
		{ 
			f = itr->first;
			s = itr->second;
			for (auto itx = g.adjList[it.first].VertexSetgraph.begin(); itx != g.adjList[it.first].VertexSetgraph.end(); ++itx) 
			{ 
				fstr = itx->first;
				sstr = itx->second;
				strInt p1 = make_pair(fstr,f);
				strInt p2 = make_pair(sstr,s);
				adjVert temp;
				temp.adjacentVertices.insert(p2);
				if(ProductMap.count(p1))
				{
					ProductMap[p1].adjacentVertices.insert(p2);
				}
				else
				{
					ProductMap.insert(make_pair(p1,temp));
				}
			} 
		}


	}

}



unordered_set<pair<string,int>,boost::hash<pair<string, int>>> productGraph::results(pair<string,int> startVertex)
{
	unordered_map<pair<string,int>,bool,boost::hash<pair<string, int>>> visited;

	unordered_set<pair<string,int>,boost::hash<pair<string, int>>> resultSet;
	
	list<pair<string,int>> queue;
	
	visited.insert(make_pair(startVertex,true));
    
	queue.push_back(startVertex);
	


    while(!queue.empty())
    {
		strInt currVertex = queue.front();
		/*cout << "Visited " << currVertex.first << "(" << currVertex.second <<")";*/
		if(currVertex.second==3)//need to calculate the final state num
		{
			resultSet.insert(currVertex);
		}
        queue.pop_front();
		
		for(auto i = ProductMap[currVertex].adjacentVertices.begin(); i != ProductMap[currVertex].adjacentVertices.end(); ++i)
        {
			strInt adjVertex = *i;
            if(!visited[adjVertex])
            {
                visited[adjVertex] = true;
                queue.push_back(adjVertex);
            }
        }
    }
	printSet(resultSet);
	return resultSet;
}

void productGraph::printSet(unordered_set<pair<string,int>,boost::hash<pair<string, int>>> mySet)
{
	for (auto it = mySet.cbegin(); it != mySet.cend(); it++) {
		std::cout << it->first << '\n';
    }
}