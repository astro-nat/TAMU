
#include "Simple_window.h"
#include "Graph.h"
#include "std_lib_facilities_4.h"

using namespace Graph_lib;

void maketictac(){
	Rectangle r1 {Point{10,10},200,200};
		r1.set_color(Color::red);
		win.attach(r1);
			
		Rectangle r2 {Point{210,10},200,200};
		r2.set_color(Color::white);
		win.attach(r2);
		
		Rectangle r3 {Point{410,10},200,200};
		r3.set_color(Color::red);
		win.attach(r3);
		
		Rectangle r4 {Point{10,210},200,200};
		r4.set_color(Color::white);
		win.attach(r4);
		
		Rectangle r5 {Point{210,210},200,200};
		r5.set_color(Color::red);
		win.attach(r5);
		
		Rectangle r6 {Point{410,210},200,200};
		r6.set_color(Color::white);
		win.attach(r6);
		
		Rectangle r7 {Point{10,410},200,200};
		r7.set_color(Color::red);
		win.attach(r7);
		
		Rectangle r8 {Point{210,410},200,200};
		r8.set_color(Color::white);
		win.attach(r8);
		
		Rectangle r9 {Point{410,410},200,200};
		r9.set_color(Color::red);
		win.attach(r9);		
}

int main(){
        try
        {
        Point tl {220,100};
        Simple_window win {tl,620,620,"Canvas"};
		
		maketictac();
	
	    win.set_label("Canvas");
        win.wait_for_button(); //display
        }
        catch(exception& e)
        {
			// code goes here
			return 1;
        }
        catch(...)
        {
			// code goes here
            return 2;
        }
}
