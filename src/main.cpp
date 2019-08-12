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

int main(int argc, char *argv[]){

	if(argc < 3) {
		cout << "Supply graph file and automata file as arguments" << endl;
		exit(0);
	}
    
    ifstream graphRead, automataFile;
    
    graphRead.open(argv[1]);
    automataFile.open(argv[2]);
    
    vector<string> vertices_CSR0;
	
    string start,edge,target,f,s,label;
    int maxState = 0,first,second, vertexNumCheck=0;
    ////////////////
    automata au;
    unsigned long memory = 0;
    int counter = 0;
    unsigned long PGedgeNumber = 0;
    cout << "Started reading automata" << endl;
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
    cout << "Finished reading automata" << endl;
    automataFile.close();
    /////////////////
    productGraph *p = new productGraph;
    
    cout << "Started Reading Graph" << endl;
    string line;
    string temp;
    int stringNum = 0;
    while(getline(graphRead, line)) // reading the vertices and edges line by line from the txt file
    {
        istringstream iss(line);
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
        if(stringNum == 3)
        {
            p->addEdge(au, start, edge, target);
            counter++;
            if(counter%1000000 == 0)
                cout <<counter<<endl;
        }
        stringNum = 0;
        
    }
    cout << "Finished reading Graph" << endl;
    graphRead.close();
    PGedgeNumber = p->edgeNumber;
    ////////////////
    cout << "Started building CSR" << endl;
    CSR c(p->vertexNum+p->neighborNum,p->neighborNum);
    c.buildMap(p);
    vertices_CSR0 = c.getVertex0();
    c.buildIndexArr(p);
    c.buildCSR(p);
    memory +=  p->vertexNum + p->neighborNum * sizeof(int) + p->neighborNum * sizeof(int);
    memory += vertices_CSR0.size()*(c.MapValuesSize/(p->vertexNum + p->neighborNum));
    int VertexNum = p->vertexNum + p->neighborNum;
    cout << "Finished building CSR" << endl;
    delete p;
    //////////////// CSR Matrix Representation
    
    ClockTime start_time, end_time;
    start_time = Clock::now();
    for(unsigned int j = 0; j < vertices_CSR0.size(); j++)
    {
        c.BFS(vertices_CSR0[j],maxState,vertexNumCheck);
    }
    end_time = Clock::now();
    memory += c.MapValuesSize + c.maxMapSize;
    cout << vertexNumCheck << " results found with max State"<< endl;
    cout << "There are " << VertexNum << " vertices in the Product Graph" << endl;
    cout << "There are " << PGedgeNumber << " edges in the Product Graph" <<endl;
    cout << "Memory used by CSR representation is " << memory/(1024*1024) << " MB" << endl;
    cout << "CSRmatrix representation ";
    printExecutionTime(start_time, end_time);

    return 0;
}

void printExecutionTime(ClockTime start_time, ClockTime end_time)
{
    auto execution_time_ms = duration_cast<microseconds>(end_time - start_time).count();
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
    if(execution_time_ms > 0)
        cout << "" << execution_time_ms % long(1E+3) << " MicroSeconds, ";
}
