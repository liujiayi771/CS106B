#include <iostream>
#include "vector.h"
#include "set.h"

using namespace std;

bool Solvable(int start, Vector<int> & squares);
bool recursionSolve(Set<int> & visited, int start, Vector<int> & squares);
int main()
{
    Vector<int> squares;
    squares.add(3);
    squares.add(1);
    squares.add(2);
    squares.add(3);
    squares.add(0);
    //squares.add(3);
    //squares.add(6);
    //squares.add(4);
    //squares.add(1);
    //squares.add(3);
    //squares.add(4);
    //squares.add(2);
    //squares.add(5);
    //squares.add(3);
    //squares.add(0);
    if(Solvable(0, squares))
    {
            cout << "solvable!" << endl;
    }
    else
    {
            cout << "unsolvable" << endl;
    }
    return 0;
}

bool Solvable(int start, Vector<int> & squares)
{
        Set<int> visitedIndex;
        return recursionSolve(visitedIndex, start, squares);
}

bool recursionSolve(Set<int> & visited, int start, Vector<int> & squares)
{
        int num = squares[start];
        if(num == 0)
        {
                return true;
        }
        if(visited.contains(start))
        {
                return false;
        }
        visited.add(start);
        if(start + num <= squares.size() - 1)
        {
                return recursionSolve(visited, start + num, squares);
        }
        if(start - num >= 0)
        {
                return recursionSolve(visited, start - num, squares);
        }
        return false;
}
