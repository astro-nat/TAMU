#include <iostream>    // for i/o
#include <sstream>     // for string streams
#include "Graph.h"     // next 3 are for graphics library
#include "GUI.h"
#include "Window.h"
#include "MDB.h"

using namespace Graph_lib;
using namespace std;

struct MyMDB_Window : Graph_lib::Window {       // inherits from Window
	
	private:
	vector<Movie> movies;		
	vector<Actor> actors;
	
	Button search_button;
	Button quit_button;
	In_box search_box;
	Menu search_menu;
	Button smenu_button;
	
	public:
	MyMDB_Window(Point xy, int w, int h, const string& title,
					vector<Movie>& m, vector<Actor>& a)
				: Window(xy, w, h, title),
				movies(m), actors(a),
				search_button(Point(x_max()-150,0),   // location of button
							70, 20,                 // dimensions of button
							"Search",           // label of button
							cb_next),
				quit_button(Point(x_max()-70,0),    // location of button
							70, 20,                 // dimensions of button 
							"Quit",                 // label of button
							cb_quit),
				search_box(Point(x_max()/2-75,30),
							150, 20,
							"Search:"),
				search_menu(Point(20,30),   // location of menu
							70, 20,                 // dimensions of menu
							Menu::vertical,         // list menu items vertically
							"Search Options:"),
				smenu_button(Point(x_max()-80,30),  // location of menu button
							80, 20,                // dimensions of button 
							"Search Options: ",          // label of button
							cb_smenu)
	{
		attach(search_button);
		attach(quit_button);
		attach(search_box);
		
		search_menu.attach(new Button(Point(0,0),0,0,"Movie Title", cb_movie_title));
		search_menu.attach(new Button(Point(0,0),0,0,"Movie Year", cb_movie_year));
		search_menu.attach(new Button(Point(0,0),0,0,"Actor", cb_actor));
		search_menu.attach(new Button(Point(0,0),0,0,"Tag", cb_tag));
		attach(search_menu);
		search_menu.hide();
		
		attach(smenu_button);
	}
	
	void hide_menu() {     
		search_menu.hide(); 
		smenu_button.show(); 
	}

	void title_pressed() {
    
	}

	void year_pressed() {
    
	}

	void actor_pressed() {
    
	}
	

	void smenu_pressed() {
		smenu_button.hide();    
		search_menu.show();
	}

	void next() {
		
	}

	void quit() {
		//function to save data
		hide();
	}
	
	
  // callback functions; declared here and defined below.

  static void cb_movie_title(Address, Address);
  static void cb_movie_year(Address, Address);
  static void cb_actor(Address, Address);
  static void cb_tag(Address, Address);
  static void cb_smenu(Address, Address);
  static void cb_next(Address, Address);
  static void cb_quit(Address, Address pw) {
	reference_to<MyMDB_Window>(pw).quit();
  }
};


