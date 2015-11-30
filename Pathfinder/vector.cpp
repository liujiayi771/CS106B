/* File: vector.cpp
 * ----------------
 * This file implements the Vector template class using a dynamic array.
 */

#include "vector.h"

template <typename ElemType>
Vector<ElemType>::Vector()
{	
	elems = new ElemType[4];
	numAllocated = 4;
	numUsed = 0;
}


template <typename ElemType>
Vector<ElemType>::~Vector()
{	
	delete[] elems;
}

template <typename ElemType>
int Vector<ElemType>::Length()
{	
	return (numUsed);
}

template <typename ElemType>
ElemType Vector<ElemType>::ElementAt(int n)
{	
	if (n < 0 || n >= numUsed)
		Error("Attempt to access vector element out of bounds");
	return elems[n];
}

template <typename ElemType>
void Vector<ElemType>::AddElement(ElemType elem)
{	
	InsertAt(elem, numUsed);
}

template <typename ElemType>
void Vector<ElemType>::InsertAt(ElemType elem, int pos)
{	
	if (pos < 0 || pos > numUsed)
		Error("Attempt to insert vector element out of bounds");
	if (numUsed == numAllocated) {
		ElemType *newArr = new ElemType[numAllocated*2];
		numAllocated *= 2;
		for (int i = 0; i < numUsed; i++)
			newArr[i] = elems[i];
		delete[] elems;
		elems = newArr;
	}
	for (int i = numUsed; i > pos; i--)
		elems[i] = elems[i-1];
	elems[pos] = elem;
	numUsed++;
}


template <typename ElemType>
void Vector<ElemType>::RemoveAt(int pos)
{	
	if (pos < 0 || pos >= numUsed)
		Error("Attempt to remove vector element out of bounds");
	for (int i = pos; i < numUsed - 1; i++)
		elems[i] = elems[i+1];
	numUsed--;
}
