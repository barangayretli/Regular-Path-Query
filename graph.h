#include <unordered_map>
#include <string>
#include <boost/functional/hash.hpp>
#include <list>
#include "automata.h"

class productGraph{

private:
	struct adjVert{
        std::vector<std::pair<std::string,int>> adjacentVertices; // vector of adjacent vertices of a vertex
	};	
    std::unordered_map<std::pair<std::string,int>,adjVert,boost::hash<std::pair<std::string,int>>> ProductMap; // starting vertex map
    
public:
    void printArr(std::vector<std::pair<std::string,int>>); // prints the result array
    void addEdge(automata q, std::string start, std::string label, std::string end); // adds an edge to the graph
	void BFS(std::pair<std::string,int>, int maxState, int & vertexNumCheck);// BFS on product graph
    std::vector<std::pair<std::string,int>> getVertex0 ();
};

class adjListVect{
    
private:
    std::vector<std::pair<std::string,std::vector<std::string>>>adjVect; // adjacent vertices of a vertex
    friend class CSR;
    
public:
    void addEdge(std::string edge1, std::string edge2); // adds an edge to the graph
    void buildProductGraph(automata q, std::string start, std::string label, std::string end); // builds product graph
    void BFS(std::string edge1, int maxState, int & vertexNumCheck); // BFS on product graph
    std::vector<std::string> getVertex0(int maxState);
    int vertexNum=0;
    int neighborNum=0;
    friend class CSR;
};

class CSR{
    
private:
    int n, m; // size of vertex and neighbors
    int count=0;
    int* CSRmatrix; // CSRMatrix that contains only the neighbors
    int* indices; // index of the starting vertices
    bool* visited; // boolean array to check if a vertex is visited during BFS
    std::unordered_map<std::string, int> mapValues; // map of string vertices
    std::string* inverted; // inverse of mapValues
    
public:
    CSR(int n, int m); // CSRMatrix constructor
    void buildIndexArr(adjListVect v); // Construct the index array
    void buildCSR(adjListVect v); // Construct CSR matrix
    void buildMap(adjListVect v); // Handles mapping of strings
    void BFS(std::string startVertex, int maxState, int & vertexNumCheck); // BFS on product graph
    void getInterval(int currvertex,int & start, int & end); // interval of neighbors of a vertex in CSR matrix
    void setFalse();
};
