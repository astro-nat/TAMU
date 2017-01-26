#include "Simple_window.h"
#include "Graph.h"
#include "std_lib_facilities_4.h"

using namespace Graph_lib;

void makehouse(){
	Rectangle base {Point{280,80},400,200};
	r1.set_color(Color::black);
	win.attach(r1);





}




int main(){
	try{
		Point tl {200,100};
        Simple_window win {tl,620,620,"Canvas"};
		
		maketictac();
	
	    win.set_label("Canvas");
        win.wait_for_button(); //display
	
	
	
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