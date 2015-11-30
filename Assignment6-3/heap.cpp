#include <iostream>
#include "heap.h"

using namespace std;

void Heap::exchange(int i, int j)
{
        int temp = value[i - 1];
        value[i - 1] = value[ j - 1];
        value[j - 1] = temp;
}

void Heap::rise()
{
        int k = value.size();
        while(k / 2 >= 1)
        {
                int j = k / 2;
                if(value[k - 1] > value[j - 1])
                        exchange(k, j);
                else
                        break;
                k = j;
        }
}

void Heap::add(int newElem)
{
        value.add(newElem);
        rise();
}

int Heap::remove()
{
        int result = value[0];
        int N = value.size();
        exchange(1, N);
        value.removeAt(N - 1);
        N = value.size();
        int k = 1;
        while(2 * k <= N)
        {
                int j = 2 * k;
                if(j < N && value[j-1] < value[j])
                        j++;
                if(value[k-1] > value[j-1])
                        break;
                exchange(k, j);
                k = j;
        }
        return result;
}

void Heap::display()
{
        for(int i = 0; i < value.size(); i++)
        {
                cout << value[i] << " ";

                        cout << endl;
        }
}
