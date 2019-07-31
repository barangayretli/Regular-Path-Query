#include "graph.h"

using namespace std;

typedef pair<string,int> strInt; // vertex name and state

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

void printArr(vector<string> arr)// prints the result array
{
    for(int i=0; i<arr.size();i++)
    {
        cout << arr[i] << endl;
    }
    cout << "---" << endl;
}


void productGraph::addEdge(automata q, string start, string label, string end)
{
    int f; // first int
    int s; // second int
    string fstr; // first string
    string sstr; // second string
    for (auto itr = q.automataGraph[label].VertexNeighbors.begin(); itr != q.automataGraph[label].VertexNeighbors.end(); ++itr)
    { // automata graph states traversal
        f = itr->first;
        s = itr->second;
        fstr = start;
        sstr = end;
        strInt p1 = make_pair(fstr,f);
        strInt p2 = make_pair(sstr,s);
        adjVert temp;
        temp.adjacentVertices.push_back(p2);
        if(ProductMap.count(p1))// if it is already in the product graph
        {
            ProductMap[p1].adjacentVertices.push_back(p2);
            neighborNum++;
        }
        else// if it is not in the product graph
        {
            ProductMap.insert(make_pair(p1,temp));
            vertexNum++;
            neighborNum++;
        }
        
    }
}
vector<pair<string,int>> productGraph::getVertex0()
{
    vector<pair<string,int>> arr;
    for (auto it = ProductMap.begin(); it != ProductMap.end(); ++it)
    {
        if(it->first.second == 0)
            arr.push_back(it->first);
    }
    return arr;
}

void productGraph::BFS(pair<string,int> startVertex, int maxState, int & vertexNumCheck)
{
	unordered_map<pair<string,int>,bool,boost::hash<pair<string, int>>> visited; // hash table to check if a vertex is visited

	//vector<pair<string,int>> resultSet; // resulting set
	
	list<pair<string,int>> queue; // queue to store neighbors
	
	visited.insert(make_pair(startVertex,true)); // make the starting vertex visited
    
	queue.push_back(startVertex); // push the starting vertex
	
    while(!queue.empty()) // as long as queue is not empty, continue
    {
		strInt currVertex = queue.front(); // current vertex is the front of the queue
		if(currVertex.second==maxState) // if the state is maximum, add the vertex to the result array
		{
			//resultSet.push_back(currVertex);
            vertexNumCheck++;
		}
        queue.pop_front();
		
		for(auto i = ProductMap[currVertex].adjacentVertices.begin(); i != ProductMap[currVertex].adjacentVertices.end(); ++i)
        {// take the neighbors and check if they are visited
			strInt adjVertex = *i;
            if(!visited[adjVertex])// if the vertes is not visited
            {
                visited[adjVertex] = true;
                queue.push_back(adjVertex); // push the neighbor to the queue
            }
        }
    }
    cout << vertexNumCheck << " vertices found with max State"<< endl;
	//printArr(resultSet);// print the result array
}

void productGraph::printArr(vector<pair<string,int>> resultArr)
{// prints the result array
	for (auto it = resultArr.cbegin(); it != resultArr.cend(); it++) {
		std::cout << it->first << '\n';
    }
    cout << "---" << endl;
}
/*
void adjListVect::addEdge(string edge1, string edge2)
{
    bool exist = contains(adjVect, edge1);
    
    if(exist){ // if the starting edge exist before
        int t = index(adjVect,edge1);
        adjVect[t].second.push_back(edge2);// add ending edge to the adjacent vertices
        neighborNum++;
    }
    else{ // if the starting edge does not exist before
        vector<string>temp;
        temp.push_back(edge2);
        adjVect.push_back(make_pair(edge1,temp)); // create an entry for starting edge and add ending edge to the adj vertices
        neighborNum++;
        vertexNum++;

    }
}

void adjListVect::buildProductGraph(automata q, string start, string label, string end)
{
    int f; // first int
    int s; // second int
    string fstr; // first string
    string sstr; // second string
    for (auto itr = q.automataGraph[label].VertexNeighbors.begin(); itr != q.automataGraph[label].VertexNeighbors.end(); ++itr)
    { // loop for automata graph states traversal
        f = itr->first;
        s = itr->second;
        fstr = start;
        sstr = end;
        string a1=to_string(f);
        string a2=to_string(s);
        string str1 = fstr+a1;
        string str2 = sstr+a2;
        addEdge(str1, str2);
    }
}

vector<string> adjListVect::getVertex0(int maxState)
{
    char maxS = '0';
    vector<string> arr;
    for(int i = 0; i < adjVect.size(); i++)
    {
        if(adjVect[i].first.at(adjVect[i].first.length()-1) == maxS)
        {
            arr.push_back(adjVect[i].first);
        }
    }
    return arr;
}

void adjListVect::BFS(string vertex1, int maxState, int & vertexNumCheck)
{
    unordered_map<string,bool> visited; // map to check if the vertex is visited before
    
    list<string> queue; // queue to store the adjacent vertices
    
    visited.insert(make_pair(vertex1,true)); // make the starting vertex visited
    
    queue.push_back(vertex1); // add first vertex to the queue
    
    //vector<string> resultArr;
    
    char c = '0';
    
    while(!queue.empty())
    {
        string currVertex = queue.front();
        if(currVertex.at(currVertex.length()-1)==(c + maxState))
        {
           // resultArr.push_back(currVertex.substr(0,currVertex.length()-1));
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
   // printArr(resultArr);
    
}
*/

CSR::CSR(int n, int m) {
    this -> n = n;// vertex number
    this -> m = m;// neighbor number
    indices = new int[n]; // dynamically create indices array
    CSRmatrix = new int[m]; // dynamically create CSR matrix array
    inverted = new string[n]; // dtnamically create inverted array
}

void CSR::setFalse()
{
    for(int i=0; i<n; i++)
    {
        visited[i]=false; // set all the elements of the visited array false
    }
}

vector<string> CSR::getVertex0()
{
    return Vertex0;
}

void CSR::getInterval(int currvertex, int & start, int & end)
{// change the start and end variables to store beginning and ending points
    start = indices[currvertex];
    end = indices[currvertex+1];
}

void CSR::buildMap(productGraph p)
{
    string str;
    for(auto it = p.ProductMap.begin(); it != p.ProductMap.end();it++)
    {
        
        str = it->first.first + to_string(it->first.second);
        if(it->first.second==0)
        {
            Vertex0.push_back(str);
        }
        if(mapValues.count(str))
        {
            
        }
        else
        {
            // this vertex has an outgoing edge
            mapValues.insert(make_pair(str, count));
            inverted[count] = (str);
            count++;
        }
        
    }
    for(auto it = p.ProductMap.begin(); it != p.ProductMap.end();it++)
    {
        for(auto itr = it->second.adjacentVertices.begin(); itr !=it->second.adjacentVertices.begin();itr++)
        {
            str = itr->first + to_string(itr->second);
            if(mapValues.count(str))
            {
            }
            else
            {
                // this vertex has no outgoing edge, has already been assigned an id previously
                mapValues.insert(make_pair(str, count));
                inverted[count]=(str);
                count++;
            }
        }
    }
}

void CSR::buildIndexArr(productGraph p)
{
    int currIndex = 0;
    
    int i=0;
    
    for(auto it = p.ProductMap.begin(); it != p.ProductMap.end();it++)
    {
        indices[i] = currIndex;
        currIndex += it->second.adjacentVertices.size();
        i++;
    }
    
    // for vertex that do not have outgoing edges
    for(size_t x = i; x < n ; x++) {
        indices[x] = currIndex;
        x++;
    }
}

void CSR::buildCSR(productGraph p)
{
    int index = 0;
    string str;
    for(auto it = p.ProductMap.begin(); it != p.ProductMap.end();it++)
    {
        for(auto itr = it->second.adjacentVertices.begin(); itr !=it->second.adjacentVertices.begin();itr++)
        {
            str = itr->first + to_string(itr->second);
            CSRmatrix[index++] = (mapValues[str]); // add the neighbor to the CSR matrix
        }
    }
}

void CSR::BFS(string vertex1, int maxState, int & vertexNumCheck)
{
    int startVertex = mapValues[vertex1]; // int value of starting edge
    
    list<int> queue; // queue to store the neighbors
    
    visited = new bool[n];
    
    setFalse();
    
    visited[startVertex] = true; // make the first edge visited
    
    queue.push_back(startVertex);
    
    //vector<string> resultArr; // result array
    
    int start = 0; // starting index
    
    int end = 0; // ending index
    
    char c = '0';
    
    while(!queue.empty())
    {
        int currVertex = queue.front();
        if(inverted[currVertex].at(inverted[currVertex].length()-1)==(c + maxState) )
        {
            //resultArr.push_back(inverted[currVertex].substr(0,inverted[currVertex].length()-1));
            vertexNumCheck++;
        }
        queue.pop_front();
        
        getInterval(currVertex,start,end); // get the starting and ending points
        
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
    cout << vertexNumCheck << " vertices found with max State"<< endl;
    //printArr(resultArr);
    delete visited;
}
