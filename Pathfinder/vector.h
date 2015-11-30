/*
 * File: vector.h
 * --------------
 * This interface defines a class for an ordered collection
 * that supports insertion and deletion operations.
 * The abstraction is called a "vector" primarily because that is
 * the name used for a similar concept in Java.
 */

#ifndef _vector_h_
#define _vector_h_

/*
 * Class: Vector
 * -------------
 * The class Vector stores an ordered collection of elements.
 */

template <typename ElementType>
class Vector {

 public:

	/*
	 * Constructor: Vector
	 * Usage: vec = new Vector<int>();
	 * ------------------------------
	 * This function initializes a new empty vector.
     */
	Vector();

	/*
	 * Destructor: ~Vector
	 * Usage: delete vec;
	 * ------------------
	 * This function frees the storage associated with the vector.
	 */

	~Vector();

	 
	/*
	 * Member function: Length
	 * Usage: n = vec->Length();
	 * -------------------------
	 * This function returns the number of elements in the vector.
	 */

	int Length();

	/*
	 * Member function: ElementAt
	 * Usage: element = vec->ElementAt(n);
	 * -----------------------------------
	 * This function returns the element at position n in the vector
	 * vec, where the position numbers begin at 0.  Thus, calling
	 * vec->ElementAt(0) returns the initial element in the vector;
	 * calling vec->ElementAt(vec->Length() - 1) returns the
	 * last.  The vector is unchanged by this operation, which
	 * generates an error if n is outside the range [0, N-1].
	 */

	ElementType ElementAt(int n);

	/*
	 * Member function: AddElement
	 * Usage: vec->AddElement(element);
	 * --------------------------------
	 * This function adds the element to the end of the vector. 
	 */

	void AddElement(ElementType element);


	/*
	 * Member function: InsertAt
	 * Usage: vec->InsertAt(element, pos);
	 * ------------------------------------
	 * This function inserts the element into the vector before
	 * the specified position.  Position numbers start at 0 and
	 * go up to the length of the vector, which is used to signify
	 * an insertion at the end of the vector.  The function generates
	 * an error if pos is outside the range [0, N].
	 */

	void InsertAt(ElementType element, int pos);

	/*
	 * Member function: RemoveAt
	 * Usage: vec->RemoveAt(pos);
	 * -------------------------
	 * This function removes the element at the specified position.
	 * The function generates an error if pos is outside the range
	 * [0, N-1].
	 */

	void RemoveAt(int pos);

 private:
	ElementType *elems;
	int numAllocated, numUsed;
};

#include "vector.cpp"

#endif //_vector_h_
