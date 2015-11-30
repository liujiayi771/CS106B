#include <iostream>
#include "chunklist.h"

using namespace std;

int main()
{
        ChunkList* chunklist = new ChunkList;
        chunklist->add(18);
        chunklist->add(16);
        chunklist->add(14);
        chunklist->add(13);
        chunklist->add(12);
        chunklist->add(10);
        chunklist->add(8);
        chunklist->add(6);
        chunklist->add(17);
        chunklist->add(15);
        chunklist->add(5);
        chunklist->add(19);
        chunklist->add(20);
        chunklist->add(21);
        chunklist->add(22);
        chunklist->add(17);
        chunklist->remove(17);
        chunklist->remove(16);
        chunklist->display();
        return 0;
}
