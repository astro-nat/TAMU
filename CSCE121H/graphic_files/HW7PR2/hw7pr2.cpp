// To practice with inheritance and virtual functions

// Write a program that manipulates different kinds of publications (books, encyclopedia articles, and journal articles) and prints out bibliography entries for them, with different format for different kinds of publications.

// Required formats:

/* Book:
------
	Format:
	Author's last name, first name. _Book title_.  City of publication: 
	Publishing company, date.

		Example:
		Spratt, Jack.  _Eating Healthily_.  New York: Nursery Rhymes Company, 1855.

Encyclopedia Article:
---------------------
	Format:
	"Title of Article." _Title of Encylopedia_. Date.

		Example:
		"Nursery Rhymes." _Encyclopedia Galactica_. 2050.

Journal Article:
-----------------
	Format:
	Author's last name, first name. (year) "Title of article." _Journal name_ 
	volume number (issue number) : starting page-ending page, year.

		Example:
		Knuth, Donald. (1965) "On the translation of languages from left to right."
		_Information and Computation_ 8(6):607-639.

Your program is to read in "raw data" from a file, using this file
format (for the examples given above):

B
Spratt, Jack
Eating Healthily
New York
Nursery Rhymes Company
1855

E
Nursery Rhymes
Encyclopedia Galactica
2050

J
Knuth, Donald
On the translation of languages from left to right
Information and Computation
8
6
607
639
1965

// Done Make a hierarchy of classes (or structs), with a generic class representing publication as the base, and separate derived classes for books, encyclopedia articles, and journal articles.  

// Done Your base publication class must have a virtual function for writing the formatted bibliography entries to the file, which is overridden in each of the derived classes. 

// You are to read in the information in the file into variables of the appropriate types, and then store each one in a "vector_ref" of references to publication objects. (Add into your code the code defining Vector_ref on pp. 1166-1167.) Then loop through the vector, writing out to a file the properly formatted bibliographic entries for the information in each vector entry, by calling the virtual function of the base class. */

#include "std_lib_facilities_4.h"

using namespace std;

struct Publication
{
protected:
	// variables that ALL formats have. Title. First m,Name. Last Name. Date (only book and encycl) 
	string firstname;
	string lastname;
	int year;
	
	ifstream RawData("dahpubs.txt");
	
public:
	virtual void biblio();
};

struct Book : Publication
{
	// variables that only books have
private:
	string title;
	string city;
	string company;
public:	
	void biblio()
	{
	
	}
	// constructor to format bibliography entry
	/* Format:
	Author's last name, first name. _Book title_.  City of publication: 
	Publishing company, date.

		Example:
		Spratt, Jack.  _Eating Healthily_.  New York: Nursery Rhymes Company, 1855.
	*/
};

struct Encyclopedia : Publication 
{
	// variables that only encyclopedias have
private:
	string article;
	string name;
public:
	// biblio --> write entry according to encyclopedia format
	void biblio()
	{
	
	}
	// constructor to format bibliography entry
	/* Format:
	"Title of Article." _Title of Encylopedia_. Date.

		Example:
		"Nursery Rhymes." _Encyclopedia Galactica_. 2050. */
};

struct Journal : Publication
{
	// variables that only journal has
private:
	string article;
	int volume;
	int issue;
	int startpg;
	int endpg;
public:
	// biblio --> write entry according to journal article format
	void biblio()
	{
	
	}
	// constructor to format bibliography entry
	/* Format:
	Author's last name, first name. (year) "Title of article." _Journal name_ 
	volume number (issue number) : starting page-ending page, year.

		Example:
		Knuth, Donald. (1965) "On the translation of languages from left to right."
		_Information and Computation_ 8(6):607-639. */
};

template<class T> class Vector_ref{
	vector<T*> v;
	vector<T*> owned;
public:
	Vector_ref(){}
	Vector_ref(T* a, T* B = 0, T* c = 0, T* d = 0);
	
	~Vector_ref(){for (int i = 0; i<owned.size(); ++i) delete owned[i];}
	
	void push_back(T& s){v.push_back(&s);}
	void push_back(T* p){v.push_back(p); owned.push_back(p);}
	
	T& operator[](int i){ return *v[i];}
	const T& operator[](int i) const {return *v[i];}
	
	int size() const {return v.size(); }
};

int main() 
{
	try 
	{
		cout << "This works." << endl;
		ifstream RawData("dahpubs.txt");
	}
	catch(exception& e)
	{
		cerr << "exception: " << e.what() << endl;
	}
	catch(...)
	{
		cerr << "Something else went wrong." << endl;
	}
}