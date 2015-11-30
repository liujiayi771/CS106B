#include <iostream>
#include "lexicon.h"
#include "simpio.h"
#include "vector.h"

using namespace std;

void recursionPrefix(Vector<string> & combination, string prefix, string rest);
void ListCompletions(string digits, Lexicon & lex);
string digit2letters(char ch);
void recursionCompletion(Lexicon & lex, string prefi);
string letters = "abcdefghijklmnopqrstuvwxyz";

int main()
{
        Lexicon lex("lexicon.dat");
        while(1)
        {
                cout << "Enter digits combo (2 - 9) (Enter q to quit): ";
                string str = GetLine();
                if(str == "q")
                {
                        break;
                }
                ListCompletions(str, lex);
        }
        return 0;
}

void recursionPrefix(Vector<string> & combination, string prefix, string rest)
{
        if(rest.size() == 0 && prefix != "")
        {
                combination.add(prefix);
        }
        else
        {
                string options = digit2letters(rest[0]);
                int size = options.size();
                for(int i = 0; i < size; i ++)
                {
                        recursionPrefix(combination, prefix + options[i], rest.substr(1));
                }
        }
}

string digit2letters(char ch)
{
    switch (ch) {
        case '2': return ("abc");
        case '3': return ("def");
        case '4': return ("ghi");
        case '5': return ("jkl");
        case '6': return ("mno");
        case '7': return ("pqrs");
        case '8': return ("tuv");
        case '9': return ("wxyz");
        default: cout << "Illegal digit" << endl;
    }
    return ("");
}

void ListCompletions(string digits, Lexicon & lex)
{
        Vector<string> combination;
        recursionPrefix(combination, "", digits);
        for(int i = 0; i < combination.size(); i++)
        {
                recursionCompletion(lex, combination[i]);
        }
}

void recursionCompletion(Lexicon & lex, string prefix)
{
        if(lex.containsWord(prefix))
        {
                cout << prefix << endl;
        }
        if(lex.containsPrefix(prefix))
                {
                        int size = letters.size();
                        for(int i = 0; i < size; i++)
                        {
                                recursionCompletion(lex, prefix + letters[i]);
                        }
                }
                else
                {
                        return;
                }

}
