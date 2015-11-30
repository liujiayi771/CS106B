#include <iostream>
#include "simpio.h"

using namespace std;

int CountWay(int numStairs);

int main()
{
        cout << "Enter the number of the stairs: ";
        int numStairs = GetInteger();
        cout << "The number of different ways to climb the stairs: " << CountWay(numStairs) << endl;
        return 0;
}

int CountWay(int numStairs)
{
        if(numStairs == 1)
                return 1;
        else if(numStairs == 2)
                return 2;
        else
                return CountWay(numStairs - 1) + CountWay(numStairs - 2);
}
