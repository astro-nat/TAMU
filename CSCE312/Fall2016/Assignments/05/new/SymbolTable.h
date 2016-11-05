#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <iostream>
#include <map>

using namespace std;

class SymbolTable {
	map<string,int> symbols;
public:
	SymbolTable();
	void addEntry(string symbol, int address);
	bool contains(string symbol);
	int GetAddress(string symbol);
};



#endif