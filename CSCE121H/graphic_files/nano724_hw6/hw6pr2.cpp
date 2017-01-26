#include "Simple_window.h"
#include "Graph.h"
#include "std_lib_facilities_4.h"

using namespace Graph_lib;

void makehouse(){
	Point tl {200,100};
    Simple_window win {tl,800,800,"Canvas"};
	
	Rectangle house{Point{200,350},400,400};
	house.set_color(Color::red);
	house.set_style(Line_style::dash);
	win.attach(house);
	
	Polygon roof;
	roof.add(Point{200,350});
	roof.add(Point{400,100});
	roof.add(Point{600,350});
	roof.set_color(Color::yellow);
	win.attach(roof);
	
	Polygon chimney;
	chimney.add(Point{250,288});
	chimney.add(Point{250,100});
	chimney.add(Point{350,100});
	chimney.add(Point{350,163});
	chimney.set_color(Color::cyan);
	win.attach(chimney);
	
	Rectangle window1{Point{225,450},100,100};
	window1.set_color(Color::blue);
	win.attach(window1);
	
	Rectangle window2{Point{475,450},100,100};
	window2.set_color(Color::blue);
	win.attach(window2);
	
	Rectangle door{Point{340,400},120,350};
	door.set_color(Color::cyan);
	win.attach(door);
	
	win.set_label("Canvas");
    win.wait_for_button(); //display
}

int main(){
	try
	{
		makehouse();	
	}
	catch(exception& e){
	//some code here
	return 1;
	}
	catch(...){
	//some code here
	return 2;
	}
}