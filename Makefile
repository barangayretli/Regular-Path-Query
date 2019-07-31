CXX = g++
CXXFLAGS = -Wall -g -Isrc

rpq: automata.o graph.o
	$(CXX) $(CXXFLAGS) -o rpq main.cpp	

automata: automata.h
	$(CXX) $(CXXFLAGS) -c automata/automata.cpp

graph: graph.h
	$(CXX) $(CXXFLAGS) -c graph/graph.cpp
