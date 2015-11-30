/*
 * File: stack.cpp
 * ---------------
 * This file implements the Stack template class using a linked
 * list to represent the stack.
 */

#include "stack.h"
#include <cstdlib>

/* Exported entries */

template <typename ElementType>
Stack<ElementType>::Stack()
{
    start = NULL;
}

template <typename ElementType>
Stack<ElementType>::~Stack()
{
    cellT *cp, *next;

    cp = start;
    while (cp != NULL) {
        next = cp->link;
        delete cp;
        cp = next;
    }
}


template <typename ElementType>
void Stack<ElementType>::Push(ElementType element)
{
    cellT *cp;

    cp = new cellT;
    cp->element = element;
    cp->link = start;
    start = cp;
}

 
template <typename ElementType>
ElementType Stack<ElementType>::Pop()
{
    ElementType result;
    cellT *cp;

    if (IsEmpty()) Error("Pop of an empty stack");
    cp = start;
    result = cp->element;
    start = cp->link;
    delete cp;
    return (result);
}

template <typename ElementType>
bool Stack<ElementType>::IsEmpty()
{
    return (start == NULL);
}

template <typename ElementType>
bool Stack<ElementType>::IsFull()
{
    return (false);
}

template <typename ElementType>
int Stack<ElementType>::Depth()
{
    int n;

    n = 0;
    for (cellT *cp = start; cp != NULL; cp = cp->link) n++;
    return (n);
}

template <typename ElementType>
ElementType Stack<ElementType>::ElementAt(int depth)
{
    cellT *cp;

    if (depth < 0 || depth >= Depth()) {
        Error("Non-existent stack element");
    }
    cp = start;
    for (int i = 0; i < depth; i++) cp = cp->link;
    return (cp->element);
}


template <typename ElementType>
Stack<ElementType> *Stack<ElementType>::Copy()
{
    Stack *copy = new Stack();
	cellT *prevCell = NULL;
    
    for (cellT *cp = start; cp != NULL; cp = cp->link) {
    	cellT *newCell = new cellT;
    	newCell->element = cp->element;
   		newCell->link = NULL;
    	if (prevCell == NULL) copy->start = newCell;
    	else prevCell->link = newCell;
    	prevCell = newCell;
	}
    return copy;
}

