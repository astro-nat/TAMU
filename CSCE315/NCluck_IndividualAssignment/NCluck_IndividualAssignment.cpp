/********************************************************************************
 
 Individual Assignment
 Natalie Cluck
 Due: Sunday, 2/5/2017, 11:59pm
 
 Purpose: Create a program that can be used for keeping track of textbooks
 required and recommended for classes and the cost of those textbooks.
 
 ********************************************************************************/

#include <iostream>
#include <list>
#include <regex>
#include <algorithm>
#include <map>

using namespace std;

// stores the character code for the operation type
enum inputType {
    B,D,M,C,A,GC,GS,GB,PB,PC,PY,PD,PM
};

class Course;

// defines variables and functions for Textbook object
class Textbook {
    
    string ISBN = "";      // 13-digit ISBN number
    string title = "";     // book title
    string author = "";    // book author
    string edition = "";   // edition (a positive integer)
    string pubDate = "";   // date the book was published (MM/YYYY format)
    
    vector<Course> courses;
    bool required;
    
    double cost[4] = {0,0,0,0};        // costs for New, Used, Rented, and Electronic versions of Textbook
    
public:
    
    // constructor for creating new textbook with ISBN and title
    Textbook(string ISBN,string title) : ISBN(ISBN),title(title) {};
    
    bool isTextbookRequired() {
        return required;
    }
    
    void printBook() {
        cout << "Title: " << getTitle() << endl;
        cout << "ISBN: " << getISBN() << endl;
        cout << "Author: " << getAuthor() << endl;
        cout << "Edition: " << getEdition() << endl;
        cout << "Publication Date: " << getPubDate() << endl;
        
        if (getCost("New") != 0) cout << "Cost for New Book: " << getCost("New") << endl;
        //else cout << "Cost for New Book: -" << endl;
        
        if (getCost("Used") != 0) cout << "Cost for Used Book: " << getCost("Used") << endl;
        //else cout << "Cost for Used Book: -" << endl;
        
        if (getCost("Rented") != 0) cout << "Cost for Rented Book: " << getCost("Rented") << endl;
        //else cout << "Cost for Rented Book: -" << endl;
        
        if (getCost("Electronic") != 0) cout << "Cost for Electronic Book: " << getCost("Electronic") << endl;
        //else cout << "Cost for Electronic Book: -" << endl;
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
    
};

// defines variables and functions for Course object
class Course {
    
    string name;
    string code = "";           // 4-letter code for department
    string courseNum = "";      // 3-digit number for the course
    //string sectionNum = "";     // 3-digit section number
    //vector<string> books;     // list of textbooks for course with ISBN, required/optional
    map<string,map<Textbook,bool>> sectionTextbooks; // list of Textbooks for a 3-digit section number and whether it's required/optional
    
public:
    
    Course(string code,string courseNum,string name):code(code),courseNum(courseNum),name(name) {};
    
    // get functions to return private variables
    string getCode() {
        return code;
    }
    
    string getCourseNum() {
        return courseNum;
    }
    
    // set functions to change private variables
    void setCode(int c) {
        code = c;
    }
    
    void setCourseNum(string n) {
        courseNum = n;
    }
    
    /*
     void addSectionNum(string s) {
     
     sectionTextbooks.insert(pair<string,Textbook>(s,NULL));
     }
     */
    
    void setName(string n) {
        name = n;
    }
    
    
    void addBooktoSection(string section, Textbook book, bool required) {
        if (sectionTextbooks.count(section) == 1) {
            
            cout << sectionTextbooks[section].second.first.getTitle(); // .insert(pair<Textbook,bool>(book,required));
        }
        else {
            cout << "Section does not exist." << endl;
        }
    }
    
    
    bool isTextbookRequired(string section, Textbook book) {
        //return sectionTextbooks[section][book].second;
        return true;
    }
    
    void listAllBooks() {
        
         map<string,map<Textbook,bool>>::iterator it = sectionTextbooks.begin();
         
         while(it != sectionTextbooks.end()) {
         
             map<Textbook,bool>::iterator books_it = (*it).second.begin();
         
             while(books_it != (*it).second.end()) {
                    if (isTextbookRequired((*it).first,(*books_it).first)) {
                        cout << "Required: " << endl;
                        Textbook book = (*books_it).first;
                        book.printBook();
                    }
                    else if (!isTextbookRequired((*it).first,(*books_it).first)) {
                        cout << "Optional: " << endl;
                        Textbook book = (*books_it).first;
                        book.printBook();
                    }
             }
        }
    }
    
    void listSectionBooks(string section) {
        
        map<Textbook,bool>::iterator books_it = sectionTextbooks[section].begin();
        
        while(books_it != sectionTextbooks[section].end()) {
            if (isTextbookRequired(section,(*books_it).first)) {
                cout << "Required: " << endl;
                Textbook book = (*books_it).first;
                book.printBook();
            }
            else if (!isTextbookRequired(section,(*books_it).first)) {
                cout << "Optional: " << endl;
                Textbook book = (*books_it).first;
                book.printBook();
            }
        }
        
    }
    
    
};


// adds new Book object to map of Textbooks <ISBN,title>
void addBooktoDB(string ISBN,string title,vector<Textbook>& textbooks) {
    
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

void addCoursetoDB(string code,string& courseNum,string& courseTitle,vector<Course>& courses) {
    
    /*
     Course* course = new Course(code,courseNum,courseTitle);
     bool found = false;
     
     for(int i = 0; i < courses.size(); i++) {
     
     if (courses[i].getCode() == code) {
     
     courses[i].setCourseNum(courseNum);
     courses[i].setName(courseTitle);
     found = true;
     }
     }
     
     // if code not found in database, add new course with code, course number, and section
     if (found == false) {
     courses.push_back(*course);
     }
     */
}

// prints all Textbook objects and their information
void printBooks(vector<Textbook>& textbooks) {
    
    /*
     if (sizeof(textbooks) != 0) {
     
     vector<Textbook>::iterator it = textbooks.begin();
     
     for(vector<Textbook>::iterator it = textbooks.begin(); it != textbooks.end(); it++) {
     
     cout << "*" << endl;
     (*it).printBook();
     }
     
     cout << "*" << endl;
     }
     */
}

// prints all Course objects and their information
void printCourses(vector<Course>& courses) {
    
    /*
     if (sizeof(courses) != 0) {
     vector<Course>::iterator it = courses.begin();
     for(vector<Course>::iterator it = courses.begin(); it != courses.end(); it++) {
     cout << (*it).getCode() << endl;
     }
     }
     */
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
    //object = regex_replace(object, regex("^ +"), "");
}

int main() {
    try {
        // initializes course list and textbook list
        vector<Course> courses;
        vector<Textbook> textbooks;
        
        string type;                                      // stores operation type
        string ISBN, bookTitle, author, date, edition;    // variables for Textbook objects
        string code, courseTitle, courseNum, sectionNum;  // variables for Course objects
        string tracker;                                   // placeholder to track other types
        double cost;                                      // Textbook cost placeholder
        
        while(type != "Q") {
            
            cout << "Input (H for help, Q to quit): ";
            cin >> type;
            if (type == "H") {
                cout << "\n******** OPTIONS ********\n\n";
                cout << "B <ISBN> <Title>\n";
                cout << "D <ISBN> <A | E | D> <value>\n";
                cout << "M <ISBN> <Cost> <N | U | R | E>\n";
                cout << "C <Department Code> <Course Number> <Name>\n";
                cout << "A <ISBN> <Department Code> <Course Number> <Section Number> <R | O>\n";
                cout << "GC <Department Code> <Course Number>\n";
                cout << "GS <Department Code> <Course Number> <Section Number>\n";
                cout << "GB <ISBN>\n";
                cout << "PB\n";
                cout << "PC\n";
                cout << "PY <MM/YYYY>\n";
                cout << "PD <Department Code>\n";
                cout << "PM <Department Code>\n\n";
            }
            else {
                
                // cases for different operation types
                switch (hashInput(type)) {
                        
                    case B:
                        
                        cin >> ISBN;                        // stores ISBN number
                        getline(cin,bookTitle);             // stores rest of line as title
                        trimLeadWhitespace(bookTitle);      // removes leading white space
                        
                        cout << "Adding " << bookTitle << " to database..." << endl;
                        addBooktoDB(ISBN,bookTitle,textbooks);  // adds book to textbook database
                        
                        cout << "Done." << endl;
                        break;
                        
                    case D:
                        
                        cin >> ISBN >> tracker;   // stores ISBN and A, E, or D
                        
                        // searches through textbook database for book with matching ISBN
                        for(int i = 0; i < textbooks.size(); i++) {
                            
                            // if found, updates textbook with author, edition, or date
                            if (textbooks[i].getISBN() == ISBN) {
                                
                                // updates author
                                if (tracker == "A") {
                                    cout << "Updating author for \"" << textbooks[i].getTitle() << "\"...\n";
                                    getline(cin,author);
                                    trimLeadWhitespace(author);
                                    textbooks[i].setAuthor(author);
                                }
                                // updates edition
                                else if (tracker == "E") {
                                    cout << "Updating edition for \"" << textbooks[i].getTitle() << " ...\n\"";
                                    getline(cin,edition);
                                    trimLeadWhitespace(edition);
                                    textbooks[i].setEdition(edition);
                                }
                                // updates publication date
                                else if (tracker == "D") {
                                    cout << "Updating publication date for \"" << textbooks[i].getTitle() << " ...\n\"";
                                    getline(cin,date);
                                    trimLeadWhitespace(date);
                                    textbooks[i].setPubDate(date);
                                }
                                else {
                                    cout << "Not a valid input." << endl;
                                }
                            }
                        }
                        
                        cout << "Done." << endl;
                        break;
                        
                    case M:
                        
                        cin >> ISBN >> cost >> tracker; // stores ISBN, cost value, and (N,U,R,E)
                        
                        // searches through textbook database for book with matching ISBN
                        for(int i = 0; i < textbooks.size(); i++) {
                            
                            // if found, updates textbook with cost for N,U,R,E
                            if (textbooks[i].getISBN() == ISBN) {
                                
                                if (tracker == "N") {
                                    cout << "Updating cost for new version of \"" << textbooks[i].getTitle() << " ...\n\"";
                                    textbooks[i].setCost("New",cost);
                                }
                                else if (tracker == "U") {
                                    cout << "Updating cost for used version of \"" << textbooks[i].getTitle() << " ...\n\"";
                                    textbooks[i].setCost("Used",cost);
                                }
                                else if (tracker == "R") {
                                    cout << "Updating cost for rented version of \"" << textbooks[i].getTitle() << " ...\n\"";
                                    textbooks[i].setCost("Rented",cost);
                                }
                                else if (tracker == "E") {
                                    cout << "Updating cost for electronic version of \"" << textbooks[i].getTitle() << " ...\n\"";
                                    cout << textbooks[i].getCost("Electronic") << endl;
                                    textbooks[i].setCost("Electronic",cost);
                                    cout << textbooks[i].getCost("Electronic") << endl;
                                }
                            }
                        }
                        
                        cout << "Done." << endl;
                        break;
                        
                    case C:
                        
                        cin >> code >> courseNum;
                        getline(cin,courseTitle);
                        trimLeadWhitespace(courseTitle);
                        
                        cout << "Adding course " << courseTitle << " to course database...\n";
                        addCoursetoDB(code,courseNum,courseTitle,courses);
                        
                        cout << "Done.\n";
                        break;
                        
                    case A:
                        
                        // assign a book to a course
                        cin >> ISBN >> code >> courseNum >> sectionNum >> tracker;
                        bool required;
                        
                        /*
                         // would work better with map instead of vector
                         for(int i = 0; i < courses.size(); i++) {
                         if (code == courses[i].getCode()) {
                         for(int i = 0; i < textbooks.size(); i++) {
                         if (textbooks[i].getISBN() == ISBN) {
                         if (tracker == "R") {
                         //courses[i].addBooktoCourse(textbooks[i]->getISBN(),true);
                         }
                         else if (tracker == "O") {
                         //courses[i].addBooktoCourse(book->getISBN(),false);
                         }
                         }
                         }
                         }
                         else {
                         cout << "Course doesn't exist!" << endl;
                         }
                         }
                         */
                        
                        break;
                        
                    case GC:
                        
                        // Print the books required and optional for all sections of a given course
                        cout << "Required: " << endl;
                        cin >> code >> courseNum;
                        //Course course(code,courseNum);
                        //course.listSectionBooks();
                        
                        break;
                        
                    case GS:
                        
                        // Print the books required and optional for a given section of a course
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
                        
                        // Print all books with known publication dates in the given month/year or later.
                        break;
                        
                    case PD:
                        
                        // Print the list of all books used in a department, given by department code. Do not list by section
                        break;
                        
                    case PM:
                        
                        // Print the AVERAGE minimum and maximum costs of all books in a department
                        break;
                        
                    default:
                        break;
                        
                };
            }
            
            
            cout << "---" << endl;
        }
    }
    catch(exception& e) {
        cout << "Exception: " << e.what() << endl;
    }
}











