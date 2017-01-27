/********************************************************************************

Individual Assignment
Natalie Cluck
Due: Sunday, 2/5/2017, 11:59pm

Purpose: Create a program that can be used for keeping track of textbooks required and recommended for classes and the cost of those textbooks.

********************************************************************************/

#include <iostream>
#include <list>
#include <regex>
#include <algorithm>

using namespace std;

// stores the character code for the operation type
enum inputType {
    B,D,M,C,A,GC,GS,GB,PB,PC,PY,PD,PM
};

// declares Textbook class for use in Course class
class Textbook;

// defines variables and functions for Course object
class Course {
    
    int code = 0;        // 4-letter code for department
    int courseNum = 0;      // 3-digit number for the course
    int sectionNum = 0;     // 3-digit section number
    vector<Textbook> books; // list of textbooks for course
    
public:
    
    // get functions to return private variables
    int getCode() { return code; }
    int getCourseNum() { return courseNum; }
    int getSectionNum() { return sectionNum; }
    
    // set functions to change private variables
    void setCode(int c) { code = c; }
    void setCourseNum(int n) { courseNum = n; }
    void setSectionNum(int s) { sectionNum = s; }
    
};

// defines variables and functions for Textbook object
class Textbook {
    
	string ISBN = "";      // 13-digit ISBN number
	string title = "";     // book title
	string author = "";    // book author
	string edition = "";   // edition (a positive integer)
	string pubDate = "";   // date the book was published (MM/YYYY format)
	bool required = true;  // is the book required or optional for the course?
    
    vector<Course> courses;
    
    // stores costs for New, Used, Rented, and Electronic versions of Textbook
    double cost[4] = { };
    
public:

    // constructor for creating new textbook with ISBN and title
	Textbook(string ISBN,string title) : ISBN(ISBN),title(title) {};
    
    void printBook() {
        cout << "Title: " << getTitle() << endl;
        cout << "ISBN: " << getISBN() << endl;
        cout << "Author: " << getAuthor() << endl;
        cout << "Edition: " << getEdition() << endl;
        cout << "Publication Date: " << getPubDate() << endl;
        
        if (getCost("New") != 0) cout << "Cost for New Book: " << getCost("New") << endl;
        else cout << "Cost for New Book: -" << endl;
        
        if (getCost("Used") != 0) cout << "Cost for Used Book: " << getCost("Used") << endl;
        else cout << "Cost for Used Book: -" << endl;
        
        if (getCost("Rented") != 0) cout << "Cost for Rented Book: " << getCost("Rented") << endl;
        else cout << "Cost for Rented Book: -" << endl;
        
        if (getCost("Electronic") != 0) cout << "Cost for Electronic Book: " << getCost("Electronic") << endl;
        else cout << "Cost for Electronic Book: -" << endl;
    }
    
    string getISBN() { return ISBN; }
    string getTitle() { return title; }
    string getAuthor() { return author; }
    string getEdition() { return edition; }
    string getPubDate() { return pubDate; }
    double getCost(string booktype) {
        if (booktype == "New") {
            return cost[0];
        }
        if (booktype == "Used") {
            return cost[1];
        }
        if (booktype == "Rented") {
            return cost[2];
        }
        if (booktype == "Electronic") {
            return cost[3];
        }
        else return 0;
    }
    bool IsRequired() { return required; }
    
    void setISBN(string i) { ISBN = i; }
    void setTitle(string t) { title = t; }
    void setAuthor(string a) { author = a; }
    void setEdition(string e) { edition = e; }
    void setPubDate(string d) { pubDate = d; }
    
    void setCost(string booktype, double c) {
        if (booktype == "New") {
            cost[0] = c;
        }
        else if (booktype == "Used") {
            cost[1] = c;
        }
        else if (booktype == "Rented") {
            cost[2] = c;
        }
        else if (booktype == "Electronic") {
            cost[3] = c;
        }
    }
    
    void makeItRequired() { required = true; }
    void makeItOptional() { required = false; }
	
};

// adds new Book object to vector of Textbooks
void addBook(string ISBN,string& title,vector<Textbook>& textbooks) {
    
    Textbook* book = new Textbook(ISBN,title); // creates new textbook with ISBN and title
    bool found = false;  // will be used to find existing ISBN number in database
    
    // if ISBN found in database, update the title
    for(int i = 0; i < textbooks.size(); i++) {
        if (textbooks[i].getISBN() == ISBN) {
            textbooks[i].setTitle(title);
            found = true;
        }
    }
    
    // if ISBN not found in database, add new book with ISBN and title
    if (found == false) {
        textbooks.push_back(*book);
    }
   
}

// prints all Textbook objects and their information
void printBooks(vector<Textbook>& textbooks) {
    if (sizeof(textbooks) != 0) {
        vector<Textbook>::iterator it = textbooks.begin();
        for(vector<Textbook>::iterator it = textbooks.begin(); it != textbooks.end(); it++) {
            cout << "*" << endl;
            (*it).printBook();
        }
        cout << "*" << endl;
    }
}

// prints all Course objects and their information
void printCourses(vector<Course>& courses) {
    if (sizeof(courses) != 0) {
        vector<Course>::iterator it = courses.begin();
        for(vector<Course>::iterator it = courses.begin(); it != courses.end(); it++) {
            cout << (*it).getCode() << endl;
        }
    }
}

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
			else return PM;
		}
		catch(exception& e) {
			cout << "That operation does not exist." << endl;
		}
}

void trimLeadWhitespace(string& object) {
    object = regex_replace(object, regex("^ +"), "");
}

int main() {
    try {
        // initializes course list and textbook list
        vector<Course> courses;
        vector<Textbook> textbooks;
        
        string type, ISBN, title, author, date, edition, tracker;
        double cost;
        
        while(type != "q") {
            cout << "Input: ";
            cin >> type;
            
            // cases for different operation types
            switch (hashInput(type)) {
                
                case B:
                    cin >> ISBN; // stores ISBN number
                    getline(cin,title); // stores rest of line as title
                    trimLeadWhitespace(title); // removes leading white space
                    addBook(ISBN,title,textbooks); // adds book to textbook database
                    break;
                    
                case D:
                    cin >> ISBN;      // stores ISBN number
                    cin >> tracker;   // stores A, E, or D
                    
                    // searches through textbook database for book with matching ISBN
                    for(int i = 0; i < textbooks.size(); i++) {
                        
                        // if found, updates textbook with author, edition, or date
                        if (textbooks[i].getISBN() == ISBN) {
                            
                            // updates author
                            if (tracker == "A") {
                                getline(cin,author);
                                trimLeadWhitespace(author);
                                textbooks[i].setAuthor(author);
                            }
                            // updates edition
                            else if (tracker == "E") {
                                getline(cin,edition);
                                trimLeadWhitespace(edition);
                                textbooks[i].setEdition(edition);
                            }
                            // updates publication date
                            else if (tracker == "D") {
                                getline(cin,date);
                                trimLeadWhitespace(date);
                                textbooks[i].setPubDate(date);
                            }
                            else {
                                cout << "Not a valid input." << endl;
                            }
                        }
                    }
                    
                    break;
                    
                case M:
                    cin >> ISBN >> cost >> tracker;
                    
                    // searches through textbook database for book with matching ISBN
                    for(int i = 0; i < textbooks.size(); i++) {
                        
                        // if found, updates textbook with cost for N,U,R,E
                        if (textbooks[i].getISBN() == ISBN) {
                            
                            if (tracker == "N") {
                                textbooks[i].setCost("New",cost);
                            }
                            else if (tracker == "U") {
                                textbooks[i].setCost("Used",cost);
                            }
                            else if (tracker == "R") {
                                textbooks[i].setCost("Rented",cost);
                            }
                            else if (tracker == "E") {
                                cout << textbooks[i].getCost("Electronic") << endl;
                                textbooks[i].setCost("Electronic",cost);
                                cout << textbooks[i].getCost("Electronic") << endl;
                            }
                            else {
                                cout << "Not a valid input." << endl;
                            }
                        }
                    }
                    
                    break;
                    
                case C:
                    break;
                    
                case A:
                    break;
                    
                case GC:
                    break;
                    
                case GS:
                    break;
                    
                case GB:
                    
                    cin >> ISBN;     // collects ISBN number
                    
                    // search for book with matching ISBN number, then print it
                    for(int i = 0; i < textbooks.size(); i++) {
                        if (ISBN == textbooks[i].getISBN()) {
                            textbooks[i].printBook();
                        }
                    }
                    break;
                    
                case PB:
                    
                    // prints all books in the textbook database
                    cout << "\nPrinting all books... \n\n";
                    printBooks(textbooks);
                    break;
                    
                case PC:
                    
                    // prints all courses in the course database
                    cout << "\nPrinting all courses... \n\n";
                    printCourses(courses);
                    break;
                    
                case PY:
                    break;
                    
                case PD:
                    break;
                    
                case PM:
                    break;
                    
                default:
                    break;
                    
            };
            
            
            
            cout << "---" << endl;
        }
    }
    catch(exception& e) {
        cout << "Exception: " << e.what() << endl;
    }
}












