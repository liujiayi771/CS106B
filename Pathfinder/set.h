/*
 * File: set.h
 * -----------
 * This interface exports the Set class template, a generic
 * pattern for a set of data values.  The data values can be of
 * any type, specialized through a template placeholder. The one
 * requirement on the type is that the client must supply a
 * a comparison function that compares two elements (or be willing 
 * to use the default comparison function that relies on < and ==).
 *
 * In addition to the set operations, the set class allows 
 * iteration, as described in the iterator.h interface.  
 * The standard iterator idiom looks like this:
 *
 *     iterator = set->CreateIterator();
 *     while (iterator->HasNext()) {
 *        x = iterator->Next();
 *        . . . body of loop involving x . . .
 *     }
 *     delete iterator;
 */

#ifndef _set_h
#define _set_h

#include "cmpfn.h"
#include "iterator.h"
#include "bst.h"

/*
 * Class: Set
 * ----------
 * This class is used to represent a set of values.
 */

template <typename ElemType>
class Set {

 public: 

	/*
	 * Type: cmpFnT
	 * ------------
	 * This type defines the prototype of functions used to
	 * compare two elements.
	 */

	 typedef int (*cmpFnT)(ElemType one, ElemType two);


	/*
	 * Constructor: Set
	 * Usage: set = new Set<int>(MyCompareFn);
	 * ---------------------------------------
	 * The constructor initializes an empty set.
	 */

	Set(cmpFnT cmpFn = DefaultCmp);

	/*
	 * Destructor: ~Set
	 * Usage: delete set;
	 * --------------------
	 * The destructor frees the storage associated with set.
	 */

	~Set();

	/*
	 * Member function: NElements
	 * Usage: n = set->NElements();
	 * ----------------------------
	 * This function returns the number of elements in the set.
	 */

	int NElements();

	/*
	 * Member function: IsEmpty
	 * Usage: if (set->IsEmpty()) . . .
	 * ---------------------------------
	 * This function returns true if the set has no elements.
	 */

	bool IsEmpty();

	/*
	 * Member function: AddElement
	 * Usage: set->AddElement(element);
	 * --------------------------------
	 * This function adds a new element to an existing set.
	 */

	void AddElement(ElemType element);

	/*
	 * Member function: RemoveElement
	 * Usage: set->RemoveElement(element);
	 * -----------------------------------
	 * This functions removes the element from the set, if it exists.
	 */

	void RemoveElement(ElemType element);

	
	/*
	 * Member function: FindElement
	 * Usage: element = (set->FindElement(element)) . . .
	 * ----------------------------------------
	 * This function returns a pointer to the given element in the
	 * set if the element exists in the set.  It returns NULL otherwise.
	 */

	ElemType *FindElement(ElemType element);

	 /*
	 * Member function: Contains
	 * Usage: if (set->Contains(element)) . . .
	 * ----------------------------------------
	 * This function returns true if the element is in the set.
	 */

	bool Contains(ElemType element);

	/*
	 * Functions: IsEqual, IsSubsetOf
	 * Usage: if (s1->IsEqual(s2)) . . .
	 *        if (s1->IsSubsetOf(s2)) . . .
	 * ------------------------------------
	 * These predicate functions implement the equality and subset
	 * relations on sets, respectively.  s1->IsEqual(s2) returns
	 * true if s1 and s2 have the same elements.  s1->IsSubsetOf(s2)
	 * returns true if all elements of s1 are also elements of s2.
	 */

	bool IsEqual(Set *otherSet);
	bool IsSubsetOf(Set *otherSet);

	/*
	 * Member functions: Union, Intersection, SetDifference
	 * Usage: resultSet = s1->Union(s2);
	 *        resultSet = s1->Intersection(s2);
	 *        resultSet = s1->SetDifference(s2);
	 * -----------------------------------------
	 * These functions each return a new set, as follows:
	 *
	 * s1->Union(s2)          All elements in either s1 or s2.
	 * s1->Intersection(s2)   All elements in both s1 and s2.
	 * s1->SetDifference(s2)  All elements in s1 but not in s2.
	 */

	Set *Union(Set *otherSet);
	Set *Intersection(Set *otherSet);
	Set *SetDifference(Set *otherSet);

	/* Member function: CreateIterator
	 * Usage: iterator = set->CreateIterator();
	 * ----------------------------------------
	 * This function creates a new iterator that can be used
	 * to iterate over the elements contained in the set.
	 */

	Iterator<ElemType> *CreateIterator();

  private:
   	BST<ElemType> *bst;
   	int nElements;
   	cmpFnT cmp;
   	
};

#include "set.cpp"

#endif
