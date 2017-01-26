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

class Course;

// stores the character code for the type of operation
enum inputType {
	B,D,M,C,A,GC,GS,GB,PB,PC,PY,PD,PM
};

class Textbook {
	int ISBN;
	string title;
	string author;
	int edition;
	int pubDate;
	int cost;
	bool required;
public:

	Textbook(int ISBN,string title):ISBN(ISBN),title(title) {};
	
	void addBook(int ISBN,string title,list<Textbook> textbooks) {
		textbooks.push_back(Textbook(ISBN,title));
	}
};

class Course {
	int code;
	int courseNum = 2;
	int sectionNum;
	list<Textbook> books;
	public:
	int getCourseNum() {
		return courseNum;
	}
};

inputType hashInput(string input) {
		try {
			if (input == "B") return B;
			else if (input == "D") return D;
			else if (input == "M") return M;
			else if (input == "C") return C;
			else if (input == "A") return A;
			else if (input == "GC") return GC;
			else if (input == "GS") return GS;
			else if (input == "GB") return GB;
			else if (input == "PB") return PB;
			else if (input == "PC") return PC;
			else if (input == "PY") return PY;
			else if (input == "PD") return PD;
			else if (input == "PM") return PM;
		}
		catch(exception& e) {
			cout << "That operation does not exist." << endl;
		}
}
	
int main() {
	
	// initializes course list and textbook list
	list<Course> courses;
	list<Textbook> textbooks;
	
	string type;
	cout << "Input: ";
	cin >> type;
	
	// cases for different operation types
	switch (hashInput(type)) {
		
		case B:
			long int ISBN;
			cin >> ISBN;
			cout << "ISBN: " << ISBN << endl;
			break;
		case D:
		case M:
		case C:
		case A:
		case GC:
		case GS:
		case GB:
		case PB:
		case PC:
		case PY:
		case PD:
		case PM:
			break;
		default:
			break;
			
	}
}












