#include <iostream>
#include "simpio.h"

using namespace std;

string ReverseString1(string str);
string ReverseString2(string str);

int main()
{
    cout << "Enter a string: " << endl;
    string str = GetLine();
    cout << "The recursive technique: " << ReverseString1(str) << endl;
    cout << "The iterative technique: " << ReverseString2(str) << endl;
    return 0;
}

string ReverseString1(string str)
{
        if(str.size() == 1)
        {
                return str;
        }
        else
        {
                return ReverseString1(str.substr(1)) += str[0];
        }
}

string ReverseString2(string str)
{
        string result;
        string::iterator it = str.end();
        for(; it != str.begin() - 1; it--)
        {
                result += *it;
        }
        return result;
}
