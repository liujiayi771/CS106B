/*
 * File: pqueue.h
 * --------------
 * Defines the interface for the priority queue class. 
 * 
 * Last modified: Mon Feb 28 17:58:58 PST 2005 juliez
 */
 
 
#ifndef _pqueue_h
#define _pqueue_h

#include "cmpfn.h"

/*
 * Class: PQueue
 * -------------
 * This is the class for a priority queue.  This is not
 * simple FIFO queue, it is a priority queue, where elements are
 * retrieved in order of priority, not just by longevity in queue.
 * The elements are integers and the integer is assumed to represent 
 * the priority (larger integer is higher priority).
 */
template <typename ElemType>
class PQueue 
{
  public:

	/*
	 * Type: cmpFnT
	 * ------------
	 * This type defines the prototype of functions used to
	 * compare two elements to determine their relative priority.
	 * A zero result indicates one and two have same priority.
	 * A negative result means two is higher priority than one.
	 * A positive result means one is higher priority than two.
	 */
	typedef int (*cmpFn)(ElemType one, ElemType two);
	
	/*
	 * Constructor: PQueue
	 * Usage: queue = new PQueue<string>(CmpByLength);
	 * -----------------------------------------------
	 * Initializes a new PQueue to have no elements. 
	 * The one argument is a comparison function, which is called
	 * to compare items to determine relative priority.  This 
	 * argument is optional, if not  given, the DefaultCmp function 
	 * from cmpfn.h is used, which applies the built-in operator < 
	 * to its operands. If the behavior of < on your ElemType is 
	 * defined and appropriate, you do not need to supply your own 
	 * comparison function. Otherwise, your callback should take
	 * two items and return 0/neg/pos to show the prioritized ordering
	 * between the two.
	 */
	PQueue(cmpFn cmp = DefaultCmp);


	/*
	 * Destructor: ~PQueue
	 * Usage: delete queue;
	 * --------------------
	 * Frees all the storage associated with the PQueue.
	 */
	~PQueue();


	/*
	 * Member function: IsEmpty
	 * Usage: if (queue->IsEmpty()) . . .
	 * ----------------------------------
	 * Returns true if PQueue has no entries.
	 */
	bool IsEmpty();


	/*
	 * Member function: IsFull
	 * Usage: if (queue->IsFull()) . . .
	 * ---------------------------------
	 * Returns true if PQueue has no more room for entries.  Clients can use
	 * this to check if any further Enqueue operation will overflow the
	 * ability of the PQueue to handle it. Some versions of the PQueue may 
	 * always return false if they can always accommodate more entries.
	 */
	bool IsFull();


	/*
	 * Member function: Enqueue
	 * Usage: queue->Enqueue(newElem);
	 * -------------------------------
	 * Adds the specified element to the PQueue. No effort is made to
	 * avoid duplicates.  If the PQueue is full, this function raises an error.
	 */
	void Enqueue(ElemType newElem);


	/*
	 * Member function: DequeueMax
	 * Usage: maxElem = queue->DequeueMax();
	 * -------------------------------------
	 * Removes the largest priority element from the PQueue and returns it.
	 * If the PQueue is empty, this function raises an error.
	 */
	ElemType DequeueMax();


  private:
  
 	ElemType *elements;
	unsigned int numUsed, numAllocated;
	cmpFn cmp;
	
	int MaxElement(int);
	void Heapify(int);
};

#include "pqueue.cpp"

#endif