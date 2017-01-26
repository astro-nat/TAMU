#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities_4.h"

using namespace Graph_lib;

void display_image()
{
	Point tl {100,100};
    Simple_window win {tl,650,530,"My Car"};
	
	Image car{Point{25,25},"my_car.jpg"};
	win.attach(car);
	
	Text brag{Point{65,510}, "This is my car! It's maroon, has great gas mileage, and the sound system rocks."};
	win.attach(brag);
	
	win.wait_for_button();
}

int main(){
	try
	{
		display_image();
	}
	catch(exception& e)
	{
		cerr << "Something went wrong." << endl;
		return 1;
	}
	catch(...)
	{
		cerr << "Something else went wrong." << endl;
		return 2;
	}
}