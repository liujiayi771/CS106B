/* pathfinder.cpp
 * ---------------
 * A starter file with some helpful #defines and handy utility routines.
 */
 
#include "genlib.h"
#include "extgraph.h"
#include <iostream>


#define CIRCLE_RADIUS .05     // the radius of a node
#define FONT_SIZE 9           // for node name labels
#define ARC_COLOR "Dark gray" // normal arc color
#define NODE_COLOR "Black"    // normal node color
#define HIGHLIGHT_COLOR "Red" // color of chosen path/nodes
#define PAUSE_TIME .02		  // time to pause when animating algorithm


/* Type: coordT
 * ------------
 * Just a simple struct to handle a pair of x,y coordinate values.
 */
struct coordT {
	double x, y;
};


/* Function: DrawFilledCircleWithLabel
 * Usage:  DrawFilledCircleWithLabel(center, .25, "Green", "You are here");
 * -----------------------------------------------------------------------
 * Uses facilities from extgraph to draw a circle filled with
 * color specified. The circle is centered at the given coord has the
 * specified radius.  A label is drawn to the right of the circle.
 * If you don't want a label, pass the empty string.
 */
void DrawFilledCircleWithLabel(coordT center, double radius, string color, string label)
{
	MovePen(center.x + radius, center.y);
	SetPenColor(color);
	StartFilledRegion(1.0);
	DrawArc(radius, 0, 360);
	EndFilledRegion();
	MovePen(center.x + radius, center.y);
	SetFont("Helvetica");
	SetPointSize(FONT_SIZE);
	DrawTextString(label);
}

/* Function: DrawLineBetween
 * Usage:  DrawLineBetween(coord1, coord2, "Black");
 * -------------------------------------------------
 * Uses facilities from extgraph to draw a line of the
 * specified color between the two given coordinates.
 */
void DrawLineBetween(coordT start, coordT end, string color)
{
	SetPenColor(color);
	MovePen(start.x, start.y);
	DrawLine(end.x - start.x, end.y - start.y);
}


/* Function: GetMouseClick
 * Usage:  loc = GetMouseClick();
 * ------------------------------
 * Waits for the user to click somewhere on the graphics window
 * and returns the coordinate of where the click took place.
 */
coordT GetMouseClick()
{
	coordT where;
	WaitForMouseDown();
	WaitForMouseUp();
	where.x = GetMouseX();
	where.y = GetMouseY();
	return where;
}



int main()
{
	InitGraphics();
	SetWindowTitle("CS106 Pathfinder");
    cout << "This masterful piece of work is a graph extravaganza!" << endl
        << "The main attractions include a lovely visual presentation of the graph" << endl
        << "along with an implementation of Dijkstra's shortest path algorithm and" << endl
        << "the computation of a minimal spanning tree.  Enjoy!" << endl;
    return (0);
}