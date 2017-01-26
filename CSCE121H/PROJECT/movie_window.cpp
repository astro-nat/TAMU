#include "std_lib_facilities_4.h"
#include <iostream>
#include "Simple_window.h"
#include "Graph.h"
#include "GUI.h"
#include "Window.h"

using namespace Graph_lib;
using namespace std;

struct Movie_window : Graph_lib::Window {
	Movie_window(Point xy, int w, int h, const string& title);
};

Movie_window::Movie_window(Point xy, int w, int h, const string& title) : 

  // initialization - start by calling constructor of base class 
  Window(xy,w,h,title),    

  // initialize "Next point" button
  next_button(
	      Point(x_max()-150,0),   // location of button
	      70, 20,                 // dimensions of button
	      "Next point",           // label of button
	      cb_next),               // callback function for button
  // initialize quit button
  quit_button(
	      Point(x_max()-70,0),    // location of button
	      70, 20,                 // dimensions of button 
	      "Quit",                 // label of button
	      cb_quit),               // callback function for button
  // initialize the next_x inbox
  next_x(
	 Point(x_max()-310,0),       // location of box
	 50, 20,                     // dimensions of box
	 "next x:"),                 // label of box 
  // initialize the next_y inbox
  next_y(
	 Point(x_max()-210,0),       // location of box
	 50, 20,                     // dimensions of box
	 "next y:"),                 // label of box
  // initialize the outbox
  xy_out(
	 Point(100,0),               // location of box
	 100, 20,                    // dimensions of box
	 "current (x,y):"),          // label of box
  // initialize the color menu
  color_menu(                        
	     Point(x_max()-70,30),   // location of menu
	     70, 20,                 // dimensions of menu
	     Menu::vertical,         // list menu items vertically
	     "color"),               // label of menu 
  // initialize the menu button
  menu_button(
	      Point(x_max()-80,30),  // location of menu button
	      80, 20,                // dimensions of button 
	      "color menu",          // label of button
	      cb_menu)               // callback for button

  // body of constructor follows
{
  // attach buttons and boxes to window
  attach(next_button);
  attach(quit_button);
  attach(next_x);
  attach(next_y);
  attach(xy_out);
  xy_out.put("no point");        // output to out box

  // First make 3 buttons for color menu, one for each color, and 
  // attach them to the menu: the attach function of the Menu struct
  // adjusts the size and location of the buttons; note callback functions).
  // Then attach menu to window but hide it (initially, the menu button
  // is displayed, not the actual menu of color choices).

  color_menu.attach(new Button(Point(0,0),0,0,"red",cb_red)); 
  color_menu.attach(new Button(Point(0,0),0,0,"blue",cb_blue));
  color_menu.attach(new Button(Point(0,0),0,0,"black",cb_black));
  attach(color_menu);
  color_menu.hide(); 

  // attach menu button
  attach(menu_button);

  // attach shape that holds the lines to be displayed
  attach(lines);
}

// ---------------------------- 
// callback function for quit button - boilerplate: 
// When the button is pressed, the system invokes the
// specified callback function.  First argument is address of the
// button (which we won't use, so we don't bother to name it).  Second
// argument, named pw, is address of the window containing the pressed
// button, i.e., address of our Movie_window object.  reference_to
// converts the address pw into a reference to a Movie_window object,
// so we can call the quit() function.  Objective is to call function
// quit() which does the real work specific to this button.

void Movie_window::cb_quit(Address, Address pw) {
  reference_to<Movie_window>(pw).quit();   // quit is defined next
}

//------------------------------------
// what to do when quit button is pressed

void Movie_window::quit() {
  hide();                   // FLTK idiom for delete window
}

// ----------------------------
// callback function for next button - boilerplate:

void Movie_window::cb_next(Address, Address pw) {
  reference_to<Movie_window>(pw).next();  // next is defined next
}

// -------------------------------
// what to do when "next point" button is pressed

void Movie_window::next() {
  // get input data from the inboxes - x and y coordinates
  // of next point
  int x = next_x.get_int();
  int y = next_y.get_int();

  // add the new point to the lines object
  lines.add(Point(x,y));

  // update current position readout - make a string with the
  // coordinate info and use the out box
  stringstream ss;
  ss << '(' << x << ',' << y << ')';
  xy_out.put(ss.str());

  redraw();  // function inherited from Window to redraw the window
}

// -------------------------------
// callback for when red button (part of color menu) is pressed - boilerplate

void Movie_window::cb_red(Address, Address pw) {
  reference_to<Movie_window>(pw).red_pressed();  
  // red_pressed defined in Movie_window class as part of declaration
}

// -------------------------------
// callback for when blue button (part of color menu) is pressed - boilerplate

void Movie_window::cb_blue(Address, Address pw) {
  reference_to<Movie_window>(pw).blue_pressed();  
  // blue_pressed defined in Movie_window class as part of declaration
}

// -------------------------------
// callback for when black button (part of color menu) is pressed - boilerplate

void Movie_window::cb_black(Address, Address pw) {
  reference_to<Movie_window>(pw).black_pressed();  
  // black_pressed defined in Movie_window class as part of declaration
}

// -------------------------------
// callback for when menu button is pressed - boilerplate

void Movie_window::cb_menu(Address, Address pw)
{  
    reference_to<Movie_window>(pw).menu_pressed();
    // menu_pressed defined in Movie_window class as part of declaration
} 

int main()
{
	try
	{
		Point p(100,100);
		Movie_window mv(p,600,400,"Movie Information");
		return gui_main();
	}
	catch(exception& e) 
	{
		cerr << "exception: " << e.what() << endl;
		return 1;
	}
	catch(...) 
	{
		cerr << "some exception" << endl;
		return 2;
	}
}