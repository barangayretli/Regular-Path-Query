#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>
#include <ostream>
#include <boost/optional.hpp>
#include "graph.h"	
#include <hash_set>
#include <unordered_map>

using namespace std;

struct relation{
	string start;
	string edge;
	string target;
};


int main(){

	

	
	ifstream myReadFile;
	struct temp;
	vector<relation> container;
	myReadFile.open("relations.txt");
	string start;
	string edge;
	string target;
	while(myReadFile>>start>>edge>>target)
	{
		relation temp;
		temp.start=start;
		temp.edge=edge;
		temp.target=target;
		container.push_back(temp);
	}

	graph g;
	for(unsigned int i=0; i<container.size();i++)
	{

		g.addEdge(container[i].start,container[i].edge,container[i].target);

	}
	
	

	return 0;
}

