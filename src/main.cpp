#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include "graph/graph.h"

using namespace std;
using namespace std::chrono;

typedef high_resolution_clock Clock;
typedef Clock::time_point ClockTime;

void printExecutionTime(ClockTime start_time, ClockTime end_time);
void traverseCSR(vector<string> vertices0, CSR *c, int maxState, int & vertexNumCheck, unsigned long & memory);
void constructCSR(productGraph *p, CSR *c, vector<string> & vertices_CSR0);

int main(int argc, char *argv[]){

	if(argc < 3) {
		cout << "Supply graph file and automata file as arguments" << endl;
		exit(0);
	}
	if(argc < 5) {
		cout << "Supply both line limit and interval size as arguments" << endl;
		exit(0);
	}
    
    ifstream graphRead, automataFile;
    
    graphRead.open(argv[1]);
    automataFile.open(argv[2]);
    
    int lineLimit;
    sscanf(argv[3], "%d", &lineLimit);
    int intervalSize;
    sscanf(argv[4], "%d", &intervalSize);
   
    vector<string> vertices_CSR0;
	
    string start,edge,target,f,s,label; // variables to store automata and graph vertices and labels
    int maxState = 0,first,second, vertexNumCheck=0;
    
    automata au;
    
    while(automataFile >> f >> label >> s)// reading automata from a txt file
    {
        first = stoi(f);
        second = stoi(s);
        au.addEdge(first, label, second);
        if(first > maxState)
            maxState = first;
        if(second > maxState)
            maxState = second;
    }
    automataFile.close();
    
    productGraph *p = new productGraph; // dynamically create product graph
    unsigned long memory = 0;
    int edgeCounter = 0;
    unsigned long PGedgeNumber = 0;
	
    string line;// line that stores the edge
    string temp;// temporary variable to store string
    int stringNum = 0;
    while(getline(graphRead, line) && edgeCounter < lineLimit) // reading the vertices and edges line by line from the txt file
    {
        istringstream iss(line); // take the edge as a string
        while ((iss >> temp))
        {
            if(stringNum == 0)
            {
                start = temp;
            }
            else if (stringNum == 1)
            {
                edge = temp;
            }
            else if (stringNum == 2)
            {
                target = temp;
            }
            stringNum++;
        }
        if(stringNum == 3)// only use lines with three string, as they define a valid edge 
        {
            p->addEdge(au, start, edge, target);
            edgeCounter++;
            if(edgeCounter%intervalSize == 0)
	    {
		memory = 0;
		vertexNumCheck = 0;
                memory += p->vertexNum * sizeof(int) + p->neighborNumCSR * sizeof(int);
		    
                cout << "Started building CSR" << endl;
		    
                CSR *c = new CSR(p->uniqueVertexSet.size(),p->neighborNumCSR);// CSR Constructor
                constructCSR(p, c, vertices_CSR0);// build indexarray, map and CSR matrix
		    
                cout << "Finished building CSR" << endl;
		 
		traverseCSR(vertices_CSR0,c,maxState,vertexNumCheck, memory);
		memory += vertices_CSR0.size()*(c->MapValuesSize/(p->vertexNum + p->neighborNumCSR));
		    
		PGedgeNumber = p->edgeNumber;
		cout << "There are " << PGedgeNumber << " edges in the Product Graph" <<endl;
		int VertexNum = p->vertexNum + p->uniqueNeighbor;
    		cout << "There are " << VertexNum << " vertices in the Product Graph" << endl;
                cout <<edgeCounter<<endl;
		delete c;
	    }     
        }
        stringNum = 0;
    }
    
    return 0;
}

void printExecutionTime(ClockTime start_time, ClockTime end_time)
{
    auto execution_time_ms = duration_cast<microseconds>(end_time - start_time).count();
    auto execution_time_mls = duration_cast<milliseconds>(end_time-start_time).count();
    auto execution_time_sec = duration_cast<seconds>(end_time - start_time).count();
    auto execution_time_min = duration_cast<minutes>(end_time - start_time).count();
    auto execution_time_hour = duration_cast<hours>(end_time - start_time).count();
    
    cout << "Execution Time: ";
    if(execution_time_hour > 0)
        cout << "" << execution_time_hour << " Hours, ";
    if(execution_time_min > 0)
        cout << "" << execution_time_min % 60 << " Minutes, ";
    if(execution_time_sec > 0)
        cout << "" << execution_time_sec % 60 << " Seconds, ";
    if(execution_time_sec > 0)
        cout << "" << execution_time_mls % long(1000) << " MiliSeconds, ";
    if(execution_time_ms > 0)
        cout << "" << execution_time_ms << " MicroSeconds, ";
    
}

void traverseCSR(vector<string> vertices0, CSR *c, int maxState, int & vertexNumCheck,  unsigned long & memory)
{
    ClockTime start_time, end_time;
    start_time = Clock::now();
		    
    for(unsigned int j = 0; j < vertices0.size(); j++)
    {
    	c->BFS(vertices0[j],maxState,vertexNumCheck);
    }
		    
    end_time = Clock::now();
		    
    memory += c->MapValuesSize + c->maxMapSize;
		    
    cout << "CSRmatrix representation ";
    printExecutionTime(start_time, end_time);
    cout << endl;
    cout << "Memory used by CSR representation is " << memory/(1024*1024) << " MB" << endl;
   
    cout << vertexNumCheck << " results found with max State"<< endl;
	 
    cout << "There are " << vertices0.size() << " vertices with 0 state"<<endl;
}

void constructCSR(productGraph *p, CSR *c, vector<string> & vertices_CSR0)
{
	c->buildMap(p);// Maps strings to integers
                
        vertices_CSR0 = c->getVertex0(); // get vertices with 0 state in a vector
		    
        c->buildIndexArr(p);// build index array of CSR
                
        c->buildCSR(p);// build CSR matrix where we store the neighbors
}
