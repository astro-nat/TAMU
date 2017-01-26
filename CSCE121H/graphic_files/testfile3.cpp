#include "Simple_window.h"
#include "Graph.h"
#include "std_lib_facilities_4.h"

using namespace Graph_lib;

int main(){
	try
	{
	
	Point tl {100,100};

	Simple_window win {tl,600,400,"Canvas"};
		// screen coordinate tl for top left corner
		// window size(600*400)
		// title: Canvas


	win.wait_for_button(); //display




	}
	catch(exception& e)
	{
		
		return 1;
	}
	catch(...)
	{
		
		return 2;
	}
}
