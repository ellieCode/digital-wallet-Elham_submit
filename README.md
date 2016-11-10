# Table of Contents

1. [Summary] (README.md#summary)
2. [Details of Implementation] (README.md#details-of-implementation)
4. [Notes] (README.md#Notes)

##Summary
The 3 features described in the challenge summary were implemented in C++. The driver file called "DigitalWallet.cpp" can be found in src folder

###Libraries
Please note that several features of c++11 have been used, therefore, for proper compilation c++11 will be required. 

###Assumptions
(1) We assumed that transaction between a person and himself/herself is trusted, no matter it's included in the batch_payment.txt or not.

(2) We assumed that ids are numbers, basically valid unsigned integer numbers, however, the implementation can be readily employed to any other object type.

(3) We assumed that transactions are valid, therefore, we did not check for data extracted from the csv/txt file. We assumed (as promised in the challenge Description)
    that entries are valid.

(4) we assumed that the line description of each transaction is not extremely huge. Therefore, reading lines will fit into memory.


##Details of implementation

[Back to Table of Contents] (README.md#table-of-contents)

We leveraged Graphs for representing the friends' network, which were implemented using Adjacency Lists.
The design structure for this digital wallet has been kept simple and minimal. There are three classes: AdjacencyList, Graph and CSVhandler.  
We first construct an Adjacency List given the batch_payment.txt file, Use it for Feature 1, and then use the Adjacency List for Breadth First Search (BFS) of the Graph
for features 2 and 3.


###AdjacencyList
The underlying data structure for adjacency list was chosen as "unorderd_map", which is ideal for allowing IDs to be of any type/object. 
Unordered_maps are ideal for hashing the IDs to a table, and accessing them later very efficiently.
As for any Adj List, each node has a vector of connected friends. Duplicates are avoided by checking existence of a node in the current vector. 

We note that for implementing Feature 1, a mere Adjacency List is enough. Given any node, one can efficiently look at its connected friends in a vector, and find out "trusted" or "unverified" status. However, we double check our results with the solution provided for Features 2 and 3.

###Graph
For implementing features 2 and 3, we used the adjacency list representation of the graph to perform BFS. 
The idea is to preform BFS up to a certain depth. For example, for friend of friend, we need two levels of BFS. 
BFS was implemented using doubly linked Lists, so that we can insert at the end of the queue and pop from the top in O(1).
Obviously one can check results from adjacency list with results from Graph with depth=1 for debugging.


###CSVhandler
This class is merely a utility wrapper for I/O and error checking of file operations.


###Output
There will be three outputs for features 1 to 3, named output1.txt, output2.txt, output3.txt. 
We added our results for Feature 2 as output2.txt (~26MB). 
The directory structure and the format of output was tested under Unix and Linux and the 3 test cases in insight_testsuite folder were passed.

#Notes
Enhancements:

(1) One enhancement that would be beneficial for fraud checking, is to benefit from other fields of information. Particularly, the "amount" field can be very useful for fraud checking. It's enough to check a certain threshold when reading the data from file, and mark the transaction as suspected if the amount is too large.

(2) Another enhancement is to change the graph from "undirected" to "directed". This means, if I am used to have transaction with a company, doesn't necessarily imply that the company also has a valid transaction with me! Some transactions are uni-directional in nature.
    This is easily achieved given the current implementation. In the Adjacency List class, we insert nodes for both id1 and id2 when seeing a transaction between id1 and id2. 
    For a directed graph, it will be changed to one entry to the unordered_map
