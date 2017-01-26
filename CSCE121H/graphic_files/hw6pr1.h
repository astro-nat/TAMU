/*
NATALIE CLUCK
CSCE 121 HONORS
FALL 2014
HOMEWORK 6

CHAPTER 12: EXERCISES 4, 7, AND 9

4. Draw a 3-by-3 tic-tac-toe board of alternating white and red squares.
7. Draw a two-dimensional house seen from the front, the way a child would: with a door, two windows, and a roof with a chimney. Feel free to add details; maybe have "smoke" come out of the chimney.
9. Display an image on the screen, e.g., a photo of a friend. Label the image both with a title on the window and with a caption in the window.

*/


#include "Simple_window.h"
#include "Graph.h"

int main()
{
        using namespace Graph_lib;

        Point tl {100,100};


        Simple_window win {tl,600,400,"Canvas"};

        Polygon square;

        square.add(Point{100,100});
        square.add(Point{100,200});
        square.add(Point{200,200});
        square.add(Point{200,101});

        square.set_color(Color::red);

        win.attach (square);

        win.wait_for_button();

}