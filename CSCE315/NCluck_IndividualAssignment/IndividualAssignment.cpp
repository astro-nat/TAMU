/********************************************************************************
 
 Purpose: Create a program that can be used for keeping track of textbooks
 required and recommended for classes and the cost of those textbooks.
 
 ********************************************************************************/

#include <iostream>
#include <numeric>
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
    
    bool required;

public:
    
    double cost[4] = {0,0,0,0};        // costs for New, Used, Rented, and Electronic versions of Textbook

    // constructor for creating new textbook with ISBN and title
    Textbook(string ISBN,string title) : ISBN(ISBN),title(title) {};
    
    // checks if textbook is required or optional
    bool isTextbookRequired() {
        return required;
    }
    
    // prints all information about a textbook
    void printBook() {
        
        cout << "Title: " << getTitle() << endl;
        cout << "ISBN: " << getISBN() << endl;
        cout << "Author: " << getAuthor() << endl;
        cout << "Edition: " << getEdition() << endl;
        cout << "Publication Date: " << getPubDate() << endl;
        
        // prints costs of different versions of textbook, if they exist
        if (getCost("New") != 0) {
            cout << "Cost for New Book: " << getCost("New") << endl;
        }
        
        if (getCost("Used") != 0) {
            cout << "Cost for Used Book: " << getCost("Used") << endl;
        }
        
        if (getCost("Rented") != 0) {
            cout << "Cost for Rented Book: " << getCost("Rented") << endl;
        }
        
        if (getCost("Electronic") != 0) {
            cout << "Cost for Electronic Book: " << getCost("Electronic") << endl;
        }
        
    }
    
    // returns ISBN
    string getISBN() {
        return ISBN;
    }
    
    // returns title
    string getTitle() {
        return title;
    }
    
    // return author
    string getAuthor() {
        return author;
    }
    
    // returns edition
    string getEdition() {
        return edition;
    }
    
    // returns publication date
    string getPubDate() {
        return pubDate;
    }
    
    // returns cost based on version type
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
    
    // sets ISBN
    void setISBN(string i) {
        ISBN = i;
    }
    
    // sets title
    void setTitle(string t) {
        title = t;
    }
    
    // sets author
    void setAuthor(string a) {
        author = a;
    }
    
    // sets edition
    void setEdition(string e) {
        edition = e;
    }
    
    // sets publication date
    void setPubDate(string d) {
        pubDate = d;
    }
    
    // sets cost based on version
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
    
}; // end Textbook class

// defines variables and functions for Course object
class Course {
    
    string name;                                        // name of Course
    string code = "";                                   // 4-letter code for department
    string courseNum = "";                              // 3-digit number for the course
    vector<tuple<string,Textbook*,bool>> sectionTextbooks;
    //map<string,map<Textbook*,bool>> sectionTextbooks;   // list of Textbooks for 3-digit section number and if it's required/optional
    
public:
    
    // Course constructor
    Course(string code,string courseNum,string name):code(code),courseNum(courseNum),name(name) {};
    
    // gets Course code
    string getCode() {
        return code;
    }
    
    // gets Course number
    string getCourseNum() {
        return courseNum;
    }
    
    // sets Course code
    void setCode(int c) {
        code = c;
    }
    
    // sets Course number
    void setCourseNum(string n) {
        courseNum = n;
    }
    
    // returns a Textbook with a specific ISBN
    Textbook* findTextbook(string ISBN) {
        
        // goes through section/Textbook/required mapping
        for(int i = 0; i < sectionTextbooks.size(); i++) {
            
            // if ISBN found, return Textbook
            if (get<1>(sectionTextbooks[i])->getISBN() == ISBN){
                return get<1>(sectionTextbooks[i]);
            }
        }
        
        cout << "Textbook not found." << endl;
        return NULL;
    }
    
    // gets Course name
    string getName() {
        return name;
    }
    
    // sets Course name
    void setName(string n) {
        name = n;
    }
    
    // adds a Textbook to a specific section and includes whether it is required/optional
    void addBooktoSection(string section, Textbook* book, bool required) {
        
        tuple<string,Textbook*,bool> newBook(section,book,required);
        /*
        get<0>(newBook) = section;
        get<1>(newBook) = book;
        get<2>(newBook) = required;
        */
        sectionTextbooks.push_back(newBook);
    }
    
    // checks if textbook is required for a specific section
    bool isTextbookRequired(string section, Textbook book) {
        
        // iterates through Textbook/section/required mapping
        for(int i = 0; i < sectionTextbooks.size(); i++) {
            
            // if section and book ISBN match, return whether it's required
            if ((get<0>(sectionTextbooks[i]) == section) && ((get<1>(sectionTextbooks[i])->getISBN()) == book.getISBN()))
                
                return get<2>(sectionTextbooks[i]);
        }
        
        cout << "Section or textbook not found." << endl;
        return false;
    }
    
    // prints minimum and maximum average cost of all textbooks belonging to a course with certain code
    void printMinMax(string c) {
        
        // initializes min and max variables
        double min_num = 100000000;
        double max_num = 0;
        
        // stores all minimum and maximum values
        vector<int> minimum;
        vector<int> maximum;
        
        // checks for a course code
        if(c == code) {
            
            // iterates through section/Textbook map
            for(int i = 0; i < sectionTextbooks.size(); i++) {
                // iterates through Textbook/required map in each section
                
                // for each Textbook costs, find minimum and maximum value
                for(int j = 0; j < 3; j++) {
                    
                    // collects each version cost for textbook
                    double num = (*get<1>(sectionTextbooks[i])).cost[j];
                    
                    // finds minimum cost from all types of a textbook
                    if (num < min_num) {
                        min_num = num;
                    }
                    
                    // finds maximum cost from all types of a textbook
                    if (num > max_num) {
                        max_num = num;
                    }
                }
                
                // collects minimum and maximum costs from a textbook
                minimum.push_back(min_num);
                maximum.push_back(max_num);
            }
        }
        
        // takes average of all minimum costs of textbooks and prints it
        float min_average = accumulate( minimum.begin(), minimum.end(), 0.0)/minimum.size();
        cout << "Minimum average: " << min_average << endl;
        
        // takes average of all maximum costs of textbooks and prints it
        float max_average = accumulate( maximum.begin(), maximum.end(), 0.0)/maximum.size();
        cout << "Maximum avearge: " << max_average << endl;
        
    } // end function
    
    // prints a list of all books for a course
    void listAllBooks() {
    
        vector<tuple<string,Textbook*,bool>>::iterator it = sectionTextbooks.begin();
        
        if (sectionTextbooks.size() > 0) {
         
            // goes through all sections and textbooks
            for(int i = 0; i < sectionTextbooks.size(); i++) {
            
                // saves section and textbook
                string section = get<0>(sectionTextbooks[i]);
                Textbook textbook = *(get<1>(sectionTextbooks[i]));
                
                // lists all required books for course
                if (isTextbookRequired(section,textbook)) {
                    cout << "Required: " << endl;
                    textbook.printBook();
                }
                
                // lists all optional books for course
                else if (isTextbookRequired(section,textbook) == false) {
                    cout << "Optional: " << endl;
                    textbook.printBook();
                }
            }
        }
    }
    
    // prints a list of all books for a course with a specific section
    void listSectionBooks(string section) {
        
        // goes through all sections and textbooks
        for(int i = 0; i < sectionTextbooks.size(); i++) {
            
            Textbook textbook = *(get<1>(sectionTextbooks[i]));
            
            // lists all required books for section
            if (isTextbookRequired(section,textbook)) {
                cout << "Required: " << endl;
                textbook.printBook();
            } // end if
            
            // lists all optional books for section
            else if (isTextbookRequired(section,textbook) == false) {
                cout << "Optional: " << endl;
                textbook.printBook();
            }
        }
    }
    
}; // end class


// adds new Book object to map of Textbooks <ISBN,title>
void addBooktoDB(string ISBN,string title,vector<Textbook>& textbooks) {
    
     Textbook* book = new Textbook(ISBN,title);     // creates new textbook with ISBN and title
     bool found = false;                            // will be used to find existing ISBN number in database
     
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
} // end function

// adds Course to courses database
void addCoursetoDB(string code,string& courseNum,string& courseTitle,vector<Course>& courses) {
    
     Course* course = new Course(code,courseNum,courseTitle);   // creates new course with code, course number, and title
     bool found = false;                                        // will be used to find existing course
    
     // searches if course is in database. If so, update name
     for(int i = 0; i < courses.size(); i++) {
     
         if ((courses[i].getCode() == code) && (courses[i].getCourseNum() == courseNum)) {
             courses[i].setName(courseTitle);
             found = true;
         }
    }
     
    // if code not found in database, add new course with code, course number, and name
    if (found == false) {
        courses.push_back(*course);
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
             
             cout << (*it).getCode() << " " << (*it).getCourseNum() << " " << (*it).getName() << endl;
             
         }
     }
}

// changes string input to enum to use for switch case
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
    
    // added to remove possible return type warning
    return PM;
}

// gets rid of leading white space
void trimLeadWhitespace(string& object) {
    object = regex_replace(object, regex("^ +"), "");
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
        
        // if input is Q, exit program
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
                        
                    // adds new book to Textbook database
                    case B:
                        
                        cin >> ISBN;                        // stores ISBN number
                        getline(cin,bookTitle);             // stores rest of line as title
                        trimLeadWhitespace(bookTitle);      // removes leading white space
                        
                        cout << "Adding " << bookTitle << " to database..." << endl;
                        addBooktoDB(ISBN,bookTitle,textbooks);  // adds book to textbook database
                        
                        cout << "Done." << endl;
                        break;
                    
                    // updates author, edition, or publication date for a book
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
                                    cout << "Updating publication date for \"" << textbooks[i].getTitle() << "\" ...\n";
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
                    
                    // updates cost of Textbook for new, used, rented, electronic versions
                    case M:
                        
                        cin >> ISBN >> cost >> tracker; // stores ISBN, cost value, and (N,U,R,E)
                        
                        // searches through textbook database for book with matching ISBN
                        for(int i = 0; i < textbooks.size(); i++) {
                            
                            // if found, updates textbook with cost for N,U,R,E
                            if (textbooks[i].getISBN() == ISBN) {
                                
                                // update new cost
                                if (tracker == "N") {
                                    cout << "Updating cost for new version of \"" << textbooks[i].getTitle() << "\" ...\n";
                                    textbooks[i].setCost("New",cost);
                                }
                                // update used cost
                                else if (tracker == "U") {
                                    cout << "Updating cost for used version of \"" << textbooks[i].getTitle() << "\" ...\n";
                                    textbooks[i].setCost("Used",cost);
                                }
                                // update rented cost
                                else if (tracker == "R") {
                                    cout << "Updating cost for rented version of \"" << textbooks[i].getTitle() << "\" ...\n";
                                    textbooks[i].setCost("Rented",cost);
                                }
                                // update electronic cost
                                else if (tracker == "E") {
                                    cout << "Updating cost for electronic version of \"" << textbooks[i].getTitle() << "\" ...\n";
                                    cout << textbooks[i].getCost("Electronic") << endl;
                                    textbooks[i].setCost("Electronic",cost);
                                    cout << textbooks[i].getCost("Electronic") << endl;
                                }
                            }
                        }
                        
                        cout << "Done." << endl;
                        break;
                     
                    // adds new course to course database
                    case C:
                        
                        cin >> code >> courseNum;
                        getline(cin,courseTitle);
                        trimLeadWhitespace(courseTitle);
                        
                        cout << "Adding course " << courseTitle << " to course database...\n";
                        addCoursetoDB(code,courseNum,courseTitle,courses);
                        
                        cout << "Done.\n";
                        break;
                    
                    // assign a book to a course
                    case A:
                        
                        cin >> ISBN >> code >> courseNum >> sectionNum >> tracker;
                        bool required;
                        
                        // R means book is required, O means book is optional
                        if(tracker == "R") {
                            
                            required = true;
                        }
                        else if (tracker == "O") {
                            
                            required = false;
                        }
                        
                        // looks for course with code and course number in database. If it exists, adds the book to the given section number for that course
                        for(int i = 0; i < courses.size(); i++) {
                            
                            if(courses[i].getCode() == code && courses[i].getCourseNum() == courseNum){
                                
                                courses[i].addBooktoSection(sectionNum,courses[i].findTextbook(ISBN),required);
                            }
                        }
                        
                        cout << "Done.\n";
                        break;
                        
                    // prints all books required and optional for a course
                    case GC:
                        
                        cin >> code >> courseNum;
                        
                        for(int i = 0; i < courses.size(); i++) {
                            
                            if(courses[i].getCode() == code && courses[i].getCourseNum() == courseNum){
                                
                                courses[i].listAllBooks();
                            }
                        }
                        
                        cout << "Done.\n";
                        break;
                        
                    // Print the books required and optional for a given section of a course
                    case GS:
                        
                        if(courses.size() > 0) {
                            
                            // goes through all courses
                            for(int i = 0; i < courses.size(); i++) {
                            
                                // if code and course number match, list all books for a section
                                if((courses[i].getCode() == code) && (courses[i].getCourseNum() == courseNum)) {
                                
                                    // list section books
                                    courses[i].listSectionBooks(sectionNum);
                                }
                            }
                        }
                        
                        cout << "Done.\n";
                        break;
                    
                    // lists all information about a book
                    case GB:
                        
                        cin >> ISBN;     // collects ISBN number
                        
                        // search for book with matching ISBN number, then print it
                        if(textbooks.size() > 0) {
                            
                            for(int i = 0; i < textbooks.size(); i++) {
                                
                                if (ISBN == textbooks[i].getISBN()) {
                                    
                                    cout << "*\n";
                                    textbooks[i].printBook();
                                    cout << "*\n";
                                }
                            }
                        }
                        
                        cout << "Done.\n";
                        break;
                        
                    // prints all books
                    case PB:
                        
                        cout << "\nPrinting all books... \n\n";
                        printBooks(textbooks);
                        
                        cout << "Done.\n";
                        break;
                    
                    // prints all courses
                    case PC:
                        
                        // prints all courses in the course database
                        cout << "\nPrinting all courses... \n\n";
                        printCourses(courses);
                        
                        cout << "Done.\n";
                        break;
                        
                    // Print all books with known publication dates in the given month/year or later
                    case PY:
                        
                        cin >> date;
                        
                        if (textbooks.size() > 0) {
                            
                            // goes through textbook database and finds matching date
                            for(int i = 0; i < textbooks.size(); i++) {
                               
                                // if date matches, print book info
                                if (date == textbooks[i].getPubDate()) {
                                    
                                    cout << "*\n";
                                    textbooks[i].printBook();
                                    cout << "*\n";
                                }
                            }
                        }
                        
                        cout << "Done.\n";
                        break;
                        
                    // Print the list of all books used in a department, given by department code. Do not list by section
                    case PD:
                        
                        cin >> code;
                        
                        if (courses.size() > 0) {
                            
                            // goes through courses and finds matching code, then prints associated textbooks
                            for(int i = 0; i < courses.size(); i++) {
                                
                                // if code matches, print all books for department
                                if (code == courses[i].getCode()) {
                                    
                                    cout << "*\n";
                                    courses[i].listAllBooks();
                                    cout << "*\n";
                                }
                            }
                        }
                        
                        cout << "Done.\n";
                        break;
                    
                    // Print the AVERAGE minimum and maximum costs of all books in a department
                    case PM:
                        
                        cin >> code;
                        
                        // goes through courses and finds matching course code. If code matches, print total average min and max for courses with that code
                        for(int i = 0; i < courses.size(); i++) {
                            
                            if (code == courses[i].getCode()) {
                                
                                cout << "*\n";
                                courses[i].printMinMax(code);
                                cout << "*\n";
                            }
                        }
                        
                        cout << "Done.\n";
                        break;
                        
                    default:
                        break;
                };
            }
            
            
            cout << "---" << endl;
        } // end while
    } // end try
    
    catch(exception& e) {
        cout << "Exception: " << e.what() << endl;
    }
    
} // end main











