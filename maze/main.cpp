#include <iostream>
#include <string>
#include "simpio.h"
#include "graphics.h"
#include "maze.h"
#include "set.h"
#include "vector.h"
#include "stack.h"
#include "extgraph.h"
#include "random.h"

using namespace std;

const int MAX_LEN = 1000;

void init(int & row, int & col);
void createMaze(Maze & m, int row, int col);
void findWay(Maze & m, int row, int col);
void drawPath(Stack<pointT> & shortestPathStack, Maze & myMaze);

bool operator<(const pointT & a, const pointT & b)
{
	if(a.row < b.row)
		return true;
	else
        {
		if(a.row > b.row)
			return false;
		else
		{
			if(a.col < b.col)
				return true;
			else
                                return false;
		}
	}
}

bool operator>(const pointT & a, const pointT & b)
{
	if(a.row > b.row)
        {
		return true;
	}
	else
                {
		if(a.row < b.row)
			return false;
		else
		{
		        if(a.col > b.col)
				return true;
                        else
                                return false;
		}
	}
}

bool operator==(const pointT & a, const pointT & b)
{
	if(a.row == b.row && a.col == b.col)
		return true;
	else
		return false;
}

int main()
{
        int row, col;
        init(row, col);
        Maze m(row, col, true);
        createMaze(m, row, col);
        while(!MouseButtonIsDown());
        findWay(m, row, col);
        return 0;
}

void init(int & row, int & col)
{
        cout << "Enter the row of the maze: ";
        row = GetInteger();
        while(row <= 0)
        {
                cout << "Please enter the correct number of the row!" << endl;
                cout << "Enter the row of the maze: ";
                row = GetInteger();
        }
        cout << "Enter the col of the maze: ";
        col = GetInteger();
        while(col <= 0)
        {
                cout << "Please enter the correct number of the col!" << endl;
                cout << "Enter the col of the maze: ";
                col = GetInteger();
        }
        InitGraphics();
        SetWindowSize(GetFullScreenWidth(), GetFullScreenHeight());
        Maze m(row, col, true);
        m.draw();
}

void createMaze(Maze & m, int row, int col)
{
        Set<pointT> mstate;
        Randomize();
        int counter = 0;
        int currentRow = RandomInteger(0, row);
        int currentCol = RandomInteger(0, col);
        pointT currentPoint = {currentRow, currentCol};
        mstate.add(currentPoint);
        counter ++;
        while(counter < row * col)
        {
                int nextRow, nextCol, direction;
                direction = RandomInteger(0,4);
                switch(direction)
                {
                case 0://up
                        nextRow = currentRow + 1;
                        nextCol = currentCol;
                        break;
                case 1://down
                        nextRow = currentRow - 1;
                        nextCol = currentCol;
                        break;
                case 2://left
                        nextRow = currentRow;
                        nextCol = currentCol - 1;
                        break;
                case 3://right
                        nextRow = currentRow;
                        nextCol = currentCol + 1;
                        break;
                default:
                        cout << "ERROR in generate random direction!" << endl;
                        break;
                }
                pointT nextPoint = {nextRow, nextCol};
                if(!m.pointInBounds(nextPoint))//the point is not inside the bound
                        continue;
                else//the point is inside the bound
                {
                        if(!mstate.contains(nextPoint))//the point has not been visited before
                        {
                                mstate.add(nextPoint);//add the point to the set show its state(has been visited)
                                counter ++;
                                m.setWall(currentPoint, nextPoint, false);
                        }
                        currentRow = nextRow;
                        currentCol = nextCol;
                        currentPoint = nextPoint;
                }
        }
}

void findWay(Maze & m, int row, int col)
{
        pointT origin = {0, 0};
        pointT destination = {row - 1, col - 1};

	Vector<Stack<pointT>> mazePath;
	Stack<pointT> originPath;
	originPath.push(origin);
	mazePath.add(originPath);

	while(1)
        {
		int shortestPath = MAX_LEN;
		int pathNum;
		int size = mazePath.size();
		for(int i = 0; i < mazePath.size(); i++)
		{
			int currentLength = mazePath[i].size();
			if(currentLength < shortestPath)
                        {
				shortestPath = currentLength;
				cout << currentLength << endl;
				pathNum = i;//save the index of the shortest path
			}
		}

		Stack<pointT> shortestPathStack = mazePath.getAt(pathNum);
		pointT lastPoint = shortestPathStack.peek();

		if(lastPoint.row == destination.row && lastPoint.col == destination.col) //if the last point is the destination then we picture the path
                {
			drawPath(shortestPathStack, m);
			break;
		}
		else
                {
			shortestPathStack.pop();
			pointT penultimatePoint;

			if(!shortestPathStack.isEmpty())
				penultimatePoint = shortestPathStack.peek();//get the last but one point

			pointT tmpPoint;

			tmpPoint.col = lastPoint.col;
			tmpPoint.row = lastPoint.row - 1;//down of the last point
			if(m.pointInBounds(tmpPoint)//the point is inside the bound
                        && (shortestPathStack.isEmpty() || tmpPoint.col != penultimatePoint.col || tmpPoint.row != penultimatePoint.row)//the shortest path stack only has one point or the path does not go back
                        && !(m.isWall(lastPoint, tmpPoint))) //there is no wall between the last point and the temp point
                        {
				Stack<pointT> newPath = shortestPathStack;
				newPath.push(lastPoint);
				newPath.push(tmpPoint);
				mazePath.add(newPath);
			}

			tmpPoint.col = lastPoint.col;
			tmpPoint.row = lastPoint.row + 1;//up of the last point
			if(m.pointInBounds(tmpPoint)
                        && (shortestPathStack.isEmpty() || tmpPoint.col != penultimatePoint.col || tmpPoint.row != penultimatePoint.row)
                        && !(m.isWall(lastPoint, tmpPoint)))
                        {
				Stack<pointT> newPath = shortestPathStack;
				newPath.push(lastPoint);
				newPath.push(tmpPoint);
				mazePath.add(newPath);
			}

			tmpPoint.row = lastPoint.row;
			tmpPoint.col = lastPoint.col - 1;//left of the last point
			if(m.pointInBounds(tmpPoint)
                        && (shortestPathStack.isEmpty() || tmpPoint.col != penultimatePoint.col || tmpPoint.row != penultimatePoint.row)
                        && !(m.isWall(lastPoint, tmpPoint)))
                        {
				Stack<pointT> newPath = shortestPathStack;
				newPath.push(lastPoint);
				newPath.push(tmpPoint);
				mazePath.add(newPath);
			}

			tmpPoint.row = lastPoint.row;
			tmpPoint.col = lastPoint.col + 1;//right of the last point
			if(m.pointInBounds(tmpPoint)
                        && (shortestPathStack.isEmpty() || tmpPoint.col != penultimatePoint.col || tmpPoint.row != penultimatePoint.row)
                        && !(m.isWall(lastPoint, tmpPoint)))
                        {
				Stack<pointT> newPath = shortestPathStack;
				newPath.push(lastPoint);
				newPath.push(tmpPoint);
				mazePath.add(newPath);
			}

			mazePath.removeAt(pathNum);
		}
	}
}

void drawPath(Stack<pointT> & shortestPathStack, Maze & m) {
	while(!shortestPathStack.isEmpty()) {
		pointT currentPoint = shortestPathStack.pop();
		m.drawMark(currentPoint, "Blue");
	}
}
