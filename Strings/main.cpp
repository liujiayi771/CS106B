#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include "simpio.h"

using namespace std;
string getSoundexCode(string surname);

int main()
{
        string surname;
        while(1)
        {
                cout << "Enter surname (RETURN to quit): ";
                surname = GetLine();
                if(surname == "")
                {
                        return 0;
                }
                const char *p = surname.c_str();
                for(; *p; p++)
                {
                        if(!isalpha(*p))
                                break;
                }
                while(*p)
                {
                        cout << "Please enter the correct surname!" << endl;
                        cout << "Enter surname (RETURN to quit): ";
                        surname = GetLine();
                        if(surname == "")
                        {
                                return 0;
                        }
                        p = surname.c_str();
                        for(; *p; p++)
                        {
                                if(!isalpha(*p))
                                        break;
                        }
                }
                cout << "Soundex code for " << surname << " is ";
                transform(surname.begin(), surname.end(), surname.begin(), ::toupper);
                cout << getSoundexCode(surname) << endl;
        }
        return 0;
}

string getSoundexCode(string surname)
{
        string soundexCode = "";
        int size = surname.size();
        soundexCode += surname[0];
        for(int i = 1; i < size; i++)
        {
                char c = surname[i];
                switch(c)
                {
                case 'A':
                case 'E':
                case 'I':
                case 'O':
                case 'U':
                case 'H':
                case 'W':
                case 'Y':
                        soundexCode += '0';
                        break;
                case 'B':
                case 'F':
                case 'P':
                case 'V':
                        soundexCode += '1';
                        break;
                case 'C':
                case 'G':
                case 'J':
                case 'K':
                case 'Q':
                case 'S':
                case 'X':
                case 'Z':
                        soundexCode += '2';
                        break;
                case 'D':
                case 'T':
                        soundexCode += '3';
                        break;
                case 'M':
                case 'N':
                        soundexCode += '4';
                        break;
                case 'L':
                        soundexCode += '5';
                        break;
                case 'R':
                        soundexCode += '6';
                default:
                        cout << "ERROR!" << endl;
                        break;
                }
        }
        return soundexCode;
}
