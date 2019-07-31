CXX = g++
CXXFLAGS = -std=c++11 -Wall -g -Isrc

rpq: automata graph
	$(CXX) $(CXXFLAGS) -o rpq src/main.cpp automata.o graph.o

automata: 
	$(CXX) $(CXXFLAGS) -c src/automata/automata.cpp

graph:
	$(CXX) $(CXXFLAGS) -c src/graph/graph.cpp
