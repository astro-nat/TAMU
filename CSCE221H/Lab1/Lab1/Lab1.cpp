// Lab1.cpp
// Natalie Cluck

#include "stdafx.h"
#include <iostream>

using namespace std;

struct Point
{
	int x;
	int y;

	Point(int x, int y) : x(x), y(y) {};
	Point& operator=(const Point& p)
	{
		x = p.x;
		y = p.y;
		return Point(x, y);
	}
};

class Shape
{
protected:
	Point center;
public:
	Shape(Point c) : center(c) {}
	virtual void print() = 0;
};

class Circle : public Shape
{
private:
	float radius; //radius of circle
public:
	Circle(float r, Point p) : radius(r), Shape(p) {};
	void print() 
	{
		cout << "This will draw a circle at point (" << center.x << "," << center.y << ") and radius " << radius << ". " << endl;
	};
};

class Square : public Shape
{
private:
	int size; //distance from center to one side
public:
	Square(float s, Point p) : size(s), Shape(p) {};
	void print()
	{
		cout << "This will draw a square at point (" << center.x << "," << center.y << ") with a size of " << size << ". " << endl;
	};
};

int main()
{
	Point p1(2, 4);
	Point p2(4, 5);

	Shape *c = new Circle (5, p1);
	Shape *s = new Square (6, p2);

	c->print();
	s->print();
	
	//This will keep window open
	int temp; 
	cin >> temp;
}