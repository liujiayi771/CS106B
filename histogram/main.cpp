#include <iostream>
#include <fstream>
#include <string>
#include "simpio.h"
#include "stack.h"

using namespace std;

int main()
{
        string filename;
        string singleScore;
        int num[10] = {0};
        Stack<string> score;
        ifstream file_in;
        cout << "Enter the file name: ";
        filename = GetLine();
        file_in.open(filename.c_str());
        while(!file_in)
        {
                cout << "Please Enter the correct file name!" << endl;
                cout << "Enter the file name: ";
                filename = GetLine();
                file_in.open(filename.c_str());
        }
        while(getline(file_in, singleScore))
        {
                if(singleScore.size() == 1)
                {
                        string temp = "";
                        temp += '0';
                        singleScore = temp + singleScore;
                }
                score.push(singleScore);
        }
        file_in.close();
        while(!score.isEmpty())
        {
                string temp = score.pop();
                int i = temp[0] - '0';
                num[i] ++;
        }
        for(int i = 0; i < 10; i++)
        {
                cout << i * 10 << " - " << i * 10 + 9 << ": ";
                for(int j = 0; j < num[i]; j++)
                {
                        cout << "X";
                }
                cout << endl;
        }
        return 0;
}
