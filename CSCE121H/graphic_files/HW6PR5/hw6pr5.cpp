/*
	Define a Binary_treeclass derived from Shape. Give the number of levels as a parameter (levels==0 means no nodes,levels ==1 means one node, levels==2 means one top node with two sub-=notes level==3 means one top node with two sub-nodes each two sub-nodes etc. ). Let a node be represented by a small circle. Connect the nodes by lines (as is conventional).
	
	In comp sci, trees grow downward from a top node (often called the root, amusingly).
*/

#include "Graph.h"
#include "Simple_window.cpp"
#include "std_lib_facilities_4.h"

using namespace Graph_lib;

struct Combo : Shape // combination of node and connecting lines
{ 
private:
	int x; 
	int y; 
	int radius;
public:
	Combo(int x, int y, int r):x(x),y(y),radius(r)
	{
		Circle node {Point{x,y},radius};
	
		Line line1{Point{x,y-radius},Point{x-50,y-50}};
		Line line2{Point{x,y-radius},Point{x+50,y-50}};
	}
};

struct Binary_tree : Shape
{
	int level;
	int num; // number of nodes on one level
	
	Binary_tree(int level):level(level){
		for(int i = 0; i < level; i++)
			{
			if(i = 0)
			{
				cout << "There are no nodes to display." << endl;
			}
			if(i = 1)
			{
				// insert x and y , r here
				Combo c(300,100,50);
			}
			// supposed to create combos based off of the center x,y coordinates of its "parent" combo
			if(i >= 2)
			{
				int x; int y;
				Combo cleft(x-50,y-50,50);
				Combo cright(x+50,y-50,50);
			}
		
		cout << "Not finished here.";
		}	
	}
};

int main()
{
	try
	{
		Point tl {100,100};
		Simple_window win {tl,600,600,"Your Shape"};
		
		int level;
		cout << "How many levels?" << endl;
		cin >> level;
		
		Binary_tree omg(level);
		
		win.attach(omg);
		win.wait_for_button();
	}
	catch(exception& e)
	{
		//insert code here
		return 1;
	}
	catch(...)
	{
		//insert code here
		return 2;
	}
}