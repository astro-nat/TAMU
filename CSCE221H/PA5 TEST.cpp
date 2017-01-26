// PA5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "LocatorHeap.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
	// read first two numbers for verticies/edges
	int verticies;
	int edges;

	ifstream ist("graph.txt");
	ist >> verticies;
	ist >> edges;

	cout << verticies << edges << endl;
	int temp;
	cin >> temp;
	// construct an adjacency list
	// use djikstra's algorithm to find shortest path
	// use heap with locators???
}

