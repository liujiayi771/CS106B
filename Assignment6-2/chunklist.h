#ifndef CHUNKLIST_H_INCLUDED
#define CHUNKLIST_H_INCLUDED

#include "vector.h"

const int MaxElemsPerBlock = 4;

class ChunkList
{
private:
        struct LNode
        {
                Vector<int> value;
                LNode* next = NULL;
        };
        LNode* header;
public:
        ChunkList();
        ~ChunkList();
        int size();
        bool isEmpty();
        void add(int newElem);
        void remove(int removeElem);
        void display();
        LNode* getHeader();
};

#endif // CHUNKLIST_H_INCLUDED
