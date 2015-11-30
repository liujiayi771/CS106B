#include <iostream>
#include "simpio.h"

using namespace std;

int GCD(int x, int y);

int main()
{
        int x, y;
        cout << "Enter two numbers: " << endl;
        x = GetInteger();
        y = GetInteger();
        cout << "The g.c.d of " << x << " and " << y << ": " << GCD(x, y) << endl;
        return 0;
}

int GCD(int x, int y)
{
        int temp = 0;
        if((x % y) == 0)
        {
                temp = y;
        }
        else
        {
                temp = GCD(y, x % y);
        }
        return temp;
}
