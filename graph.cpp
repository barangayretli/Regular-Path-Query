#include "graph.h"

using namespace std;

typedef pair<string, string> edgePairs; 
typedef pair<int, int> pairs; 
typedef pair<string,int> strInt;


int index(const vector<pair<string,vector<string>>> & listOfElements, const string str)
{
    int i =0;
    for(; i<listOfElements.size();i++)
    {
        if(listOfElements[i].first==str)
            return i;
    }
    return i;
}

bool contains(const vector<pair<string,vector<string>>> & listOfElements, const string str)
{
    for(int i =0; i<listOfElements.size();i++)
    {
       if(listOfElements[i].first==str)
           return true;
    }
    return false;
}

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
	for (const auto& it : q.map1)
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

void adjListVect::addEdge(string edge1, string edge2)
{
    
    
    bool exist = contains(adjVect, edge1);
    
    if(exist){
        int t = index(adjVect,edge1);
        adjVect[t].second.push_back(edge2);
    }
    else{
        vector<string>temp;
        temp.push_back(edge2);
        adjVect.push_back(make_pair(edge1,temp));
    }
}

void adjListVect::buildPG(graph g, automata q)
{
    int f;
    int s;
    string fstr;
    string sstr;
    for (const auto& it : q.map1)
    {
        
        for (auto itr = q.map1[it.first].VertexSetautomata.begin(); itr != q.map1[it.first].VertexSetautomata.end(); ++itr)
        {
            f = itr->first;
            s = itr->second;
            for (auto itx = g.adjList[it.first].VertexSetgraph.begin(); itx != g.adjList[it.first].VertexSetgraph.end(); ++itx)
            {
                fstr = itx->first;
                sstr = itx->second;
                string a1=to_string(f);
                string a2=to_string(s);
                string str1 = fstr+a1;
                string str2 = fstr+a2;
                addEdge(str1, str2);
            }
        }
    }
}

void adjListVect::results(string edge1)
{
    unordered_map<string,bool> visited;
    
    list<string> queue;
    
    visited.insert(make_pair(edge1,true));
    
    queue.push_back(edge1);
    
    vector<string> resultArr;
    
    while(!queue.empty())
    {
        string currVertex = queue.front();
        /*cout << "Visited " << currVertex.first << "(" << currVertex.second <<")";*/
        if(currVertex.at(currVertex.length()-1)=='3')//need to calculate the final state num
        {
            resultArr.push_back(currVertex.substr(0,currVertex.length()-1));
        }
        queue.pop_front();
        
        for(auto i = 0; i < adjVect.size(); ++i)
        {
            string adjVertex = adjVect[i].first;
            if(!visited[adjVertex])
            {
                visited[adjVertex] = true;
                queue.push_back(adjVertex);
            }
        }
    }
    printArr(resultArr);
    
}

void adjListVect::printArr(vector<string> arr)
{
    for(int i=0; i<arr.size();i++)
    {
        cout << arr[i] << endl;
    }
}
