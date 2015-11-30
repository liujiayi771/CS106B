/*
 * File: set.cpp
 * -------------
 * This file implements the set class template defined in set.h.
 */

#include "set.h"

template <typename ElemType>
Set<ElemType>::Set(cmpFnT clientFn)
{
    bst = new BST<ElemType>(clientFn);
    cmp = clientFn;
    nElements = 0;
}


template <typename ElemType>
Set<ElemType>::~Set()
{
    delete bst;
}

/*
 * Implementation notes: NElements, IsEmpty
 * ----------------------------------------
 * For efficiency, the class stores the number of elements
 * as a private data member, updating it as necessary.
 */

template <typename ElemType>
int Set<ElemType>::NElements()
{
    return (nElements);
}

template <typename ElemType>
bool Set<ElemType>::IsEmpty()
{
    return (nElements == 0);
}

template <typename ElemType>
void Set<ElemType>::AddElement(ElemType element)
{
    if (bst->Insert(element))
      nElements++;
}


template <typename ElemType>
void Set<ElemType>::RemoveElement(ElemType element)
{
	   if (bst->Remove(element))
      nElements--;
}

template <typename ElemType>
ElemType *Set<ElemType>::FindElement(ElemType element)
{
	return (bst->Find(element));
}

template <typename ElemType>
bool Set<ElemType>::Contains(ElemType element)
{
    return (bst->Find(element) != NULL);
}


/*
 * Implementation notes: Set operations
 * ------------------------------------
 * The functions IsSubsetOf, Union, Intersection, and SetDifference
 * are similar in structure.  Each one uses an iterator to walk over
 * the appropriate set.
 */

template <typename ElemType>
bool Set<ElemType>::IsEqual(Set *otherSet)
{
    return (IsSubsetOf(otherSet) && otherSet->IsSubsetOf(this));
}

template <typename ElemType>
bool Set<ElemType>::IsSubsetOf(Set *otherSet)
{
    Iterator<ElemType> *iterator;
    bool result;

    result = true;
    iterator = CreateIterator();
    while (result && iterator->HasNext()) {
        if (!otherSet->Contains(iterator->Next()))
	           result = false;
    }
    delete iterator;
    return (result);
}

template <typename ElemType>
Iterator<ElemType> *Set<ElemType>::CreateIterator()
{
    return (bst->CreateIterator());
}

 template <typename ElemType>
Set<ElemType> *Set<ElemType>::Union(Set *otherSet)
{
	    Iterator<ElemType> *iterator;
    Set *result;
    
    result = new Set<ElemType>(cmp);
    iterator = CreateIterator();
    while (iterator->HasNext()) {
        result->AddElement(iterator->Next());
    }
    delete iterator;
    iterator = otherSet->CreateIterator();
    while (iterator->HasNext()) {
        result->AddElement(iterator->Next());
    }
    delete iterator;
    return (result);
}

template <typename ElemType>
Set<ElemType> *Set<ElemType>::Intersection(Set *otherSet)
{
    Iterator<ElemType> *iterator;
    Set *result;

    result = new Set<ElemType>(cmp);
	    iterator = CreateIterator();
    while (iterator->HasNext()) {
        ElemType elem = iterator->Next();
        if (otherSet->Contains(elem))
            result->AddElement(elem);
    }
    delete iterator;
    return (result);
}

template <typename ElemType>
Set<ElemType> *Set<ElemType>::SetDifference(Set *otherSet)
{
    Iterator<ElemType> *iterator;
    ElemType element;
    Set *result;

    result = new Set<ElemType>(cmp);
	    iterator = CreateIterator();
    while (iterator->HasNext()) {
        ElemType elem = iterator->Next();
        if (!otherSet->Contains(elem))
            result->AddElement(elem);
    }
    delete iterator;
    return (result);
}
