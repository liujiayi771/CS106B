#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED
#include "vector.h"
#include "cmpfn.h"
#include "genlib.h"
#include <iostream>

using namespace std;

template <typename T>
class Heap
{
public:
    typedef int (*cmpFn)(T one, T two);

    Heap(cmpFn cmp = OperatorCmp);

    int size()
    {
        return value.size();
    }

    bool lessThan(int i, int j, cmpFn cmp)
    {
        return cmp(value[i - 1], value[j - 1]) < 0;
    }

    void exchange(int i, int j)
    {
        T temp = value[i - 1];
        value[i - 1] = value[j - 1];
        value[j - 1] = temp;
    }

    void rise(cmpFn cmp)
    {
        int k = value.size();
        while(k / 2 >= 1) {
            int j = k / 2;
            if(!lessThan(k, j, cmp))
                exchange(k, j);
            else
                break;
            k = j;
        }
    }

    void add(T newElem)
    {
        value.add(newElem);
        rise(this->cmp);
    }

    T remove(cmpFn cmp = OperatorCmp)
    {
        T result = value[0];
        int N = value.size();
        exchange(1, N);
        value.removeAt(N - 1);
        N = value.size();
        int k = 1;
        while(2 * k <= N) {
            int j = 2 * k;
            if(j < N && lessThan(j, j + 1, cmp))
                j++;
            if(!lessThan(k, j, cmp))
                break;
            exchange(k, j);
            k = j;
        }
        return result;
    }

    void display()
    {
        for(int i = 0; i < value.size(); i++) {
            cout << value[i] << " " << endl;
        }
    }
private:
    Vector<T> value;
    cmpFn cmp;
};

template <typename T>
Heap<T>::Heap(cmpFn cmp)
{
    this->cmp = cmp;
}

#endif // HEAP_H_INCLUDED
