// PA5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

int _tmain(int argc, _TCHAR* argv[])
{
	// read first two numbers for verticies/edges
	ifstream ist("graph.txt");
	ist >> int verticies;
	ist >> int edges;

	cout << verticies << edges << endl;
	int temp;
	cin >> temp;
	// construct an adjacency list
	// use djikstra's algorithm to find shortest path
	// use heap with locators???
}

