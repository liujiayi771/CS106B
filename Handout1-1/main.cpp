#include <iostream>
#include <string>

using namespace std;

string CensorString1(string text, string remove);
void CensorString2(string &text, string remove);

int main()
{
	string text1 = "Stanford University";
	string remove1 = "nt";
	string text2 = "Llamas like to laugh";
	string remove2 = "la";
	cout << "test1 for CensorString1: " << CensorString1(text1, remove1) << endl;
	cout << "test2 for CensorString1: " << CensorString1(text2, remove2) << endl;
	CensorString2(text1, remove1);
	cout << "test1 for CensorString2: " << text1 << endl;
	CensorString2(text2, remove2);
	cout << "test2 for CensorString2: " << text2 << endl;
	getchar();
	return 0;
}

string CensorString1(string text, string remove)
{
	string::iterator it;
	int size = remove.size();
	for (it = text.begin(); it != text.end(); it++)
	{
		for (int i = 0; i < size; i++)
		{
			if (*it == remove[i])
			{
				text.erase(it);
			}
		}
	}
	return text;
}

void CensorString2(string &text, string remove)
{
	string::iterator it;
	int size = remove.size();
	for (it = text.begin(); it != text.end(); it++)
	{
		for (int i = 0; i < size; i++)
		{
			if (*it == remove[i])
			{
				text.erase(it);
			}
		}
	}
}
