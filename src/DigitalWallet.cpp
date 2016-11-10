//============================================================================
// Name        : DigitalWallet_v3.0.cpp
// Author      : Elham Sakhaee
// Version     :
// Copyright   : 
// Description : The driver code, which reads in the batch_input,
//								  forms the adjList or the Graph,
// 								  reads stream_input, writes to output
//============================================================================

#include <iostream>
#include "AdjacencyList.h"
#include "Graph.h"

using namespace std;

static void usage(string fcnName){
	cerr << "Usage: " << fcnName << "/path/to/batch_payment.txt  " << "/path/to/stream_payment.txt  "
								 << "/path/to/output1.txt " << "/path/to/output2.txt " << "/path/to/output3.txt ";
}
int main(int argc, char* argv[]){

	    if (argc < 6) {
	    	usage(argv[0]);
	    	return 1;
	    }

    int depth;
	string batchFilename = argv[1];
	string streamFilename = argv[2];

	vector <string> outputfiles;
	for (int i = 3; i < argc; ++i){
		outputfiles.push_back(argv[i]);
	}

	AdjacencyList adjList(batchFilename);
	Graph g (&adjList);

	//Feature 1:
	adjList.checkTrusted(streamFilename,outputfiles[0]);
    
    
    //Feature 1, double check:
    //depth = 1;      //1 = friend
    //g.checkTrusted(streamFilename,outputfiles[0], 1);

    //Feature 2
    depth = 1;  //2 = friend of friend, ...
    g.checkTrusted(streamFilename,outputfiles[1], depth);
    
    
	//Feature 3
	depth = 4;      //4 = friend of friend of friend of friend
 	g.checkTrusted(streamFilename,outputfiles[2], depth);
   

}


