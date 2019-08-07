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

void addExecutionTime(duration<long long, ratio<1, 1000000000>> x);
void printExecutionTime(ClockTime start_time, ClockTime end_time);

int main(int argc, char *argv[]){

	if(argc < 3) {
		cout << "Supply graph file and automata file as arguments" << endl;
		exit(0);
	}
    
    ifstream graphRead, automataFile;
    ///////////////////////
    graphRead.open(argv[1]);
    automataFile.open(argv[2]);

    ///////////////////////
    vector<pair<string,int>> vertices_ProductGraph0;
    vector<string> vertices_CSR0;
    ///////////////////////
    string start,edge,target,f,s,label;
    int maxState = 0,first,second, vertexNumCheck=0;
    ///////////////////////
    automata au;
    int counter=0;
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
    /////////////////
    productGraph p;

    /////////////////
    cout << "Started Reading Graph" << endl;
    string line;
    string temp;
    int con = 0;
    while(getline(graphRead, line)) // reading the vertices and edges line by line from the txt file
    {
        istringstream iss(line);
        vector<string> strs;
        while ((iss >> temp))
        {

            if(con == 0)
            {
                start = temp;
            }
            else if (con == 1)
            {
                edge = temp;
            }
            else if (con == 2)
            {
                target = temp;
            }

            con++;
        }
        if(con<=3)
        {
            p.addEdge(au, start, edge, target);
            // v.buildProductGraph(au, start, edge, target);
            counter++;
            if(counter%1000000 == 0)
                cout <<counter<<endl;
        }
        con = 0;
        
    }
    cout << "Finished reading Graph" << endl;
    ////////////////
    vertices_ProductGraph0 = p.getVertex0();
    
    cout << "Started building CSR" << endl;
    CSR c(p.vertexNum+p.neighborNum,p.neighborNum);
    c.buildMap(p);
    vertices_CSR0 = c.getVertex0();
    c.buildIndexArr(p);
    c.buildCSR(p);
    cout << "Finished building CSR" << endl;
    
    //////////////// CSR Matrix Representation
    ClockTime start_time;
    ClockTime end_time;
    vertexNumCheck = 0;
    start_time = Clock::now();
    for(int j = 0; j < vertices_CSR0.size(); j++)
    {
        c.BFS(vertices_CSR0[j],maxState,vertexNumCheck, visitedTime,ifCheckTime);
        
    }
    end_time = Clock::now();
    cout << vertexNumCheck << " vertices found with max State"<< endl;
  
    cout << "CSRmatrix representation ";
    printExecutionTime(start_time, end_time);

	return 0;

}

void printExecutionTime(ClockTime start_time, ClockTime end_time)
{
    auto execution_time_ns = duration_cast<nanoseconds>(end_time - start_time).count();
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
    if(execution_time_ns > 0)
        cout << "" << execution_time_ns % long(1E+6) << " NanoSeconds, \n";
}
