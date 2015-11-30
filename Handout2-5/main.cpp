#include <iostream>
#include "grid.h"
#include "random.h"

using namespace std;

Grid<int> MakeGridOfCounts(Grid<bool> & bombLocations);

int main()
{
        Grid<bool> bombLocations(6, 6);
        Randomize();
        for(int row = 0; row < bombLocations.numRows(); row ++)
        {
                for(int col = 0 ; col < bombLocations.numCols(); col ++)
                {
                        if(RandomChance(0.5))
                        {
                                bombLocations.setAt(row, col, true);
                        }
                        else
                                bombLocations.setAt(row, col, false);
                }
        }
        for(int row = 0; row < bombLocations.numRows(); row ++)
        {
                for(int col = 0 ; col < bombLocations.numCols(); col ++)
                {
                        if(bombLocations.getAt(row, col))
                        {
                                cout << "T ";
                        }
                        else
                                cout << "F ";
                }
                cout << endl;
        }
        Grid<int> gridOfCounts = MakeGridOfCounts(bombLocations);
        cout << endl;
        for(int row = 0; row < gridOfCounts.numRows(); row ++)
        {
                for(int col = 0; col < gridOfCounts.numCols(); col ++)
                {
                        cout << gridOfCounts[row][col] << " ";
                }
                cout << endl;
        }
        return 0;
}

Grid<int> MakeGridOfCounts(Grid<bool> & bombLocations)
{
        Grid<int> gridOfCounts(bombLocations.numRows(), bombLocations.numCols());
        for(int row = 0; row < bombLocations.numRows(); row ++)
        {
                for(int col = 0 ; col < bombLocations.numCols(); col ++)
                {
                        gridOfCounts[row][col] = 0;
                }
        }
        for(int row = 0; row < bombLocations.numRows(); row ++)
        {
                for(int col = 0 ; col < bombLocations.numCols(); col ++)
                {
                        if(bombLocations.inBounds(row, col) && bombLocations.getAt(row, col))
                        {
                                gridOfCounts[row][col] ++;
                        }
                        if(bombLocations.inBounds(row-1, col-1) && bombLocations.getAt(row-1, col-1))
                        {
                                gridOfCounts[row][col] ++;
                        }
                        if(bombLocations.inBounds(row-1, col) && bombLocations.getAt(row-1, col))
                        {
                                gridOfCounts[row][col] ++;
                        }
                        if(bombLocations.inBounds(row-1, col+1) && bombLocations.getAt(row-1, col+1))
                        {
                                gridOfCounts[row][col] ++;
                        }
                        if(bombLocations.inBounds(row, col+1) && bombLocations.getAt(row, col+1))
                        {
                                gridOfCounts[row][col] ++;
                        }
                        if(bombLocations.inBounds(row+1, col+1) && bombLocations.getAt(row+1, col+1))
                        {
                                gridOfCounts[row][col] ++;
                        }
                        if(bombLocations.inBounds(row+1, col) && bombLocations.getAt(row+1, col))
                        {
                                gridOfCounts[row][col] ++;
                        }
                        if(bombLocations.inBounds(row+1, col-1) && bombLocations.getAt(row+1, col-1))
                        {
                                gridOfCounts[row][col] ++;
                        }
                        if(bombLocations.inBounds(row, col-1) && bombLocations.getAt(row, col-1))
                        {
                                gridOfCounts[row][col] ++;
                        }
                }
        }
        return gridOfCounts;
}
