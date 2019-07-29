#include "graph.h"

using namespace std;

typedef pair<string, string> edgePairs; 
typedef pair<int, int> pairs; 
typedef pair<string,int> strInt;

int index(const vector<pair<string,vector<string>>> & listOfElements, const string str)
{// returns to the index of the specific element
    int i =0;
    for(; i<listOfElements.size();i++)
    {
        if(listOfElements[i].first==str)
            return i;
    }
    return i;
}

bool contains(const vector<pair<string,vector<string>>> & listOfElements, const string str)
{//checks if the element is already in the data structure
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

void productGraph::buildPG(graph g, automata q)
{// builds the cartesian product of automata and graph
	int f; // first int
	int s; // second int
	string fstr; // first string
	string sstr; // second string
	for (const auto& it : q.map1) // automata graph traversal
	{
		for (auto itr = q.map1[it.first].VertexSetautomata.begin(); itr != q.map1[it.first].VertexSetautomata.end(); ++itr) 
		{ // automata graph states traversal
			f = itr->first;
			s = itr->second;
			for (auto itx = g.adjList[it.first].VertexSetgraph.begin(); itx != g.adjList[it.first].VertexSetgraph.end(); ++itx) 
			{ // relation graph traversal
				fstr = itx->first;
				sstr = itx->second;
				strInt p1 = make_pair(fstr,f);
				strInt p2 = make_pair(sstr,s);
				adjVert temp;
				temp.adjacentVertices.insert(p2);
				if(ProductMap.count(p1))// if it is already in the product graph
				{
					ProductMap[p1].adjacentVertices.insert(p2);
				}
				else// if it is not in the product graph
				{
					ProductMap.insert(make_pair(p1,temp));
				}
			} 
		}
	}
}

unordered_set<pair<string,int>,boost::hash<pair<string, int>>> productGraph::results(pair<string,int> startVertex, int maxState)
{
	unordered_map<pair<string,int>,bool,boost::hash<pair<string, int>>> visited;

	unordered_set<pair<string,int>,boost::hash<pair<string, int>>> resultSet;
	
	list<pair<string,int>> queue;
	
	visited.insert(make_pair(startVertex,true));
    
	queue.push_back(startVertex);
	
    while(!queue.empty())
    {
		strInt currVertex = queue.front();
		if(currVertex.second==maxState)
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
    cout << "---" << endl;
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
            vertexNum++;
            for (auto itx = g.adjList[it.first].VertexSetgraph.begin(); itx != g.adjList[it.first].VertexSetgraph.end(); ++itx)
            {
                fstr = itx->first;
                sstr = itx->second;
                string a1=to_string(f);
                string a2=to_string(s);
                string str1 = fstr+a1;
                string str2 = sstr+a2;
                addEdge(str1, str2);
                neighborNum++;
                vertexNum++;
            }
        }
    }
}

void adjListVect::results(string vertex1, int maxState)
{
    unordered_map<string,bool> visited;
    
    list<string> queue;
    
    visited.insert(make_pair(vertex1,true));
    
    queue.push_back(vertex1);
    
    vector<string> resultArr;
    
    char c = '0';
    
    while(!queue.empty())
    {
        string currVertex = queue.front();
        if(currVertex.at(currVertex.length()-1)==(c + maxState))
        {
            resultArr.push_back(currVertex.substr(0,currVertex.length()-1));
        }
        queue.pop_front();
        
        int t = index(adjVect,currVertex);
    
        for(auto i = adjVect[t].second.begin(); i != adjVect[t].second.end() && t != adjVect.size() ; ++i)
        {
            string adjVertex = *i;
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
    cout << "---" << endl;
}

CSR::CSR(int n, int m) {
    this -> n = n;
    this -> m = m;
    indices = new int[n];
    CSRmatrix = new int[m];
    inverted = new string[n];
    visited = new bool[n];
    for(int i=0; i<n; i++)
    {
        visited[i]=false;
    }
}

void CSR::getInterval(int currvertex, int & start, int & end)
{
    start = indices[currvertex];
    end = indices[currvertex+1];
}

void CSR::buildMap(adjListVect v)
{
    for(int i=0; i< v.adjVect.size();i++)
    {
        if(mapValues.count(v.adjVect[i].first))
        {
            
        }
        else
        {
            // this vertex has an outgoing edge
            mapValues.insert(make_pair(v.adjVect[i].first, count));
            inverted[count] = (v.adjVect[i].first);
            count++;
        }
        
    }
    for(int i=0; i< v.adjVect.size();i++)
    {
        for(int j=0; j<v.adjVect[i].second.size();j++)
        {
            if(mapValues.count(v.adjVect[i].second[j]))
            {
            }
            else
            {
                // this vertex has no outgoing edge, has already been assigned an id previously
                mapValues.insert(make_pair(v.adjVect[i].second[j], count));
                inverted[count]=(v.adjVect[i].second[j]);
                count++;
            }
        }
    }
}

void CSR::buildIndexArr(adjListVect v)
{
    int currIndex = 0;
    
    for(size_t i = 0; i < v.adjVect.size(); i++)
    {
        indices[i] = currIndex;
        currIndex += v.adjVect[i].second.size();
    }
    
    // for vertex that do not have outgoing edges
    for(size_t i = v.adjVect.size(); i < n ; i++) {
        indices[i] = currIndex;
    }
}

void CSR::buildCSR(adjListVect v)
{
    int index = 0;
    for(size_t i=0; i<v.adjVect.size();i++)
    {
        for(size_t j=0; j<v.adjVect[i].second.size();j++)
        {
            CSRmatrix[index++] = (mapValues[v.adjVect[i].second[j]]);
        }
    }
}

void CSR::results(string vertex1, int maxState)// BFS traversal on product graph
{
    int edge = mapValues[vertex1];
    
    list<int> queue;
    
    visited[edge] = true;
    
    queue.push_back(edge);
    
    vector<string> resultArr;
    
    int start = 0;
    
    int end = 0;
    
    char c = '0';
    
    while(!queue.empty())
    {
        int currVertex = queue.front();
        if(inverted[currVertex].at(inverted[currVertex].length()-1)==(c + maxState) )
        {
            resultArr.push_back(inverted[currVertex].substr(0,inverted[currVertex].length()-1));
        }
        queue.pop_front();
        
        getInterval(currVertex,start,end);
        
        for( ; start < end ; start++)
        {
            int adjVertex = CSRmatrix[start];
            if(!visited[adjVertex])
            {
                visited[adjVertex] = true;
                queue.push_back(adjVertex);
            }
        }
    }
    printArr(resultArr);
   
}

void CSR::printArr(vector<string> arr)// prints the result array
{
    for(int i=0; i<arr.size();i++)
    {
        cout << arr[i] << endl;
    }
    cout << "---" << endl;
}
