#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>

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
		string line = "";
		while(getline(inputfile,line)) {
			if(line.length() > 1){
				if(line.find("//") == std::string::npos){
					commands.push_back(line);
				}
			}
		}
	
		current_address = 0;
	}
	
	vector<string> getCommands() {
		return commands;	
	}

	bool hasMoreCommands() {
		if (current_address < (commands.size() - 1)) return true;
		else return false;
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