/*
	Make a menu with items that make a circle, a square, an equilateral triangle, and a hexagon, respectively. Make an input box (or two) for giving a coordinate pair, and place the shape made by pressing a menu item at that coordinate. Sorry, no drag and drop.
*/

// Two input boxes: x and y coordinates
	// x and y are the center parameters of the shape
// Set up shapes in structs. Can have them at predetermined size.
// Make a menu with buttons. Each button creates a different shape.
// When new button pressed, delete old shape or keep adding on until "Clear" button is pressed?
	
#include "std_lib_facilities_4.h"
#include "Graph.h"
#include "Window.h"
#include "GUI.h"

using namespace Graph_lib;
using namespace std;

struct Regular_polygon : Polygon // creates shapes
{
private:
	int centx; // x value of center
	int centy; // y value of center
	int points; // number of points. Should equal number of sides
	int distance; // distance from center to points
public:
	// centx, centy = center's point parameters. s = number of points. d distance from center
	Regular_polygon(int& x, int& y, int s, int d):centx(x),centy(y),points(s),distance(d)
	{ 
		if(centx < 0 || centx > 600 || centy < 0 || centy > 600) // checks if shape center is out of window
		{
			error("One or more of your values is out of bounds. Try again.");
		}
		if(points <= 2) // Can't be less than three sides on a shape
		{
			error("Invalid number of sides. Try again.");
		}
		else
			// create imaginary circle around center where points are distributed evenly
		{
			for (int i = 0; i < points; i++)
			{
				int angle = (360/points) * i;
				int r = distance;
				double pi = 3.14;
				Point p;
				p.x = (centx) + (r * cos(angle * pi / 180.0));
				p.y = (centy) + (r * sin(angle * pi / 180.0));
				add(p);	
			}
			
		}	
	}
};

struct Lines_window : Graph_lib::Window 
{
	Lines_window(Point xy, 
		int w,
		int h, 
		const string& title);
private:
	//sides
	Closed_polyline lines;
	
	// widgets
	Button quit_button;
	Button clear_button;
	In_box cent_x;
	In_box cent_y;
	Out_box shape_out;
	Menu shape_menu;
	Button menu_button;
	
	void hide_menu() 
	{
		cout << "menu here" << endl;
		shape_menu.hide();
		menu_button.show();
	}
	
	void circle_pressed() 
	{
		// display circle with center at cent_x and cent_y coordinates
		clear();
		cout << "circle here" << endl;
		hide_menu();
		int xcircle = cent_x.get_int();
		int ycircle = cent_y.get_int();
		
		Point lala({xcircle,ycircle});
		Circle c(lala,100);
		
		stringstream ss;
		ss << "(" << xcircle << "," << ycircle << ")";
		shape_out.put(ss.str());
	}
	
	void square_pressed() 
	{
		// display square with center at cent_x and cent_y coordinates
		clear();
		cout << "square here" << endl;
		int xsquare = cent_x.get_int();
		int ysquare = cent_y.get_int();
		
		Regular_polygon square(xsquare,ysquare,4,100);
		
		stringstream ss;
		ss << "(" << xsquare << "," << ysquare << ")";
		shape_out.put(ss.str());
		
		hide_menu();
	}
	
	void triangle_pressed() 
	{
		clear();
		// display triangle with center at cent_x and cent_y coordinates
		cout << "triangle here" << endl;
		int xtri = cent_x.get_int();
		int ytri = cent_y.get_int();
		
		Regular_polygon triangle(xtri,ytri,3,100);
		
		stringstream ss;
		ss << "(" << xtri << "," << ytri << ")";
		shape_out.put(ss.str());
		
		hide_menu();
	}
	
	void hexagon_pressed() 
	{
		clear();
		// display hexagon with center at cent_x and cent_y coordinates
		cout << "hexagon here" << endl;
		int xhex = cent_x.get_int();
		int yhex = cent_y.get_int();
		
		Regular_polygon hexagon(xhex,yhex,5,100);
		
		stringstream ss;
		ss << "(" << xhex << "," << xhex << ")";
		shape_out.put(ss.str());
		
		hide_menu();
	}
	
	void menu_pressed() 
	{
		cout << "menu pressed" << endl;
		shape_menu.show();
		menu_button.hide();
	}
	
	void quit();
		
	void clear();
	
	// declares callback functions
	static void cb_circle(Address, Address);
	static void cb_square(Address, Address);
	static void cb_triangle(Address, Address);
	static void cb_hexagon(Address, Address);
	static void cb_menu(Address, Address);
	static void cb_quit(Address, Address);
	static void cb_clear(Address, Address);
};

Lines_window::Lines_window(Point xy, int w, int h, const string& title) :

	Window(xy,w,h,title),
	
	quit_button(Point(x_max()-70,0),70,20,"Quit",cb_quit),
	clear_button(Point(x_max()-70,y_max()-20),70,20,"Clear All",cb_clear),
	
	cent_x(Point(x_max()-310,0),50,20,"x coordinate:"),
	cent_y(Point(x_max()-210,0),50,20,"y coordinate:"),
	
	shape_out(Point(100,0),70,20,"current (x,y):"),
	
	shape_menu(Point(x_max()-70,30),70,20,Menu::vertical,"Shape"),
	
	menu_button(Point(x_max()-80,30),80,20,"Shape Menu",cb_menu)
{
	attach(quit_button);
	attach(clear_button);
	attach(cent_x);
	attach(cent_y);
	attach(shape_out);
	shape_out.put("No shapes");
	
	shape_menu.attach(new Button(Point(0,0),0,0,"Circle",cb_circle));
	shape_menu.attach(new Button(Point(0,0),0,0,"Square",cb_square));
	shape_menu.attach(new Button(Point(0,0),0,0,"Triangle",cb_triangle));
	shape_menu.attach(new Button(Point(0,0),0,0,"Hexagon",cb_hexagon));
	attach(shape_menu);
	shape_menu.hide();
	
	attach(menu_button);
	
	attach(lines);
}

// defines callback functions in reference to buttons
void Lines_window::cb_quit(Address, Address pw) 
	{ reference_to<Lines_window>(pw).quit(); }

void Lines_window::quit() 
	{ hide(); }

void Lines_window::cb_clear(Address, Address pw)
	{ reference_to<Lines_window>(pw).clear(); }

void Lines_window::clear() 
	{ clear(); }

void Lines_window::cb_circle(Address, Address pw) 
	{ reference_to<Lines_window>(pw).circle_pressed(); }
	
void Lines_window::cb_square(Address, Address pw) 
	{ reference_to<Lines_window>(pw).square_pressed(); }

void Lines_window::cb_triangle(Address, Address pw) 
	{ reference_to<Lines_window>(pw).triangle_pressed(); }
	
void Lines_window::cb_hexagon(Address, Address pw)
	{ reference_to<Lines_window>(pw).hexagon_pressed(); }

void Lines_window::cb_menu(Address, Address pw) 
	{ reference_to<Lines_window>(pw).menu_pressed(); }
	
int main() 
{
	try
	{
		cout << "This works." << endl; // tests main function
		Lines_window win(Point(100,100),600,600,"Shapes");
		return gui_main();
	}
	catch(exception& e)
	{
		cerr << "exception: " << e.what() << endl;
		return 1;
	}
	catch(...)
	{
		cerr << "Something went wrong" << endl;
		return 2;
	}
};