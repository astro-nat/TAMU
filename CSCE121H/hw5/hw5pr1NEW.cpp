/* Write a program that implements a rudimentary movie database, called MyMDB. It will interact with the user to get and display information about movies. The data will be stored in a file so that it will persist between invocations of the program. You will need to devise a format for storing the information in the file.

The information for each movie should include, at a minimum, the following:

title
year
the names of 3 actors/actresses in the movie
genre (e.g., mystery, comedy, horror)
a list of scores (each score should be between 1 and 10)

When the program starts executing, it should query the user for the name of the file from which the data is to be obtained. Then it should present the user with the following menu of options (you can include more options if you like):

enter a new movie and its information
view all information about an existing movie
update the information about an existing movie (including the possibility of entering an additional score)
display the average/min/max/median score for a movie
output the titles of all movies starring a particular actor
output the titles of all movies made in a particular year
Before exiting, the program must write the information about all the movies to the file. */

#include "std_lib_facilities_4.h"

using namespace std;

//movie class
	//declare variables
	//functions available
		//print everything
		//change title, year, actor, genre
		//get statistics from score vector (mean, min, max, median)
		//add score to score vector

//database class
	//vector of movies
	//search through movies for certain factors (in this code --> actor and year)
	//add movie to movie vector

class Movie {
public:
	enum Genre {mystery,comedy,horror,romance,documentary,family};
private:
	string title; 
	int year;
	string actor1;
	string actor2;
	string actor3;
	Genre genre;
	vector<double> scores;
public:
	string gettitle() { return title; };
	//void settitle() { title = userinput; };
	Year getyear() { return year; };
	string getactors()	{ return actor1; return actor2; return actor3; };
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
	}
	string getscores() {
		for (int i = 0; (unsigned)i <= scores.size(); i++)
			return scores[i];
	}
	
				
	double getmedscore(vector <double> scores) 
	{ 
		double median;
		sort(scores.begin(), scores.end());
		
		if (scores.size() % 2 == 0)
		{
			median = (scores[scores.size() / 2-1] + scores[scores.size() / 2]) / 2;
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

};

void pickMenu() {
	char menuop;
	while(cin >> menuop)
	switch(menuop)
		{
			//1. enter new movie and its information (separate couts)
			case '1':
				ifstream myfile;
				Movie m;
				m.gettitle();
				m.getyear();
				//m.get
				break;
			//2. View all information (read file)
			case '2':
				cout << "Here is the movie information.\n";
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
				cout << "Type the necessary information to update the movie file\n.";
				ofstream myfile;
				myfile >> movie.gettitle();
				myfile >> movie.getyear();
				myfile >> movie.getactors();
				myfile >> movie.getgenre();
				myfile >> movie.getscores()
				break;
			//4. Display average/min/max/median score for movie
			case '4':
				cout << "Here is the average, minimum, maximum, and median scores.\n";
				getmeanscore();
				getminscore();
				getmaxscore();
				getmedscore();
				break;
			//5. Output titles of all movies starring particular actor
			case '5':
				cout << "What actor are you searching for?\n";
				cin >> useractor;
				for (int i = 0; i <= movies.size();i++)
					if movies[i] == useractor {
						cout << movies[i] << endl; }
					else {
						cout << "There are no movies with that actor."; }
				break;
			//6. Output titles of all movies made in particular year
			case '6':
				cout << "What year are you searching for?\n";
				cin >> useryear;
				for (int i = 0; i <= movies.size();i++)
					if movies[i] == useryear {
						cout << movies[i] << endl; }
					else {
						cout << "There are no movies from that year."; }
				break;
		}
		


void showMenu()
{
	cout << "Welcome to the movie database\n";
	cout << "1. Add a movie to the list\n";
	cout << "2. View information about a movie.\n";
	cout << "3. Update the file.\n";
	cout << "4. Display average, min, max, or median score of movie.\n";
	cout << "5. List all movies starring a particular actor/actress.\n";
	cout << "6. List all movies made in a particular year.\n";
};


int main() {
	//ability to read and write information
	try {
		/* string userinput;
		vector<MyMDB> movies;
		ifstream myfile;
		//ask user for file name. if it equals the file name assigned to the variable "filename" (or choose something else), give menu options (if/else statements? or case?)
		cout << "Please enter file name: ";
		cin >> userinput;
		myfile.open(userinput);
		char menuop;
		while(true) {
			showMenu();
			pickMenu();
		}
		cin >> menuop;
		
		
		//Before exiting, program writes information to the file.
		
	catch(exception& e)
		cout << "Error occurred." << endl;
	}
	
	return 0;
}
};