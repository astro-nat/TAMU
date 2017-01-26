// This exercise and the next few require you to design and implement a Book class, such as you can imagine as part of software for a library. Class Book should have members for the ISBN, title, author, and copyright date. Also store data on whether or not the book is checked out. Create functions for returning those data values. Create functions for checking a book in and out. Do simple validation of data entered into a Book; for example, accept ISBNs only of the form n-n-n-x where n is an integer and x is a digit or a letter.

// Add operators for the Book class. Have the == operator check whether the ISBN numbers are the same for two books. Have != also compare the ISBN numbers. Have a << print out the title author,  and ISBN on the separate lines.

// Create an enumerated tpe for the Book class called Genre. Have the types be fiction, nonfiction, periodical, biography, children. Give each book a Genre and make appropriate changes to the Book constructor and member functions.

// Create a Patron class for the library. The class will have a user's name, library card number, and library fees (if owed). Have functions that access these methods, as well as a function to set the fee of the user. Have a helpeer method that rturns a Boolean (bool) depending on whether or not the user owes a fee.

// Create a Library class. Include vectors of Books and Patrons. Include a struct called Transaction. Have it include a Book, a Patron, and a Date from the chapter. Make a vector of Transactions. Create functions to add books to the librayr, add patrons to tehe library, and check out books. Whenever a user checks out a book, have the library make sure that both the user and the book are in the library. If they aren't, report an error. Then check to make sure that the user owes no fees. If the user does, report an error. If not, create a Transaction, and place it in the vector of Transactions. Also create a method that will return a vector that contains the names of all Patrons who owe fees.

#include <iostream>
#include "ctype.h"
#include <exception>
#include "std_lib_facilities_4.h"
struct Date {
	int y;
	int m;
	int d;
	public:
	Date(int day, int month, int year):d(day),m(month),y(year){}
};
class Book {
	string ISBN;
	string title;
	string author;
	Date copyright_date;
	bool checked_in;
	bool ISBNchecker(string ISBN){
		string tempISBN = ISBN;
		while (true)
		{
			string part1 = tempISBN.substr(0,tempISBN.find('-'));
			string lastCheck = tempISBN;
			tempISBN = tempISBN.substr(tempISBN.find('-')+1);
			if (lastCheck.find('-') == string::npos)
			{
				if (part1.size() != 1)
				{
					cout<<part1<<" IS NOT LENGTH 1\n";
					return false;
				}
				
				if (!isalnum(part1[0]))
				{
					cout<<part1[0]<<" IS NOT ALPHANUMERIC\n";
					return false;
				}
				return true;
			}
			for (int i = 0; i < part1.size(); i++)
			{
				if(!isdigit(part1[i]))
				{
					cout<<part1[i]<<" IS NOT A DIGIT\n";
					return false;
				}
			}
			
		}
	}
	public:
	Book(string ISBN, string title, string author, Date copyright):ISBN(ISBN),title(title),author(author),copyright_date(copyright)
	{
		checked_in = true;
		if (!ISBNchecker(ISBN))
			throw exception();
	}
	string getISBN(){return ISBN;}
};
	bool Book::operator== (Book& b2) const
	{
		return b2.getISBN() == this.getISBN(); 
	}
int main()
{
	try{
		Book b1("111-11-12-a","A BOOK YO", "SOME GUY", Date(1,1,1990));
		cout<<"SHOULD BE FINE HERE\n";
		Book b2("111-11-11-2", "INVALID BOOK RAWR!","SOME OTHER GUY", Date(1,1,2800));
		if (b1 == b2)
			cout<<"Awesome\n";
	}
	catch(exception &e)
	{
		cerr<<"ERROR\n";
	}
}

void init_day(Date& dd, int y, int m, int d)
{
	//check that (y,m,d) is a valid date
	// if it is, use it to initialize dd
}