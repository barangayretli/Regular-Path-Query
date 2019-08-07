#include "graph/graph.h"

using namespace std;
using namespace std::chrono;

typedef high_resolution_clock Clock;
typedef Clock::time_point ClockTime;
typedef pair<string,int> strInt; // vertex name and state


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

void productGraph::BFS(pair<string,int> startVertex, int maxState, int & vertexNumCheck, duration<long long, ratio<1, 1000000000> > & visitedTime, duration<long long, ratio<1, 1000000000> > & ifCheckTime)
{
    ClockTime startVisited = Clock::now();
    

    unordered_map<pair<string,int>,bool,boost::hash<pair<string, int>>> visited; // hash table to check if a vertex is visited
    
    ClockTime endVisited = Clock::now();
    
    visitedTime+=(endVisited-startVisited);
    //vector<pair<string,int>> resultSet; // resulting set
    
    list<pair<string,int>> queue; // queue to store neighbors
    
    visited.insert(make_pair(startVertex,true)); // make the starting vertex visited
    
    queue.push_back(startVertex); // push the starting vertex
    
    while(!queue.empty()) // as long as queue is not empty, continue
    {
        bool check = false;

        strInt currVertex = queue.front();// current vertex is the front of the queue
        ClockTime endIfcheck = Clock::now();
        ClockTime startIfcheck = Clock::now();
        if(currVertex.second==maxState) // if the state is maximum, add the vertex to the result array
        {
            endIfcheck = Clock::now();
            //resultSet.push_back(currVertex);
            vertexNumCheck++;
            check = true;
        }
        if(check==false)
        {
            endIfcheck = Clock::now();
            ifCheckTime+=(endIfcheck-startIfcheck);
        }
        else
        {
            ifCheckTime+=(endIfcheck-startIfcheck);
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
    //printArr(resultSet);// print the result array
}

void productGraph::printArr(vector<pair<string,int>> resultArr)
{// prints the result array
    for (auto it = resultArr.cbegin(); it != resultArr.cend(); it++) {
        std::cout << it->first << '\n';
    }
    cout << "---" << endl;
}


CSR::CSR(int n, int m) {
    this -> n = n;// vertex number
    this -> m = m;// neighbor number
    indices = new int[n+1]; // dynamically create indices array
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
        for(auto itr = it->second.adjacentVertices.begin(); itr !=it->second.adjacentVertices.end();itr++)
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
    indices[i] = currIndex;
    i++;
    
    // for vertex that do not have outgoing edges
    for(; i < n + 1 ; i++) {
        indices[i] = currIndex;
    }
}

void CSR::buildCSR(productGraph p)
{
    int index = 0;
    string str;
    for(auto it = p.ProductMap.begin(); it != p.ProductMap.end();it++)
    {
        for(auto itr = it->second.adjacentVertices.begin(); itr != it->second.adjacentVertices.end();itr++)
        {
            str = itr->first + to_string(itr->second);
            CSRmatrix[index++] = (mapValues[str]); // add the neighbor to the CSR matrix
        }
    }
}

void CSR::BFS(string vertex1, int maxState, int & vertexNumCheck, duration<long long, ratio<1, 1000000000> > & visitedTime, duration<long long, ratio<1, 1000000000> > & ifCheckTime)
{
    int startVertex = mapValues[vertex1]; // int value of starting edge
    
    list<int> queue; // queue to store the neighbors
   
    unordered_map<int,bool> visited; // hash table to check if a vertex is visited
  
    visited[startVertex] = true; // make the first edge visited
    
    queue.push_back(startVertex);
    
    int start = 0; // starting index
    
    int end = 0; // ending index
    
    char c = '0';
    
    while(!queue.empty())
    {
        
        int currVertex = queue.front();

        if(inverted[currVertex].at(inverted[currVertex].length()-1)==(c + maxState) )
        {     
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
    
    //printArr(resultArr);
    //free(visited);
}
