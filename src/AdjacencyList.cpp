/*
 * adjList.cpp
 * Implements Graph as Adjacency List
 * Reads in the batch_payment file and creates AdjList 
 * AdjList is implemented as unordered_map
 */

#include "AdjacencyList.h"

//create an empty unordered list
AdjacencyList::AdjacencyList() {
	adjList.clear();
}

//Fill in the Adjacency List given the batch_payment data
AdjacencyList::AdjacencyList(string infilename){
	adjList.clear();

	//create a CVShandler object for reading
	CSVhandler input (infilename, 'r');

	//Skip the header line
	string line = input.readLine();
	line = input.readLine();

	//to get ids extracted from LineTokenizer
	vector <string> ids(2,"");
	unsigned int id1, id2;

	//for the rest of the file tokenize ids
	while (!line.empty()){

		//TODO: for now, assume adjacency list includes ids not nodes
		ids = input.LineTokenizer(line);

		//Make sure ids are valid values
		try {id1 = (unsigned int) stoul(ids[0]);}
		catch(...) {
			cerr << "Id1 (sender): "<< id1 << " is not valid" <<endl;
		}
		try {id2 =  (unsigned int) stoul(ids[1]);}
		catch(...) {
			cerr << "Id2 (receiver): "<< id2 << " is not valid" <<endl;
		}

		//insert ids and their connected nodes to the adjacency list
		if (adjList.count(id1)) { // if key already exists
			//Avoid duplicates by checking if id2 is already in the list of id1
			if(find(adjList.at(id1).begin(), adjList.at(id1).end(), id2) == adjList.at(id1).end()){
				adjList.at(id1).push_back(id2);
			}
		} else {
			//if key doesn't exist, create the key first
			adjList.insert(std::make_pair(id1, std::vector<unsigned int>()));
			adjList.at(id1).push_back(id2);
		}

		//since this is an undirected graph, id1-id2 is the same as id2-id1
		//therefore, we should insert both
		if (adjList.count(id2)) {
			//Avoid duplicates by checking if id2 is already in the list of id1
			if(find(adjList.at(id2).begin(), adjList.at(id2).end(), id1) == adjList.at(id2).end()){
				adjList.at(id2).push_back(id1);
			}
		} else {
			adjList.insert(std::make_pair(id2, std::vector<unsigned int>()));
			adjList.at(id2).push_back(id1);
		}

		line = input.readLine();
	}


}

//Given stream file data, check which transaction is trusted and which is unverified
//write the result to outFilename
void AdjacencyList::checkTrusted(string infilename, string outfilename){

	CSVhandler input (infilename, 'r');
	CSVhandler output (outfilename , 'w');

	//skip the header line of input
	string line = input.readLine();
	line = input.readLine();

	//To get ids extracted from lineTokenizer
	vector <string> ids (2,"");
	unsigned int id1, id2;
	while(!line.empty()){
		ids = input.LineTokenizer(line);

		//Make sure ids are valid values
		try {id1 = (unsigned int) stoul(ids[0]);}
		catch(...) {
			cerr << "Id1 (sender): "<< id1 << " is not valid or is too long" <<endl;
		}
		try {id2 = (unsigned int) stoul(ids[1]);}
		catch(...) {
			cerr << "Id2 (receiver): "<< id2 << " is not valid or is too long" <<endl;
		}

		//We assume transaction with oneself is trusted no matter if appears in the graph or not
		if (id1 == id2){
			output.writeLine("trusted");

		}else{
			if (adjList.count(id1) ){//To catch and handle out-of-range exception

				//check if id2 exists in the connected ngbrs of id1
				if (find(adjList.at(id1).begin(), adjList.at(id1).end(), id2) != adjList.at(id1).end() )
					output.writeLine("trusted");
				else
					output.writeLine("unverified");
			}
			//If id1 or id2 has no transactions with any one else before
			else{
				output.writeLine("unverified");
			}
		}
		line = input.readLine();
	}
}

myAdjList* AdjacencyList::getAdjList(){
	return &adjList;
}


//show the adjacency list for error checking
void AdjacencyList::print(){
	for ( auto it = adjList.begin(); it != adjList.end(); ++it ){
		cout << " " << it->first << "-->";
		for(vector<unsigned int>::iterator vIter = (it->second).begin(); vIter!=(it->second).end(); ++vIter){
			cout << *vIter << ":";
		}
		cout << endl;
	}
	cout << "End of AdjList!";
}


AdjacencyList::~AdjacencyList() {
	//automatic resource handling
	//unordered_map and vectors are STL containers, with garbage collection properties
}

