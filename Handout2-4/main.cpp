#include <iostream>
#include <istream>
#include "map.h"
#include "simpio.h"

using namespace std;

char MostFrequentCharacter(ifstream & file_in, int & numOccurrences);

int main()
{
        int numOccurrences;
        cout << "Enter the filename: ";
        string filename;
        filename = GetLine();
        ifstream file_in;
        file_in.open(filename.c_str());
        if(!file_in)
        {
                cout << "Open file failed" << endl;
                return 0;
        }
        char ch = MostFrequentCharacter(file_in, numOccurrences);
        cout << ch << " occurs most frequent and it occurs " << numOccurrences << " times" << endl;
        return 0;
}

char MostFrequentCharacter(ifstream & file_in, int & numOccurrences)
{
        Map<int> file;
        while(1)
        {
                string str = "";
                char currentChar;
                currentChar = file_in.get();
                str += currentChar;
                if(currentChar == EOF)
                        break;
                if(!file.containsKey(str))
                        file.put(str, 1);
                else
                {
                        file[str] ++;
                }
        }
        Map<int>::Iterator it = file.iterator();
        int max = 0;
        char maxChr;
        while(it.hasNext())
        {
                string key = it.next();
                if(file[key] > max)
                {
                        max = file[key];
                        maxChr = key[0];
                }
        }
        numOccurrences = max;
        return maxChr;
}
