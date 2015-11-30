/*
 * File: pqheap.cpp
 * --------------------
 * This file implements the priority queue class as a max heap
 * stored in a dynmaic array.
 *
 * Julie Zelenski, CS106 Winter 2005
 * Last modified: Mon Feb 28 18:08:54 PST 2005
 */
 
#include "pqueue.h"
#include "genlib.h"

#define CHUNK_SIZE 500


template <typename ElemType>
PQueue<ElemType>::PQueue(cmpFn cmp)
{
    numAllocated = CHUNK_SIZE;
    elements = new ElemType[numAllocated];
    numUsed = 0;
    this->cmp = cmp;
}


template <typename ElemType>
PQueue<ElemType>::~PQueue()
{
    delete[] elements;
}

template <typename ElemType>
bool PQueue<ElemType>::IsFull()
{
    return (false);  
}


template <typename ElemType>
bool PQueue<ElemType>::IsEmpty()
{
    return (numUsed == 0);  
}

template <typename ElemType>
static void Swap(ElemType &a, ElemType &b)
{
	ElemType tmp;
	
	tmp = a;
	a = b;
	b = tmp;
}

template <typename ElemType>
void PQueue<ElemType>::Enqueue(ElemType newValue)
{  
 	if (numUsed + 1 == numAllocated) { // remember slot[0] not used!
 		numAllocated += CHUNK_SIZE;
 		ElemType *newArray = new ElemType[numAllocated];
 		for (int i = 1; i < numUsed + 1; i++)
 			newArray[i] = elements[i];
 		delete[] elements;
 		elements = newArray;
 	}
 	int current = ++numUsed;
 	elements[current] = newValue;	// assign in last position  
 	while ((current > 1) &&  cmp(elements[current],elements[current/2]) > 0) {
 		Swap(elements[current], elements[current/2]);
 		current /= 2;
 	}
}


template <typename ElemType>
ElemType PQueue<ElemType>::DequeueMax()
{	
	if (IsEmpty()) Error ("tried to extract from empty queue!"); 
	
	ElemType max = elements[1];	// save max value to return from function
	elements[1] = elements[numUsed--]; // copy lastmost value to root node
	Heapify(1);		// restore heap property
	return max;
}



template <typename ElemType>
int PQueue<ElemType>::MaxElement(int root) 
{
	int largest;
	
	int left = root*2;
	int right = left +1;
	
	if (left <= numUsed && cmp(elements[left],elements[root]) > 0 ) 
		 largest = left;
	else 
		largest = root;
	if (right <= numUsed && cmp(elements[right], elements[largest]) > 0) 
		largest = right;
	return largest;
}




template <typename ElemType>
void PQueue<ElemType>::Heapify(int current)
{
	int largest = MaxElement(current);
	if (largest != current) {
		Swap(elements[largest], elements[current]);
		Heapify(largest);
	}
}

