#include <iostream>
#include "vector.h"

using namespace std;

bool IsMeasurable(int target, Vector<int> & weights);
bool curMeasurable(Vector<int> weights, int target, int index);

int main()
{
        Vector<int> sampleWeights;
        sampleWeights.add(3);
        sampleWeights.add(1);
        if(IsMeasurable(2, sampleWeights))
                cout << "TRUE" << endl;
        else
                cout << "FALSE" << endl;
        return 0;
}

bool IsMeasurable(int target, Vector<int> & weights)
{
        return curMeasurable(weights, target, 0);
}

bool curMeasurable(Vector<int> weights, int target, int index)
{
        if(target == 0)
                return true;
        if(index == weights.size())
                return false;
        return (curMeasurable(weights, target + weights[index], index + 1) || curMeasurable(weights, target - weights[index], index + 1) || curMeasurable(weights, target, index +1));
}
