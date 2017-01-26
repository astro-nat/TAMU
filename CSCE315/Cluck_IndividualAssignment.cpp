/********************************************************************************

Individual Assignment
Natalie Cluck
Due: Sunday, 2/5/2017, 11:59pm

Purpose: Create a program that can be used for keeping track of textbooks required and recommended for classes and the cost of those textbooks.

Create databases for:
books
courses

Book class:
ISBN
title
author
edition
publication date
cost
required/optional

Course class:
Department code
course number
section number
List of Book objects

********************************************************************************/

#include <iostream>
#include <list>

using namespace std;

class Book {
	int ISBN;
	string title;
	string author;
	int edition;
	int pubDate;
	int cost;
	bool required;
};

class Course {
	int code;
	int courseNum = 2;
	int sectionNum;
	list<Book> books;
	public:
	int getCourseNum() {
		return courseNum;
	}
};

int main() {
	Course course;
	cout << course.getCourseNum();
}