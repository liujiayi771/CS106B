/*
 * File: iterator.h
 * ----------------
 * This file implements an iterator class template.
 */

#ifndef _iterator_h
#define _iterator_h

/*
 * Class: Iterator
 * ---------------
 * This class is used to iterate over a collection of elements.
 */

template <typename ElemType>
class Iterator {

 public:

	/*
	 * Constructor: Iterator
	 * Usage: iter = new Iterator<double>();
	 * ------------------------------------
	 * The constructor allocates a new iterator with no entries.
	 */

	Iterator();

	/*
	 * Destructor: ~Iterator
	 * Usage: delete iter;
	 * --------------------
	 * The destructor frees the storage associated with the 
	 * iterator.
	 */

	~Iterator();

	 /*
	 * Member function: HasNext
	 * Usage: if (iter->HasNext())...
	 * ------------------------------
	 * This function returns true until all the values are
	 * exhausted, after which it returns false.
	 */
	bool HasNext();

	/*
	 * Member function: Next
	 * Usage: value = iter->Next();
	 * ----------------------------
	 * This function advances the iterator and returns the
	 * the next value. An Error is raised if Next is called
	 * when HasNext would return false.
	 */
	ElemType Next();

	/*
	 * Member function: AddElement
	 * Usage: iter->AddElement(elem);
	 * ------------------------------
	 * This function adds a new element to the iterator. It is
	 * intended to be called by the container when initializing
	 * the iterator to hold the collection values to be
	 * iterated over.
	 */
	void AddElement(ElemType elem);

  private: 

	struct cellT {
	  ElemType elem;
	  cellT *link;
	};

	cellT *start, *tail;
};

#include "iterator.cpp"

#endif
