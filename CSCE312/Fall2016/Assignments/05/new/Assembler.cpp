#include <iostream>
#include "SymbolTable.h"
#include "Parser.h"
#include "Code.h"

using namespace std;

int main() {
	string inputfile = "";
	cout << "Enter an assembly file name: " << endl;
	cin >> inputfile;
	
	Parser* parser = new Parser(inputfile);
	Code* code = new Code();
	SymbolTable* symboltable = new SymbolTable();
	
	for(int i = 0; i < parser->getCommands().size(); i++) {
		string curr = parser->getCommands()[i];
		cout << "Elem: " << parser->getCommands()[i] << endl;
		if (curr.find("@")) {
			parser->current_type = Parser::A_COMMAND;
		}
		else if (curr.find("=")) {
			parser->current_type = Parser::C_COMMAND;
		}
		else {
			parser->current_type = Parser::L_COMMAND;
		}
	}
	
}