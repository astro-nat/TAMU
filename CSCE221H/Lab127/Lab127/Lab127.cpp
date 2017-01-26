// Lab127.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cmath>

using namespace std;

template <class T, int n>
class Point
{
private:
	T (&myarray)[n];
public:
	Point(T (&thearray)[n]) : myarray(thearray) {};
	T& operator[] (int i) { return myarray[i]; }
	int size() { return n; };
};

template <class D>
void euclid(D& p1, D& p2)
{	
	double sum = 0;
	
	for (int i = 0; i < p1.size(); i++)
	{
		sum += pow((p1[i] - p2[i]), 2);
	}

	double distance = sqrt(sum);
	cout << "The Euclidean distance between the two points is " << distance << "." << endl;
}

int main()
{
	double array1[3] = { 1.4, 2.47, 3.295 };
	Point<double, 3> p1(array1);
	double array2[3] = { 4.2, 7.284, 10.123943 };
	Point<double, 3> p2(array2);

	euclid(p1, p2);

	int array3[2] = { 1, 2 };
	Point<int, 2> p3(array3);
	int array4[2] = { 4, 7 };
	Point<int, 2> p4(array4);

	euclid(p3, p4);
}