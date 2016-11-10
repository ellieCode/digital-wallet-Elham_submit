/*
 * adjList.h
 *
 *  Created on: Nov 6, 2016
 *      Author: Ellie
 */

#ifndef ADJACENCYLIST_H_
#define ADJACENCYLIST_H_

#include <iostream>		//std::cerr
#include <vector>		//List of connected nodes
#include <string>	    //std::string, std::stoi
#include <unordered_map>//AdjList container
#include <sstream>      // std::istringstream
#include <fstream>      // std::ofstream
#include <algorithm>    //std::find

#include "CSVhandler.h"

using namespace std;

//We assumed ids are valid unsigned integer values
//
struct node{
	unsigned int id;
	bool visited;
	node(int i):id(i),visited(false) {}
};

typedef unordered_map <unsigned int, std::vector<unsigned int>> myAdjList;

class AdjacencyList {
private:
	myAdjList adjList;

public:
	//Constructor, empty adjacency list
	AdjacencyList();

	//Constructor,create the adjacency list from the input file
	AdjacencyList(string filename);

	//Check trusted/unverified status
	void checkTrusted(string infilename,string outfilename);

	//prints the adjList, for debugging purposes
	void print();

	//return a pointer to adjList, used for Graph creation
	myAdjList* getAdjList();

	//destructor
	virtual ~AdjacencyList();
};

#endif /* ADJACENCYLIST_H_ */
