#include <iostream>

using namespace std;

bool IsPerfect(int num);

int main()
{
    for(int i = 1; i <= 10000; i++)
    {
        if(IsPerfect(i))
            cout << i << endl;
    }
    return 0;
}

bool IsPerfect(int num)
{
    int i = 1;
    int sum = 0;
    while(i < num)
    {
        if(num % i == 0 && num != i)
        {
            sum += i;
        }
        i++;
    }
    if(sum == num)
        return true;
    else
        return false;
}
