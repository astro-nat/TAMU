#include "MDB_GUI.h"

//Format of the Movies In Text File:
/*
 TITLE
 YEAR
 JPG
 number of actors
 ACTOR
 ACTOR
 ACTOR
 ...
 number of tags
 TAG
 TAG
 ...
 ~~~~~
 
 **/

//Remove carriage returns
string& rcr(string& in){
	string::iterator begin = in.begin();
	while(begin != in.end())
		if(*begin == 13)
			begin = in.erase(begin);
		else
			begin++;
	return in;
}

string getline(istream& ist){
	string str;
	getline(ist, str);
	return rcr(str);
}
 
void load_movies(vector<Movie>& m)
{
    
    ifstream ist{"MDB.txt"};										//OPEN FILE FOR READING
    if(!ist) error("can't open database file", "MDB.txt");			//MAKE SURE IT IS OPENABLE

    int counter = 0;
	
    while(ist)
    {
        string temp;
		
        string title = getline(ist);
		string year = getline(ist);
		string photo = getline(ist);
		string number_of_actors = getline(ist);
		vector<Actor> actors;
        int tre = stoi(number_of_actors);
        for(int i = 0; i < tre; i++)
        {	
			string actor = getline(ist);
            actors.push_back(Actor{actor, actor + ".jpg"});
        }
        
        string number_of_tags = getline(ist);
		vector<string> tags;
        int tagre = stoi(number_of_tags);
        for(int i = 0; i < tagre; i++)
        {
            string temptag = getline(ist);
            tags.push_back(temptag);
        }
        getline(ist, temp);
        m.push_back(Movie{title, photo, year, tags, actors});
        counter++;
    }
}

void delete_duplicates(vector<Actor>& act)
{
	for (int i = 0; i <act.size(); i++)
	{
		for(int j = 0; j<act.size(); j++)
		{
			if(act[i].get_name() == act[j].get_name() && i != j)
			{
				act.erase(act.begin() + j);
			}
		}
	}
}

void load_actors(vector<Movie>& m, vector<Actor>& a)
{
	for(int p = 0; p<m.size();p++)
	{
		for(int k = 0; k < m[p].get_number_of_actors(); k++)
		{
			a.push_back(m[p].get_actors()[k]);
		}
	}
	delete_duplicates(a);
}

int main()
{
	vector<Movie> movies;
	vector<Actor> actors;
    load_movies(movies);
	load_actors(movies, actors);
	MyMDB_Window win{Point{100, 100}, 1000, 800, "MyMDB", movies, actors};
	return 0;
}