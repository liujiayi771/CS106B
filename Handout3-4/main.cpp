#include <iostream>
#include "simpio.h"

using namespace std;

int Cannonball(int height);

int main()
{
        int height;
        cout << "Enter the number of layers in the pyramid: ";
        height = GetInteger();
        cout << endl;
        cout << "The number of cannonballs: " << Cannonball(height) << endl;
        return 0;
}

int Cannonball(int height)
{
        int sum = 0;
        for(int i = 1; i <= height; i++)
        {
                sum += (i * i);
        }
        return sum;
}
