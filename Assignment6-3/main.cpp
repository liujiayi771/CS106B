#include <iostream>
#include <iomanip>
#include "heap.h"
#include "random.h"

using namespace std;

int main()
{
        Randomize();
        Heap heap;
        heap.add(35);
        heap.add(30);
        heap.add(21);
        heap.add(6);
        heap.add(4);
        heap.add(20);
        heap.add(17);
        heap.add(5);
        heap.add(3);
        heap.add(20);
        heap.add(25);
        cout << "Enqueue order: 35 30 21 6  4  20 17  5  3  20 25" << endl;
        int size = heap.size();
        cout << "Dequeue order: ";
        for(int i = 0; i < size; i++)
        {
                        cout << setw(2) << heap.remove() << " ";
        }
        return 0;
}
