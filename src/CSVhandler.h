/*
 * CSVhandler.h
 *
 *  Created on: Nov 8, 2016
 *      Author: Ellie
 */

#ifndef CSVHANDLER_H_
#define CSVHANDLER_H_

#include <iostream>     //for std::cerr
#include <vector>
#include <string>
#include <sstream>      // std::istringstream
#include <fstream>      // std::ofstream

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
