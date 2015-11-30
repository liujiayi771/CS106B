/*
 * File: iterator.cpp
 * ------------------
 * This file implements the iterator class using a linked list.
 */

#include "iterator.h"
#include "genlib.h"

template <typename ElemType>
Iterator<ElemType>::Iterator()
{
    start = tail = NULL;
}

template <typename ElemType>
Iterator<ElemType>::~Iterator()
{
	cellT *cp;
    while ((cp = start) != NULL) {
        start = cp->link;
        delete cp;
    }
}

template <typename ElemType>
bool Iterator<ElemType>::HasNext()
{
  	  return (start != NULL);
}

template <typename ElemType>
ElemType Iterator<ElemType>::Next()
{
    cellT *cp;
    ElemType elem;

    cp = start;
    if (cp == NULL) Error("Next called on empty iterator");
    elem = cp->elem;
    start = cp->link;
    delete cp;
    return elem;
}

template <typename ElemType>
void Iterator<ElemType>::AddElement(ElemType elem)
{
    cellT *cp = new cellT;
    cp->elem = elem;
    cp->link = NULL;
    if (tail == NULL) {
        start = cp;
    } else {
        tail->link = cp;
    }
    tail = cp;
}
