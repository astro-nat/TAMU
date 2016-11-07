#include <iostream>
#include "SymbolTable.h"
#include "Parser.h"
#include "Code.h"
#include <regex>

using namespace std;

int main() {
	string inputfile = "";
	cout << "Enter an assembly file name: " << endl;
	cin >> inputfile;
	regex a_command("@(.*)");
	regex l_command("\\((.*)\\)");
	regex c_command("(.*=.*)");
	regex c_command2("(.*;.*)");
	smatch match;
	
	Parser* parser = new Parser(inputfile);
	Code* code = new Code();
	SymbolTable* symboltable = new SymbolTable();
	
	ofstream os;
	os.open(inputfile.substr(0,inputfile.find_last_of(".")) + ".hack");
	
	// first pass
	for(int i = 0; i < parser->getCommands().size(); i++) {
		string curr = parser->getCommands()[i];
		//cout << "Elem: " << parser->getCommands()[i] << endl;
		
		// checks for command type using regular expressions
		if (regex_search(curr,match,a_command) == 1) {
			parser->current_type = Parser::A_COMMAND;
			parser->advance();
		}
		
		else if ((regex_search(curr,match,c_command) == 1) || (regex_search(curr,match,c_command2 == 1))) {
			parser->current_type = Parser::C_COMMAND;
			parser->advance();
		}
		
		else if (regex_search(curr,match,l_command) == 1) {
			parser->current_type = Parser::L_COMMAND;
			cout << "Address: " << parser->getAddress() << endl;
			symboltable->addEntry(match[0],parser->getAddress());
		}
	}
	
	// second pass
	for(int i = 0; i < parser->getCommands().size(); i++) {
		int current_binary[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
		string curr = parser->getCommands()[i];
		//cout << "Elem: " << parser->getCommands()[i] << endl;
		
		// checks for command type using regular expressions
		if (regex_search(curr,match,a_command) == 1) {
			parser->current_type = Parser::A_COMMAND;
			if (symboltable->contains(match[0])) {
				for(int i = 1; i < 8; i++) {
					current_binary[i] = bitset<7>(symboltable->GetAddress(match[0]))[i];
				}
			}
			else {
				symboltable->addEntry(match[0],parser->getAddress());
			}
		}
		else if (regex_search(curr,match,c_command) == 1) {
			parser->current_type = Parser::C_COMMAND;
			current_binary[0] = 1;
			current_binary[1] = 1;
			current_binary[2] = 1;
		}
		
		else if (regex_search(curr,match,l_command) == 1) {
			parser->current_type = Parser::L_COMMAND;
			
		}
		
		for(int i = 0; i < 16; i++) {
			os << current_binary[i];
		}
		os << endl;
	}
}