#include "graph/graph.h"

using namespace std;

typedef pair<string,int> strInt; // vertex name and state


void printArr(vector<string> arr)// prints the result array
{
    for(unsigned int i=0; i<arr.size();i++)
    {
        cout << arr[i] << endl;
    }
    cout << "---" << endl;
}


void productGraph::addEdge(automata q, string start, string label, string end)
{
    int f; // state of first edge
    int s; // state of second edge
    string fstr; // first string
    string sstr; // second string
    for (auto itr = q.automataGraph[label].VertexNeighbors.begin(); itr != q.automataGraph[label].VertexNeighbors.end(); ++itr)
    { // automata graph states traversal
        edgeNumber++;
        neighborNumCSR++;
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
            
            if(neighborset.count(p2))
            {
                
            }
            else
                uniqueNeighbor++;
            neighborset.insert(p2);
            neighborset.insert(p1);
            ProductMap[p1].adjacentVertices.push_back(p2);
        }
        else// if it is not in the product graph
        {
            
            vertexNum++;
            if(neighborset.count(p2))
            {
                
            }
            else
                uniqueNeighbor++;
            neighborset.insert(p2);
            neighborset.insert(p1);
            ProductMap.insert(make_pair(p1,temp));
        }
        
    }
}

CSR::CSR(int n, int m) {
    this -> n = n;// vertex number
    this -> m = m;// neighbor number
    indices = new int[n+1]; // dynamically create indices array
    CSRmatrix = new int[m]; // dynamically create CSR matrix array
    inverted = new string[n+m+1]; // dtnamically create inverted array
}

vector<string> CSR::getVertex0()// get vector of vertices with 0 state
{
    return Vertex0;
}


void CSR::getInterval(int currvertex, int & start, int & end)
{// change the start and end variables to store beginning and ending points
    start = indices[currvertex];
    end = indices[currvertex+1];
}

void CSR::buildMap(productGraph *p)
{
    string str;
    for(auto it = p->ProductMap.begin(); it != p->ProductMap.end();it++)
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
            MapValuesSize += sizeof(str);
            inverted[count] = (str);
            count++;
        }
        
    }
    for(auto it = p->ProductMap.begin(); it != p->ProductMap.end();it++)
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
                MapValuesSize += sizeof(str);
                inverted[count]=(str);
                count++;
            }
        }
    }
}

void CSR::buildIndexArr(productGraph *p)
{
    int currIndex = 0;
    
    int i=0;
    
    for(auto it = p->ProductMap.begin(); it != p->ProductMap.end();it++)
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

void CSR::buildCSR(productGraph *p)
{// this function creates a CSR representation from an adjacency list representation
    int index = 0;
    string str;
    for(auto it = p->ProductMap.begin(); it != p->ProductMap.end();it++)
    {// iterates through the vertices of the product graph in the adjacency list
        for(auto itr = it->second.adjacentVertices.begin(); itr != it->second.adjacentVertices.end();itr++)
        {// iterates through the outgoing edges of each vertex
            str = itr->first + to_string(itr->second);
            CSRmatrix[index++] = (mapValues[str]); // add the neighbor to the CSR matrix
        }
    }
}

void CSR::BFS(string vertex1, int maxState, int & vertexNumCheck)
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

        if(inverted[currVertex].at(inverted[currVertex].length()-1)==(c + maxState))
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
    if(((visited.size()*(MapValuesSize/n)+(visited.size()*sizeof(int))>maxMapSize)))
        maxMapSize = (visited.size()*(MapValuesSize/n)+(visited.size()*sizeof(int)));
}

CSR::~CSR()
{// destructs dynamically created CSR object
    delete []indices;
    delete []CSRmatrix;
    delete []inverted;
}
