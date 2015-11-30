#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED

#include "vector.h"

class Heap
{
private:
        Vector<int> value;
        void exchange(int i, int j);
        void rise();
public:
        void add(int newElem);
        int remove();
        int size()
        {
                return value.size();
        }
        void display();
};

#endif // HEAP_H_INCLUDED
