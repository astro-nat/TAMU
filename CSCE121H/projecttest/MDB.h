#include "std_lib_facilities_4.h"


class MDBObject{


        protected:
        string _name;
        string _photo;


        MDBObject(string name, string photo): _name(name), _photo(photo) {}


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
        Actor(string name, string photo): MDBObject(name, photo) {}
};

class Movie : public MDBObject{
        
string _year;
vector<string> _tags;
vector<Actor> _actors;


        public:


Movie(string title, string photo, string year, vector<string> tags, vector<Actor> actors)
        : MDBObject(title, photo), _year(year), _tags(tags), _actors(actors) {}
        


string get_year(){
        return _year;
}
        
vector<string> get_tags(){
        return _tags;
}
        
vector<Actor> get_actors(){
        return _actors;
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
