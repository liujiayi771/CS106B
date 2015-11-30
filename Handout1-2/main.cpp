#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "random.h"

#define SIZE 100

using namespace std;

typedef struct
{
	vector<int> score;
	int max;
	int min;
	double average;
}Score;

void create_score(string filename);
Score read_score(string filename);

int main()
{
        Randomize();
	Score readScore;
	create_score("score.txt");
	readScore = read_score("score.txt");
	cout << "size: " << readScore.score.size() << endl;
	cout << "max: " << readScore.max << endl;
	cout << "min: " << readScore.min << endl;
	cout << "average: " << readScore.average << endl;
	getchar();
	return 0;
}

void create_score(string filename)
{
	ofstream out;
	out.open(filename, ios::out);
	for (int i = 0; i < SIZE; i++)
	{
		out << RandomInteger(50, 100) << endl;
	}
	out.close();
}

Score read_score(string filename)
{
	Score readScore;
	ifstream in;
	string temp;
	int max = 0;
	int min = 100;
	int sum = 0;
	in.open(filename, ios::in);
	while (getline(in, temp))
	{
		readScore.score.push_back(atoi(temp.c_str()));
	}
	in.close();
	int size = readScore.score.size();
	for (int i = 0; i < size; i++)
	{
		sum += readScore.score[i];
		if (readScore.score[i] > max)
			max = readScore.score[i];
		if (readScore.score[i] < min)
			min = readScore.score[i];
	}
	readScore.max = max;
	readScore.min = min;
	readScore.average = (double)sum / SIZE;
	return readScore;
}
