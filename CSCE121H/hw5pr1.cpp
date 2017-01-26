/* Write a program that implements a rudimentary movie database, called 
MyMDB. It will interact with the user to get and display information 
about movies. The data will be stored in a file so that it will persist 
between invocations of the program. You will need to devise a format for 
storing the information in the file.

The information for each movie should include, at a minimum, the 
following:

title
year
the names of 3 actors/actresses in the movie
genre (e.g., mystery, comedy, horror)
a list of scores (each score should be between 1 and 10)

When the program starts executing, it should query the user for the name 
of the file from which the data is to be obtained. Then it should 
present the user with the following menu of options (you can include 
more options if you like):

enter a new movie and its information
view all information about an existing movie
update the information about an existing movie (including the 
possibility of entering an additional score)
display the average/min/max/median score for a movie
output the titles of all movies starring a particular actor
output the titles of all movies made in a particular year
Before exiting, the program must write the information about all the 
movies to the file. */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

class Year 
{
private:
	static const int min = 1800;
	static const int max = 2014;
	int y;
public:
	class Invalid{};
	Year(int x) : y(x) 
	{
		if (x<min || x>max) 
			throw Invalid{};
	}
	int year()
	{
		return y;
	}
};

//create MyMDB class --> database
class MyMDB {
public:
	enum Genre {mystery,comedy,horror,romance,documentary,family};
private:
	string title; 
	Year year;
	string actor1;
	string actor2;
	string actor3;
	Genre genre;
	vector<double> scores;
public:
	string gettitle() { return title; };
	Year getyear() { return year; };
	string getactors()	{ return actor1; return actor2; return 
actor3; };
	string getgenre()
	{
		switch(genre)
		{
			case 0:
				return "Mystery";
				break;
			case 1:
				return "Comedy";
			case 2:
				return "Horror";
			case 3:
				return "Romance";
			case 4:
				return "Documentary";	
			case 5:
				return "Family";
			default:
				return "";
		}
	};
	double getmedscore(vector <double> scores) 
	{ 
		double median;
		sort(scores.begin(), scores.end());
		
		if (scores.size() % 2 == 0)
		{
			median = (scores[scores.size() / 2-1] + 
scores[scores.size() / 2]) / 2;
		}
		else
		{
			median = scores[scores.size() / 2];
		}
		return median;
	};
	double getminscore() 
	{ 
		/* return minimum score */ 
		double minimum;
		sort(begin(scores), end(scores));
		minimum = scores[0];
		return minimum;
	};
	double getmaxscore() 
	{ 
		/* return maximum score */
		double maximum;
		sort(begin(scores), end(scores));
		maximum = scores[scores.size() - 1];
		return maximum;
	};
	double getmeanscore(vector<int> scores) 
	{ 
		double sum;
		sort(scores.begin(), scores.end());
		for (double i = 0; i <= scores[scores.size() - 1]; i++)
			sum = 0 + i;
		double average = (sum / scores.size());
		return average;
	};
	
	//Format for storing information
	MyMDB(string title,int year,string actor1,string actor2, string 
actor3,Genre genre,double 
score):title(title),year(year),actor1(actor1),actor2(actor2),actor3(actor3),genre(genre),scores(score) 
{}

};


void showMenu()
{
	cout << "Welcome to the movie database\n";
	cout << "1. Add a movie to the list\n";
	cout << "2. View information about a movie.\n";
	cout << "3. Update the file.\n";
	cout << "4. Display average, min, max, or median score of 
movie.\n";
	cout << "5. List all movies starring a particular 
actor/actress.\n";
	cout << "6. List all movies made in a particular year.\n";
};

int main() {
	//ability to read and write information
	try {
		string userinput;
		ofstream myfile;
		//ask user for file name. if it equals the file name 
assigned to the variable "filename" (or choose something else), give 
menu options (if/else statements? or case?)
		cout << "Please enter file name: ";
		cin >> userinput;
		myfile.open(userinput);
		MyMDB movie;
		myfile << movie.gettitle() << endl << movie.getyear() << 
endl << movie.getactors() << endl << movie.getgenre() << endl << 
movie.getscores << endl;
		char menuop;
		showMenu();
		cin >> menuop;
		switch(menuop)
		{
			//1. enter new movie and its information 
(separate couts)
			case '1':
				ifstream myfile;
				break;
			//2. View all information (read file)
			case '2':
				string line;
				if (myfile.is_open())
				{ 
					while ( getline (myfile,line))
					{
					cout << line << endl;
					}
				else
					cout << "Cannot open file.";
				}
				myfile.close();
				break;
			//3. Update the information (write file)
			case '3':
				break;
			//4. Display average/min/max/median score for 
movie
			case '4':
				getmeanscore();
				getminscore();
				getmaxscore();
				getmedscore();
				break;
			//5. Output titles of all movies starring 
particular actor
			case '5':
				break;
			//6. Output titles of all movies made in 
particular year
			case '6':
				break;
		}
		cin >> iname;
		ifstream ist {iname};
		if (!ist) error("can't open input file ",iname);
		
		//Before exiting, program writes information to the 
file.
		
	catch(exception& e)
		cout << "Error occurred." << endl;
	}
	
	return 0;
}
};
