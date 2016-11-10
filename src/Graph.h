/*
 * Graph.h
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include "AdjacencyList.h"
#include <list>
#include <string>

class Graph {
private:
	myAdjList* adjList;

	//returns whether dest is within k distance from src
	bool BFS(unsigned int src, unsigned int dest, int depth);

public:
	//Constructor
	Graph(AdjacencyList* adjList);
	//Default destructor
	virtual ~Graph();

	//given a depth (say depth=2 means friends of friend) checks wether a transaction is trusted or not
	void checkTrusted(string infilename, string outfilename, int depth);


};

#endif /* GRAPH_H_ */
