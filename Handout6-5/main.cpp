#include <iostream>
#include "vector.h"
#include "cmpfn.h"
#include "set.h"

using namespace std;

template <typename Type>
void RemoveDuplicates(Vector<Type> & data, int (cmpFn)(Type, Type) = OperatorCmp);

int cmpFn(int one, int two)
{
    if(one < two) {
        return -1;
    }
    if(one > two) {
        return 1;
    }
    return 0;
}

int CompareIntAbsolute(int first, int second) {
    first = abs(first);
    second = abs(second);
    if(first < second) {
        return -1;
    }
    if(first > second) {
        return 1;
    }
    return 0;
}

int main()
{
    Vector<int> data1, data2;
    data1.add(1);data1.add(2);data1.add(3);data1.add(4);data1.add(2);data1.add(3);data1.add(3);
    data2.add(1);data2.add(2);data2.add(-3);data2.add(4);data2.add(-2);data2.add(3);data2.add(-3);
    cout << "Before remove duplicates: ";
    for(int i = 0; i < data1.size(); i++) {
        cout << data1[i] << " ";
    }
    cout << endl;
    RemoveDuplicates(data1, cmpFn);
    cout << "After remove duplicates: ";
    for(int i = 0; i < data1.size(); i++) {
        cout << data1[i] << " ";
    }
    cout << endl;
    cout << "Before remove duplicates: ";
    for(int i = 0; i < data2.size(); i++) {
        cout << data2[i] << " ";
    }
    cout << endl;
    RemoveDuplicates(data2, CompareIntAbsolute);
    cout << "After remove duplicates: ";
    for(int i = 0; i < data2.size(); i++) {
        cout << data2[i] << " ";
    }
    cout << endl;
    return 0;
}

template <typename Type>
void RemoveDuplicates(Vector<Type> & data, int (cmpFn)(Type, Type) = OperatorCmp)
{
    Set<Type> record(cmpFn);
    for(int i = 0; i < data.size(); i++) {
        Type temp = data[i];
        if(!record.contains(temp)) {
            record.add(temp);
        } else {
            data.removeAt(i);
            i--;
        }
    }
}
