#include <iostream>
#include "set.h"
#include "simpio.h"
using namespace std;

Set<string> generatePermutations(string str);
int main() {
        cout << "Enter a string: ";
        string str = GetLine();
        cout << "The permutation of \"" << str << "\" are: " << endl;
        foreach(string s in generatePermutations(str)) {
                cout << " \"" << s << "\"" << endl;
        }
        return 0;
}
Set<string> generatePermutations(string str) {
        Set<string> result;
        if(str == "") {
                result += "";
        } else {
                for (int i = 0; i < str.length(); i++) {
                        char ch = str[i];
                        string rest = str.substr(0, i) + str.substr(i + 1);
                        foreach (string s in generatePermutations(str)) {
                                result += ch + s;
                        }
                }
        }
        return result;
}

