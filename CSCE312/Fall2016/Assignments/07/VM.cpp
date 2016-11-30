#include <iostream>
#include "SymbolTable.h"
#include "Parser.h"
#include "Code.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
#include <regex>
#include <string>
#include <locale>

using namespace std;

bool find_val(string s, char val) {
	for(int i = 0; i < s.length(); i++) {
		if (s[i] == val) { return true; }
	}
    return false;
}

bool is_integer(string s){
		bool final = true;
		for(int i = 0; i < s.length(); i++) {
			if (!isdigit(s[i])) { return false; }
		}
    	return final;
}
	
int main() {
	string input = "";
	cout << "Enter an assembly file name: " << endl;
	cin >> input;
	regex a_command("@(.*)");
	regex l_command("\\((.*)\\)");
	regex c_command("(.*)[=;]+(.*)");
	regex re{"\\s*//.*"};
	smatch match;
	
	Parser* parser = new Parser(input);
	Code* code = new Code();
	SymbolTable* symboltable = new SymbolTable();
	int symbol_address = 16;
	
	ofstream os;
	os.open(input.substr(0,input.find_last_of(".")) + ".hack");
	
	// first pass
	string line = "";
	int temp_address = 0;
	while(getline(parser->inputfile,line)) {
	
		// removes spaces and comments
		line.erase(remove(line.begin(), line.end(), ' '),line.end());
		line = regex_replace(line,re,"");
	
		// checks for A command type
		if (regex_search(line,match,a_command) == 1) {
			//parser->current_type = Parser::A_COMMAND;
			temp_address++;
			parser->commands.push_back(line);
		}
		
		// checks for C command type
		else if (regex_search(line,match,c_command) == 1) {
			//parser->current_type = Parser::C_COMMAND;
			temp_address++;
			parser->commands.push_back(line);
		}
	
		// checks for L command type
		else if (regex_search(line,match,l_command) == 1) {
			//parser->current_type = Parser::L_COMMAND;
			if (!is_integer(string(match[1]))) {
				symboltable->addEntry(match[1],temp_address);
				//cout << "Adding: " << match[1] << " at address " << temp_address;
				parser->commands.push_back(line);
			}
		}
	}
	
	// second pass
	int curr_addr = 16;
	for(int i = 0; i < parser->commands.size(); i++) {

		// resets current binary to 0000000000000000
		bitset<16> current_binary(0000000000000000);
		bitset<15> num(000000000000000);

		// current command
		string curr = parser->commands[i];
		parser->advance();
		
		// checks for A command type using regular expressions
		if (regex_search(curr,match,a_command) == 1) {
			parser->current_type = Parser::A_COMMAND;
			
			/*for(int i = 0; i < match.length(); i++) {
				cout << "Match number " << i << ": " << match[i] << endl;
			}*/
			
			// checks if symbol exists in symbol table
			//cout << "Symbol: " << match[1] << endl;
			if (!symboltable->contains(match[1])) {
				
				if (is_integer((string)match[1])) {
					num = bitset<15>(stoi(match[1]));
					//cout << "Num: " << num << endl;
					
					current_binary[15] = num[0];
					current_binary[14] = num[1];
					current_binary[13] = num[2];
					current_binary[12] = num[3];
					current_binary[11] = num[4];
					current_binary[10] = num[5];
					current_binary[9] = num[6];
					current_binary[8] = num[7];
					current_binary[7] = num[8];
					current_binary[6] = num[9];
					current_binary[5] = num[10];
					current_binary[4] = num[11];
					current_binary[3] = num[12];
					current_binary[2] = num[13];
					current_binary[1] = num[14];
				}
				else {
					// adds symbol to symbol table, starting at address 16
					symboltable->addEntry(match[1],curr_addr);
					
					num = bitset<15>(symboltable->GetAddress(match[1]));
					//cout << "Num: " << num << endl;
					
					current_binary[15] = num[0];
					current_binary[14] = num[1];
					current_binary[13] = num[2];
					current_binary[12] = num[3];
					current_binary[11] = num[4];
					current_binary[10] = num[5];
					current_binary[9] = num[6];
					current_binary[8] = num[7];
					current_binary[7] = num[8];
					current_binary[6] = num[9];
					current_binary[5] = num[10];
					current_binary[4] = num[11];
					current_binary[3] = num[12];
					current_binary[2] = num[13];
					current_binary[1] = num[14];
					
					curr_addr++;
				}
			}
			else {
				bitset<16> num = bitset<16>(symboltable->GetAddress(match[1]));
				
				current_binary[0] = num[15];
				current_binary[1] = num[14];
				current_binary[2] = num[13];
				current_binary[3] = num[12];
				current_binary[4] = num[11];
				current_binary[5] = num[10];
				current_binary[6] = num[9];
				current_binary[7] = num[8];
				current_binary[8] = num[7];
				current_binary[9] = num[6];
				current_binary[10] = num[5];
				current_binary[11] = num[4];
				current_binary[12] = num[3];
				current_binary[13] = num[2];
				current_binary[14] = num[1];
				current_binary[15] = num[0];
			}
			
			// writes binary to hack file
			for(int i = 0; i < 16; i++) {
				os << current_binary[i];
			}
			os << endl;
		} // end if

		// checks if command is a C command
		else if (regex_search(curr,match,c_command) == 1) {
			parser->current_type = Parser::C_COMMAND;

			// if C command, changes first three bits to 111
			current_binary[0] = 1;
			current_binary[1] = 1;
			current_binary[2] = 1;
		
			if (find_val(string(match[0]),'=')) {
				if (find_val(string(match[0]),';')) {
					//cout << "Both ; and = " << endl;
					string dest = match[1];
					string comp = match[2];
					string jump = match[3];
					
					current_binary[9] = code->comp(match[2])[0];
					current_binary[8] = code->comp(match[2])[1];
					current_binary[7] = code->comp(match[2])[2];
					current_binary[6] = code->comp(match[2])[3];
					current_binary[5] = code->comp(match[2])[4];
					current_binary[4] = code->comp(match[2])[5];
					current_binary[3] = code->comp(match[2])[6];
					
					current_binary[15] = code->jump(match[3])[0];
					current_binary[14] = code->jump(match[3])[1];
					current_binary[13] = code->jump(match[3])[2];
					
					current_binary[12] = code->dest(match[1])[0];
					current_binary[11] = code->dest(match[1])[1];
					current_binary[10] = code->dest(match[1])[2];
				}
				else {
					//cout << "Only = " << endl;
					current_binary[9] = code->comp(match[2])[0];
					current_binary[8] = code->comp(match[2])[1];
					current_binary[7] = code->comp(match[2])[2];
					current_binary[6] = code->comp(match[2])[3];
					current_binary[5] = code->comp(match[2])[4];
					current_binary[4] = code->comp(match[2])[5];
					current_binary[3] = code->comp(match[2])[6];
					
					current_binary[12] = code->dest(match[1])[0];
					current_binary[11] = code->dest(match[1])[1];
					current_binary[10] = code->dest(match[1])[2];
				}
				}
			else if (find_val(string(match[0]),';')) {
				//cout << "Only ; " << endl;
				current_binary[9] = code->comp(match[1])[0];
				current_binary[8] = code->comp(match[1])[1];
				current_binary[7] = code->comp(match[1])[2];
				current_binary[6] = code->comp(match[1])[3];
				current_binary[5] = code->comp(match[1])[4];
				current_binary[4] = code->comp(match[1])[5];
				current_binary[3] = code->comp(match[1])[6];
				
				//cout << "JUMP symbol: " << match[2] << endl;
				current_binary[15] = code->jump(match[2])[0];
				current_binary[14] = code->jump(match[2])[1];
				current_binary[13] = code->jump(match[2])[2];
			}
		
				
			//cout << "C COMMAND: " << match[0] << endl;

			// writes binary to hack file
			for(int i = 0; i < 16; i++) {
				os << current_binary[i];
			}
			
			os << endl;
		} // end else if
		
		else if (regex_search(curr,match,l_command) == 1) {
			parser->current_type = Parser::L_COMMAND;
		
		} // end else if

		else {
			cout << "Not found" << endl;
		} // end else
		
		//cout << "Binary: ";
		/*for(int i = 0; i < 16; i++) {
			cout << current_binary[i];
		}*/
		//cout << endl;
	} // end for
	
	cout << "DONE" << endl;
} // end main