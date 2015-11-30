#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#define SIZE 26

using namespace std;

void CountLetters(string filename);

int main()
{
	string filename = "letters.txt";
	CountLetters(filename);
	getchar();
	return 0;
}

void CountLetters(string filename)
{
	string readFile = "";
	string temp;
	ifstream in;
	vector<int> letters;

	for (int i = 0; i < SIZE; i++)
	{
		letters.push_back(0);
	}

	in.open(filename, ios::in);
	while (getline(in, temp))
	{
		transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
		readFile += temp;
	}
	in.close();

        int size = readFile.size();
	for (int counter = 0; counter < size; counter++)
	{
		int index = readFile[counter] - 'a';
		if (index >= 0 && index < SIZE)
		{
			letters[index] ++;
		}
	}
	for (int counter = 0; counter < SIZE; counter++)
	{
		char letter = 'a' + counter;
		cout << letter << ": " << letters[counter] << endl;
	}
}
