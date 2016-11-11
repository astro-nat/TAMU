#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
#include <regex>
#include <string>

using namespace std;

struct Parser {
	ifstream inputfile;
	enum commandType {A_COMMAND,C_COMMAND,L_COMMAND};
	vector<string> commands;
	string current;
	commandType current_type;
	int current_address;
	
	Parser(string filename) {
	
		inputfile.open(filename);
		current_address = 0;
	}

	bool hasMoreCommands() {
		if (current_address < (commands.size() - 1)) return true;
		else return false;
	}
	
	int getAddress() {
		return current_address;
	}
	
	void advance() {
		current_address++;
	}
	
	commandType commandType() {
		if (current_type == L_COMMAND) {
			return L_COMMAND;
		}
		else if (current_type == C_COMMAND) {
			return C_COMMAND;
		}
		else return A_COMMAND;
	}
	
		
	string symbol() {
		if (commandType() == (A_COMMAND or L_COMMAND)) {
			return current;
		}
		else return "";
	}
	
	string dest() {
		// to be changed
		if (current_type == C_COMMAND)
			return current;
		else return "";
	}
	
	string comp() {
		// to be changed
		if (current_type == C_COMMAND)
			return current;
		else return "";
	}
	
		
	string jump() {
		// to be changed
		if ((current_type) == C_COMMAND)
			return current;
		else return "";
	}
};


#endif