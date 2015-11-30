#include <iostream>
#include "simpio.h"
#include "vector.h"

using namespace std;

void ListMnemonics(string str);
Vector<char> num2char(char num);
void curList(Vector<Vector<char>> & ch, string list, int index);

int main()
{
    cout << "Enter phone number: ";
    string str = GetLine();
    ListMnemonics(str);
    return 0;
}

void ListMnemonics(string str)
{
        string list;
        Vector<Vector<char>> ch;
        for(int i = 0; i < str.size(); i++)
        {
                ch.add(num2char(str[i]));
        }
        curList(ch, list, 0);
}

void curList(Vector<Vector<char>> & ch, string list, int index)
{
        if(index == ch.size())
        {
                cout << list << endl;
        }
        else
        {
                for(int i = 0; i < ch[index].size(); i++)
                {
                        curList(ch, list += ch[index][i], index + 1);
                        list.pop_back();
                }
        }
}

Vector<char> num2char(char num)
{
        Vector<char> result;
        switch(num)
        {
        case '2':
                result.add('A');
                result.add('B');
                result.add('C');
                break;
        case '3':
                result.add('D');
                result.add('E');
                result.add('F');
                break;
        case '4':
                result.add('G');
                result.add('H');
                break;
        case '5':
                result.add('J');
                result.add('K');
                result.add('L');
                break;
        case '6':
                result.add('M');
                result.add('N');
                result.add('O');
                break;
        case '7':
                result.add('P');
                result.add('R');
                result.add('S');
                break;
        case '8':
                result.add('T');
                result.add('U');
                result.add('V');
                break;
        case '9':
                result.add('W');
                result.add('X');
                result.add('Y');
                break;
        default:
                cout << "Input error!" << endl;
                break;
        }
        return result;
}
