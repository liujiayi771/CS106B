#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool IsCorrectlyNested(string htmlStr, stack<string> &HTMLelements);

int main() {

	string htmlStr = "<html><b><i>CS106 rules!</i></b><p>CS106</p></html>";
	stack<string> HTMLelements;
	IsCorrectlyNested(htmlStr, HTMLelements);

	int until = HTMLelements.size();
	for(int i = 0; i < until; i++){
		cout << HTMLelements.top() << endl;
		HTMLelements.pop();
	}

	return 0;
}

bool IsCorrectlyNested(string htmlStr, stack<string> &HTMLelements){
	string original = htmlStr;
	int check = 0;
	while(htmlStr != ""){
		int first = htmlStr.find("<");
		int second = htmlStr.find(">");
		if(htmlStr.at(first + 1) != '/') {
			HTMLelements.push(htmlStr.substr(first + 1, second - 1));
		}
		if(htmlStr.at(first + 1) == '/'){
			if(htmlStr.substr(first + 2, second - (first + 2)) == HTMLelements.top()){
				HTMLelements.pop();
				check = 1;
			}
			else{
				check = 0;
			}
		}
		htmlStr = htmlStr.substr(second + 1);
	}
	if(check == 1){
		cout << "Correctly nested!" << endl;
		return true;
	}
	else{
		cout << "Not correctly nested!" << endl;
		return false;
	}
}
