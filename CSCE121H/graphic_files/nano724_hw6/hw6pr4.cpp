// http://gamedev.stackexchange.com/questions/1692/what-is-a-simple-algorithm-for-calculating-evenly-distributed-points-on-an-ellip
// http://stackoverflow.com/questions/24220750/creating-a-hexagon-class

#include "Graph.h"
#include "Simple_window.h"
#include "std_lib_facilities_4.h"
#include <cmath>

using namespace Graph_lib;

struct Regular_polygon : Polygon 
{
private:
	int centx; // x value of center
	int centy; // y value of center
	double points; // number of points. Should equal number of sides
	int distance; // distance from center to points
public:
	// centx, centy = center's point parameters. s = number of points. d distance from center
	Regular_polygon(int x, int y, int s, int d):centx(x),centy(y),points(s),distance(d)
	{ 
		if(centx < 0 || centx > 600 || centy < 0 || centy > 600)
		{
			error("One or more of your values is out of bounds. Try again.");
		}
		if(points <= 2)
		{
			error("Invalid number of sides. Try again.");
		}
		else
			// create imaginary circle around center where points are distributed evenly
		{
			for (int i = 0; i < points; i++)
			{
				double angle = (360.0/points) * i;
				int r = distance;
				int pi = 3.14;
				Point p;
				p.x = (centx) + (r * cos(angle * pi / 180));
				p.y = (centy) + (r * sin(angle * pi / 180));
				add(p);	
			}
			
		}	
	}
};

int main()
{
	try
	{
		Point tl {100,100};
		Simple_window win {tl,600,600,"Your Shape"};
		
		int x;	int y;	int s;	int d;
		
		cout << "Where do you want the center of your shape?" << endl;
		cin >> x;
		cin >> y;
				
		cout << "How many sides do you want?" << endl;
		cin >> s;
		
		cout << "How big do you want your shape? Enter a number between 1 and 600." << endl;
		cin >> d;
		
		Regular_polygon poly(x,y,s,d); //creates polygon based on user's preferences
		win.attach(poly);
		
		win.wait_for_button();
		
	}
	catch(exception& e)
	{
		cerr << "Something is not right." << endl; //some code here
		return 1;
	}
	catch(...)
	{
		cerr << "Something else is not right." << endl; //some code here
		return 2;
	}
}

