/*
 * File: queue.h
 * -------------
 * This interface defines a queue template class, defined in terms
 * of a placeholder element type.  The client specializes the
 * queue by specifying the particular element type being stored.
 */

#ifndef _queue_h
#define _queue_h

/*
 * Class: Queue
 * ------------
 * A queue stores a linear collection of client-supplied
 * values that are stored and retrieved using Enqueue and
 * Dequeue operations. Because the class is defined with 
 * private data members, clients have no access to the 
 * underlying fields and can only manipulate a queue object 
 * through its public member functions.
 */

template <typename ElementType>
class Queue {
 public:

	/*
	 * Constructor: Queue
	 * Usage: queue = new Queue<int>();
	 * -------------------------------
	 * This function initializes an empty queue.
	 */

	Queue();

	/*
	 * Destructor: ~Queue
	 * Usage: delete queue;
	 * --------------------
	 * This function frees the storage associated with queue.
	 */

	~Queue();

	/*
	 * Member function: Enqueue
	 * Usage: queue->Enqueue(element);
	 * -------------------------------
	 * This function adds element to the end of the queue.
	 */

	void Enqueue(ElementType element);


	/*
	 * Member function: Dequeue
	 * Usage: element = queue->Dequeue();
	 * ----------------------------------
	 * This function removes the data value at the head of the queue
	 * and returns it to the client.  If the queue is empty, Dequeue
	 * calls Error with an appropriate message.
	 */

	ElementType Dequeue();

	/*
	 * Member functions: IsEmpty, IsFull
	 * Usage: if (queue->IsEmpty()) . . .
	 *        if (queue->IsFull()) . . .
	 * --------------------------------------
	 * These functions test whether the queue is empty or full.
	 */

	bool IsEmpty();
	bool IsFull();

	/*
	 * Member function: Length
	 * Usage: n = queue->Length();
	 * ---------------------------
	 * This function returns the number of elements in the queue.
	 */

	int Length();

	/*
	 * Member function: ElementAt
	 * Usage: element = queue->ElementAt(index);
	 * -----------------------------------------
	 * This function returns the element at the specified index in
	 * the queue, where the head of the queue is defined as index 0.
	 * For example, calling queue->ElementAt(0) returns the
	 * initial element from the queue without removing it.  If the
	 * caller tries to select an element that is out of range,
	 * ElementAt calls Error.  Note: This function is not a
	 * fundamental queue operation and is instead provided mainly
	 * to facilitate debugging.
	 */

	ElementType ElementAt(int index);

  private:
	  struct cellT {
	    ElementType value;
	    cellT *link;
	  };

	  cellT *head, *tail;
};

#include "queue.cpp"

#endif
