#include <iostream>
#include "vector.h"

using namespace std;

int CutStock(Vector<int> & requests, int stockLength);
void recursionCutStock(Vector<int> requests, Vector<int> stocks, int stockLength, int & minStockPipes, int index);

int main()
{
        Vector<int> requests;
        requests.add(4);
        requests.add(3);
        requests.add(4);
        requests.add(1);
        requests.add(7);
        requests.add(8);
        //requests.add(3);
        //requests.add(2);
        cout << "The minimum number of stock pipes needed to service all request: ";
        cout << CutStock(requests, 10) << endl;
        return 0;
}

int CutStock(Vector<int> & requests, int stockLength)
{
        Vector<int> emptyVec;
        int minStockPipes = 1000;
        recursionCutStock(requests, emptyVec, stockLength, minStockPipes, 0);
        return minStockPipes;
}

void recursionCutStock(Vector<int> requests, Vector<int> stocks, int stockLength, int & minStockPipes, int index)
{
        if(index == requests.size())
        {
                if(minStockPipes > stocks.size())
                {
                        minStockPipes = stocks.size();
                }
                return;
        }
        else
        {
                for(int i = 0; i < stocks.size(); i++)
                {
                        if(stocks[i] + requests[index] <= stockLength)
                        {
                                stocks[i] += requests[index];
                                recursionCutStock(requests, stocks, stockLength, minStockPipes, index + 1);
                                stocks[i] -= requests[index];
                        }
                }
                stocks.add(requests[index]);
                recursionCutStock(requests, stocks, stockLength, minStockPipes, index + 1);
        }
}
