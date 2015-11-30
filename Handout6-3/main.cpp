#include <iostream>
#include "vector.h"
#include "cmpfn.h"
#include "random.h"

using namespace std;

struct Car {
    string name;
    int weight;
    int numAirbags;
};

template <typename Type>
Type FindMax(Vector<Type> & data, int (cmpFn)(Type one, Type two) = OperatorCmp);

int cmp(Car one, Car two)
{
    if(one.numAirbags < two.numAirbags) {
        return -1;
    }
    if(one.numAirbags > two.numAirbags) {
        return 1;
    }
    if(one.numAirbags == two.numAirbags && one.weight < two.weight) {
        return -1;
    }
    if(one.numAirbags == two.numAirbags && one.weight > two.weight) {
        return 1;
    }
    return 0;
}

int main()
{
    Randomize();
    Vector<Car> data;
    for(int i = 0; i < 100; i++) {
        int numAirbags = RandomInteger(0, 100);
        int weight = RandomInteger(0, 1000);
        string name = "car";
        Car temp;
        temp.numAirbags = numAirbags;
        temp.weight = weight;
        temp.name = name;
        data.add(temp);
    }
    Car result = FindMax(data, cmp);
    cout << "max Car's number of airbags: " << result.numAirbags << endl;
    cout << "max Car's weight: " << result.weight << endl;
    return 0;
}

template <typename Type>
Type FindMax(Vector<Type> & data, int (cmpFn)(Type one, Type two) = OperatorCmp)
{
    Type max = data[0];
    for(int i = 1; i < data.size(); i++) {
        if(cmpFn(max, data[i]) < 0) {
            max = data[i];
        }
    }
    return max;
}
