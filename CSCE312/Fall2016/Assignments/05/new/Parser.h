#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Parser {
	ifstream inputfile;
	enum commandType {A_COMMAND,C_COMMAND,L_COMMAND};
	vector<string> commands;
	string current;
	commandType current_type;
	int current_address;
	
public:
	Parser(string filename);
	bool hasMoreCommands();
	void advance();
	commandType commandType();
	string symbol();
	string dest();
	string comp();
	string jump();
};


#endif