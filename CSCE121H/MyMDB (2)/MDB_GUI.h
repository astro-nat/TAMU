/*
 * MDB_GUI.h contains Thumbnail and MyMDB_Window.
*/

#include "MDB.h"
#include "Graph.h"
#include "GUI.h"
#include "Window.h"

using namespace Graph_lib;

//Converts a string to lower case
string lcconvert(string str){
	for(int i = 0; i < str.size(); i++)
		if(str[i] > 64 && str[i] < 91)
			str[i] += 32;
	return str;
}	

//Converts an int to string
string itos(int i){
	ostringstream o;
	o << i;
	return o.str();
}

//Will not crash if it fails
int safe_stoi(string s){
	try{
		return stoi(s);
	}catch(invalid_argument){
		return -1;
	}
}

bool exists(string file){
	ifstream in{file};
	in.get();
	return in;
}

class Thumbnail : public Widget{

	Image* photo = nullptr;
	Button* title = nullptr;
	MDBObject* _obj = nullptr;
	bool attached = false;
	
	static void callback(Address a, Address b){
		//Display obj, either an actor or a movie
	}
	
	public:
	Thumbnail(int x, int y, MDBObject* obj) : Widget(Point{x, y}, 120, 150, "", 0), _obj(obj) {
		photo = new Image{Point{x + 20, y + 5}, exists("images/" + obj->get_photo()) ? "images/" + obj->get_photo() : "images/null.jpg"};
		title = new Button{Point{x + 5, y + 130}, 120, 20, _obj->get_name(), callback};
	}
	
	~Thumbnail(){
		delete photo;
		delete title;
	}

	void attach(Graph_lib::Window& window){
		if(attached)
			return;
		window.attach(*photo);
		window.attach(*title);
		attached = true;
	}
	
	void detach(Graph_lib::Window& window){
		if(!attached)
			return;
		window.detach(*photo);
		window.detach(*title);
		attached = false;
	}
	
};

class MyMDB_Window;

static MyMDB_Window* instance = nullptr;

class MyMDB_Window : public Graph_lib::Window {       // inherits from Window
	
	private:
	vector<Movie>& movies;		
	vector<Actor>& actors;
	
	vector<Thumbnail*> thumbnails;
	int rows;
	int columns;
	int pages;
	int page;
	
	constexpr static int defaultx = 70;
	constexpr static int defaulty = 150;
	
	Button next_button;
	Button last_button;
	Button goto_button;
	Button grid_button;
	Button quit_button;
	In_box search_box;
	In_box rows_box;
	In_box columns_box;
	In_box page_box;
	Menu search_menu;
	Text page_text;
	Text search_text;
	
	public:
	MyMDB_Window(Point xy, int w, int h, const string& title,
					vector<Movie>& m, vector<Actor>& a)
				: Window(xy, w, h, title),
				movies(m), actors(a),
				next_button(Point(x_max()-270,20),   // location of button
							120, 20,                 // dimensions of button
							"Next Page",           // label of button
							cb_next),
				last_button(Point(x_max()-270,40),   // location of button
							120, 20,                 // dimensions of button
							"Previous Page",           // label of button
							cb_last),
				grid_button(Point(x_max()-270,160),   // location of button
							120, 20,                 // dimensions of button
							"Change Grid Size",           // label of button
							cb_grid),
				page_text(Point(x_max()-270,75),
							"Current page: 1"),
				page_box(Point(x_max()-270,80),
							25, 20,
							"Page:"),
				goto_button(Point(x_max()-270,100),
							120, 20,
							"Go to page",
							cb_goto),
				quit_button(Point(x_max()-140,20),    // location of button
							120, 20,                 // dimensions of button 
							"Quit",                 // label of button
							cb_quit),
				search_box(Point(70,20),
							250, 20,
							"Search:"),
				rows_box(Point(x_max()-270,140),
							25, 20,
							"Rows:"),
				columns_box(Point(x_max()-175,140),
							25, 20,
							"Columns:"),
				search_text(Point(70, 55),
							"Search by:"),
				search_menu(Point(70,60),   // location of menu
							120, 20,                 // dimensions of menu
							Menu::vertical,         // list menu items vertically
							"Search Options:")
	{
		instance = this;
		
		rows = 3;
		columns = 3;
		pages = 0;
		page = 0;
		attach(next_button);
		attach(last_button);
		attach(grid_button);
		attach(quit_button);
		attach(page_text);
		attach(goto_button);
		attach(page_box);
		attach(search_box);
		attach(rows_box);
		attach(columns_box);
		attach(search_text);
		
		search_menu.attach(new Button(Point(0,0),120,30,"Movie Title", cb_movie_title));
		search_menu.attach(new Button(Point(0,80),120,30,"Movie Year", cb_movie_year));
		search_menu.attach(new Button(Point(0,160),120,30,"Actor", cb_actor));
		search_menu.attach(new Button(Point(0,240),120,30,"Tag", cb_tag));
		attach(search_menu);
		
		gui_main();
		draw();
	}
	
	void hide_menu(){     
		search_menu.hide(); 
	}
	
	void set_grid_size(int r, int c){
		if(r < 1 || c < 1)
			return;
		rows = r;
		columns = c;
		clear_thumbnails();
	}

	void display_page(int p){
		if(p * rows * columns >= thumbnails.size())
			return;
		for(int i = page * rows * columns; i < (page + 1) * rows * columns && i < thumbnails.size(); i++){
				thumbnails[i]->detach(*this);
		}
		page = p;
		for(int i = page * rows * columns; i < (page + 1) * rows * columns && i < thumbnails.size(); i++)
			thumbnails[i]->attach(*this);
		page_text.set_label("Current page: " + itos(page + 1));
		Fl::redraw();
		draw();
	}
	
	void clear_thumbnails(){
		for(Thumbnail* t : thumbnails){
			t->detach(*this);
			delete t;
		}
		thumbnails.clear();
	}

	void update_pos(int& x, int& y){
		if(defaultx + x >= columns * 140){
			x = defaultx;
				y = defaulty + y >= rows * 160 ? defaulty : y + 160;
		}else
			x = x + 140;
	}
	
	void search_by_title(string title){
		clear_thumbnails();
		string name = lcconvert(title);
		int x = defaultx;
		int y = defaulty;
		for(Movie& movie : movies){
			if(lcconvert(movie.get_name()) == name){
				Thumbnail* t = new Thumbnail{x, y, &movie};
				thumbnails.push_back(t);
				update_pos(x, y);
			}
		}
		display_page(0);
	}

	void search_by_year(string year){
		clear_thumbnails();
		int x = defaultx;
		int y = defaulty;
		for(Movie& movie : movies){
			if(movie.get_year() == year){
				Thumbnail* t = new Thumbnail{x, y, &movie};
				thumbnails.push_back(t);
				update_pos(x, y);
			}
		}
		display_page(0);
	}

	void search_by_actor(string actor){
		clear_thumbnails();
		string name = lcconvert(actor);
		int x = defaultx;
		int y = defaulty;
		for(Actor& actor : actors){
			string aname = lcconvert(actor.get_name());
			if(aname == name){
				Thumbnail* t = new Thumbnail{x, y, &actor};
				thumbnails.push_back(t);
				update_pos(x, y);
				for(Movie& movie : movies){
					for(Actor& a : movie.get_actors()){
						if(lcconvert(a.get_name()) == aname){
							Thumbnail* t = new Thumbnail{x, y, &movie};
							thumbnails.push_back(t);
							update_pos(x, y);
							break;
						}
					}
				}
			}
		}
		display_page(0);
	}
	
	void search_by_tag(string tagg){
		clear_thumbnails();
		string tag = lcconvert(tagg);
		int x = defaultx;
		int y = defaulty;
		for(Movie& movie : movies){
			for(string mtag : movie.get_tags()){
				if(lcconvert(mtag) == tag){
					Thumbnail* t = new Thumbnail{x, y, &movie};
					thumbnails.push_back(t);
					update_pos(x, y);
					break;
				}
			}
		}
		display_page(0);
	}

	static void cb_movie_title(Address, Address){
		instance->search_by_title(instance->search_box.get_string());
	}
	
	static void cb_movie_year(Address, Address){
		instance->search_by_year(instance->search_box.get_string());
	}
	
	static void cb_actor(Address, Address){
		instance->search_by_actor(instance->search_box.get_string());
	}
	
	static void cb_tag(Address, Address){
		instance->search_by_tag(instance->search_box.get_string());
	}
	
	static void cb_next(Address, Address){
		instance->display_page(instance->page + 1);
	}
	
	static void cb_last(Address, Address){
		instance->display_page(instance->page - 1);
	}
	
	static void cb_grid(Address, Address){
		instance->set_grid_size(safe_stoi(instance->rows_box.get_string()), safe_stoi(instance->columns_box.get_string()));
	}
	
	static void cb_goto(Address, Address){
		instance->display_page(safe_stoi(instance->page_box.get_string()) - 1);
	}
	
	static void cb_quit(Address, Address){
		exit(0);
	}
};