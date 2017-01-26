/*
 * MDB.h contains MDBObject, Movie, and Actor.
*/

#include "std_lib_facilities_4.h"

class MDBObject{

	protected:
	string _name;
	string _photo;

	MDBObject(string name, string photo = "null.jpg") : _name(name), _photo(photo) {}
	
	public:
	string get_name(){
		return _name;
	}

	string get_photo(){
		return _photo;
	}

};

class Actor : public MDBObject{
	public:
	Actor(string name, string photo = "null.jpg") : MDBObject(name, photo){}
};

class Movie : public MDBObject{
	
	string _year;
	vector<string> _tags;
	vector<Actor> _actors;

	public:

	Movie(string title, string photo, string year, vector<string> tags, vector<Actor> actors)
	: MDBObject(title, photo), _tags(tags), _actors(actors), _year(year) {}

	string get_year(){
		return _year;
	}
		
	vector<string> get_tags(){
		return _tags;
	}
		
	vector<Actor> get_actors(){
		return _actors;
	}
	
	int get_number_of_actors(){
		return _actors.size();
	}
	
	int get_number_of_tags(){
		return _tags.size();
	}
		
	//Setters - Title and photo excluded
	void set_year(string year){
		_year = year;
	}
		
	void set_tags(vector<string> tags){
		_tags = tags;
	}
		
	void set_actors(vector<Actor> actors){
		_actors = actors;
	}
};