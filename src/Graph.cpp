/*
 * Graph.cpp
 *
 *  Created on: Nov 7, 2016
 *      Author: Elham sakhaee
 */

#include "Graph.h"


Graph::Graph(AdjacencyList* al){
	adjList = al->getAdjList();
}

//evaluate whether src(id1) and dest(id2) are within k distance from each other
//Note: k=1 means the are friends, k=2 means friend of friends
//We check the output of k=1 with the one from Adjacency List
bool Graph::BFS(unsigned int src, unsigned int dest, int k)
{
	//insert a dummy node to keep track of level change
	unsigned int dummy = -1;

	//initialize the breadth distance
	int depth = 0;

	// Mark all the vertices as not visited
	//vector<bool> visited(graphSz, false);
	unordered_map <int, bool> visited;

	// Create two queue for BFS
	list<unsigned int> Queue;

	// Mark the current node as visited and enqueue it
	visited[src] = true;
	Queue.push_back(src);
	Queue.push_back(dummy);


	// 'i' will be used to get all adjacent vertices of a vertex
	vector<unsigned int>::iterator i;


	while(!Queue.empty() && depth <= k)
	{
		// Dequeue a vertex from queue and check if it is the dest node
		src = Queue.front();
		Queue.pop_front();

		if (src == dummy){
			depth++;
			Queue.push_back(dummy);
		}else{
			if (src == dest){   //this also means that transfer from id1 to id1 is valid
				return true;
			}

			// Get all adjacent vertices of the dequeued vertex s
			// If a adjacent has not been visited, then mark it visited
			// and enqueue it
			if(depth<k){
				vector<unsigned int> ngbrs(adjList->at(src)); //copy the list into vector to avoid accessing the map every time
				for(i = ngbrs.begin(); i !=  ngbrs.end(); ++i)
					//for(int j = 0; j < ngbrs.size(); j++)
				{
					//this is slightly more efficient
					//if(!visited[ngbrs[j]]){
					//	visited[ngbrs[j]] = true;
					//	inactiveQueue.push_back(ngbrs[j]);
					//}
					if(!visited[*i])
					{
						visited[*i] = true;
						Queue.push_back(*i);
					}
				}
			}
		}
	}
	return false;
}

void Graph::checkTrusted(string infilename, string outfilename, int depth){

	CSVhandler input (infilename, 'r');
	CSVhandler output (outfilename , 'w');

	//Skip the header line of input
	string line = input.readLine();
	line = input.readLine();

	//Get ids extracted from lineTokenizer
	vector <string> ids (2,"");

	unsigned int id1, id2;
	while(!line.empty()){
		ids = input.LineTokenizer(line);
		//Make sure ids are valid values unsigned int values
		try {id1 = (unsigned int) stoul (ids[0]);}
		catch(...) {
			cerr << "Id1 (sender): "<< id1 << " is not valid or is too long" <<endl;
		}
		try {id2 =  (unsigned int) stoul(ids[1]);}
		catch(...) {
			cerr << "Id2 (receiver): "<< id2 << " is not valid or is too long" <<endl;
		}

		if (adjList->count(id1)){
			if (BFS(id1, id2, depth))
				output.writeLine("trusted");
			else
				output.writeLine("unverified");
		}else{										//If this id has never had a transaction before
			if(id1 == id2)   						//but transaction with oneself is always trusted
				output.writeLine("trusted");
			else
				output.writeLine("unverified");
		}
		line = input.readLine();
	}
}

Graph::~Graph() {
	//Automatic Resource Collection due to STL containers
}

