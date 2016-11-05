#include <iostream>
#include "Parser.h"

using namespace std;

Parser::Parser(string filename) {
	
	inputfile.open(filename);
	while(getline(inputfile,line)) {
		commands.push_back(line);
	}
	
	current_address = 0;
}
	
bool Parser::hasMoreCommands() {
	if (current_address < (commands.size() - 1)) return true;
	else return false;
}

void Parser::advance() {
	current_address++;
}

commandType Parser::commandType() {
	if (current_type == commandType.L_COMMAND) {
		return L_COMMAND;
	}
	else if (current_type == commandType.C_COMMAND) {
		return C_COMMAND;
	}
	else return D_COMMAND;
}
	
string Parser::symbol() {
	if (commandType() == (A_COMMAND or L_COMMAND)) {
		return current_command;
	}
	else return "";
}
	
string Parser::dest() {
	// to be changed
	if (current_type == C_COMMAND)
		return current_command;
}
	
string Parser::comp() {
	// to be changed
	if (current_type == C_COMMAND)
		return current_command;
	else return "";
}
	
string Parser::jump() {
	// to be changed
	if (current_type) == C_COMMAND)
		return current_command;
	else return "";
		
}

