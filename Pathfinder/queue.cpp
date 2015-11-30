/*
 * File: queue.cpp
 * ---------------
 * This file implements the Queue template class using a linked
 * list of cells. 
 */

#include "queue.h"
#include "genlib.h"


/*
 * Class: Queue
 * ------------
 * In this representation, the queue is a linked list of cells.
 * The next item to be dequeued is found at the cell addressed
 * by the head field.  The tail field points to the last element
 * in the queue, which allows Enqueue to operate in constant time.
 * The empty queue is indicated by a NULL head pointer.
 */

template <typename ElementType>
Queue<ElementType>::Queue()
{
    head = NULL;
}

template <typename ElementType>
Queue<ElementType>::~Queue()
{
    cellT *cp, *next;

    cp = head;
    while (cp != NULL) {
        next = cp->link;
        delete cp;
        cp = next;
    }
}

template <typename ElementType>
void Queue<ElementType>::Enqueue(ElementType element)
{
    cellT *cp;

    cp = new cellT;
    cp->value = element;
    cp->link = NULL;
    if (head == NULL) {
        head = cp;
    } else {
        tail->link = cp;
    }
    tail = cp;
}

template <typename ElementType>
ElementType Queue<ElementType>::Dequeue()
{
    ElementType result;
    cellT *cp;

    cp = head;
    if (cp == NULL) {
        Error("Dequeue: queue is empty");
    }
    result = cp->value;
    head = cp->link;
    delete cp;
    return (result);
}

template <typename ElementType>
bool Queue<ElementType>::IsEmpty()
{
    return (head == NULL);
}

template <typename ElementType>
bool Queue<ElementType>::IsFull()
{
    return (false);
}

template <typename ElementType>
int Queue<ElementType>::Length()
{
    int n;

    n = 0;
    for (cellT *cp = head; cp != NULL; cp = cp->link) n++;
    return (n);
}

template <typename ElementType>
ElementType Queue<ElementType>::ElementAt(int index)
{
    cellT *cp;

    if (index < 0 || index >= Length()) {
        Error("Queue element is out of range");
    }
    cp = head;
    for (int i = 0; i < index; i++) cp = cp->link;
    return (cp->value);
}

