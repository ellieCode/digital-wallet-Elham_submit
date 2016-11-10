/*
* Implementation of utility functions for File I/O handling
*/
#include "CSVhandler.h"

CSVhandler::CSVhandler(string filename, char operation) {
	if(operation == 'r'){ 				//input file for reading
		//infile = ifstream(filename);
		//if(!infile){
        	//This line was added when checking compilation on Linux
		infile.open(filename.c_str(), ifstream::in);
		if(!infile.is_open()){                  //if there was an issue opening the input file
			cerr << "Input File  " << filename <<" could not be opened! " << endl;
		}
	}
	else if (operation == 'w'){  			//output file for writing
		//outfile= ofstream(filename);
		//if(!outfile){
		outfile.open(filename.c_str(), ofstream::out);
		if(!outfile.is_open()){                   //if there was an issue opening the output file
			cerr << "Output File  " << filename <<" could not be opened! " << endl;
		}
	}else{						   //if the Constructor wasn't called properly
		cerr<< "operation must be read or write" <<endl;
	}
}

//The file is comma delimited, so we use a tokenizer function to get the ids
vector<string> CSVhandler::LineTokenizer(string line){
	if (line.empty()){
		cerr << "Can not Tokenize Empty Line" << endl;
	}
	//return two ids as strings, caller decides how to cast them
	vector <string> ids(2,"");
	istringstream tokens(line);
	string token;

	//tokenize properly
	try{
		getline(tokens, token, ',');
		getline(tokens, token, ',');
		ids[0] = token;
		getline(tokens, token, ',');
		ids[1] = token;
		return ids;}
	catch(std::exception &e){
		cerr << e.what();
		cerr << "Not a Valid Entry: Unable to Tokenize the Line" << endl;
		exit(-1);
	}
}

//read a line from the input file
string CSVhandler::readLine(){
	string line;
	if(infile){
		//empty line is not an error, it's handled within the caller
		getline (infile, line);
		return line;
	}
	else{
		cerr << "Error reading from input file" << endl;
		exit(-1);
	}

}

void CSVhandler::writeLine(string line){
	if(outfile){
		outfile << line << endl;
	}else{
		cerr << "Error writing to output file" << endl;
		exit(-1);
	}
}

bool CSVhandler::EOFile(){
	return infile.eof();
}

CSVhandler::~CSVhandler(){
	if(infile.is_open()){
		infile.close();
	}
	if(outfile.is_open()){
		outfile.close();
	}
}
