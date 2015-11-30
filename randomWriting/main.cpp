#include <iostream>
#include <fstream>
#include <string>
#include "random.h"
#include "simpio.h"
#include "vector.h"
#include "map.h"

using namespace std;

typedef struct seed
{
   int freq;
    Vector<char> followChar;
    seed()
    {
        freq = 1;
    }
}Seed;

void readFile(ifstream & file_in, int orderNum, Map<Seed> & MarkovMoudle);
void createFile(ofstream & file_out, string filename, int orderNum, Map<Seed> MarkovMoudle);

int main()
{
    Map<Seed> MarkovMoudle;
    ifstream file_in;
    ofstream file_out;
    string filename;
    string filenameOut = "file_out.txt";
    int orderNum;
    while(1)
    {
        cout << "Enter the source file name: ";
        filename = GetLine();
        file_in.open(filename.c_str());
        if(file_in.fail())
        {
                file_in.clear();
                cout << "Cannot open the file: " << filename << ", please enter again!" << endl;
        }
        else
            break;
    }
    while(1)
    {
        cout << "Enter the order of Markov model to use?(1-10): ";
        orderNum = GetInteger();
        if(orderNum >10 || orderNum < 1)
        {
                cout << "please enter the correct number!" << endl;
        }
        else
            break;
    }
    readFile(file_in, orderNum, MarkovMoudle);
    createFile(file_out, filenameOut, orderNum, MarkovMoudle);
    return 0;
}

void readFile(ifstream & file_in, int orderNum, Map<Seed> & MarkovMoudle)
{
    Vector<char> content;
    string tmp = "";
    char currentChar;
    while(1)
    {
        currentChar = file_in.get();
        if(currentChar == EOF)
            break;
        content.add(currentChar);
    }
    for(int i = 0; i < content.size() - orderNum; i++)
    {
        for(int j = 0; j < orderNum; j++)
        {
            tmp += content[i+j];
        }
        //cout << tmp << endl;
        if(MarkovMoudle.containsKey(tmp))
        {
            MarkovMoudle[tmp].freq ++;
            if((i + orderNum) < content.size())
                MarkovMoudle[tmp].followChar.add(content[i+orderNum]);
        }
        else
        {
            Seed s;
            if((i + orderNum) < content.size())
                s.followChar.add(content[i+orderNum]);
            MarkovMoudle.put(tmp, s);
        }
        tmp.clear();
    }
    file_in.close();
}

void createFile(ofstream & file_out, string filename, int orderNum, Map<Seed> MarkovMoudle)
{
    Map<Seed> temp = MarkovMoudle;
    int max = 0;
    string outcome = "";
    string currentKey = "";
    file_out.open(filename, ios::out);
    Map<Seed>::Iterator it = temp.iterator();
    while(it.hasNext())
    {
        string key = it.next();
        if(temp[key].freq > max)
        {
            max = temp[key].freq;
            currentKey = key;
        }
        if(temp[key].freq == max)
        {
            if(RandomChance(0.5))
                currentKey = key;
        }
    }
    outcome += currentKey;
    for(int i = 0; i < 20000; i++)
    {
        int size = temp[currentKey].followChar.size();
        if(size == 0)
            break;
        int num = RandomInteger(0, size );
        char currentChar = temp[currentKey].followChar[num];
        outcome += currentChar;
        string::iterator it = currentKey.begin();
        currentKey.erase(it);
        currentKey += currentChar;
    }
    file_out << outcome;
    cout << "Random writing: " << outcome;
    file_out.close();
}
