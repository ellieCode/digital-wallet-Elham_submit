/*
 * CSVhandler.h
 * Header for file I/O handling
 * 
 */

#ifndef CSVHANDLER_H_
#define CSVHANDLER_H_

#include <iostream>    
#include <vector>
#include <string>
#include <sstream>     
#include <fstream>      

using  namespace std;

class CSVhandler {
private:
	ifstream infile;
	ofstream outfile;

public:
	CSVhandler(string filename, char operation);
	~CSVhandler();
	vector<string> LineTokenizer(string line);
	string readLine();
	void writeLine(string line);
	bool EOFile();
};

#endif /* CSVHANDLER_H_ */
