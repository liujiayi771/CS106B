/*
 * File: stack.h
 * -------------
 * This interface defines a stack template class.  The
 * client specializes the stack as needed to hold values of
 * different types by committing on the element type that
 * is left as placeholder.
 */

#ifndef _stack_h
#define _stack_h


/*
 * Class: Stack
 * ------------
 * A stack stores a linear collection of client-supplied
 * values that are stored and retrieved using Push and Pop
 * operations. Because the class is defined with private
 * data members, clients have no access to the underlying
 * fields and can only manipulate a stack object through
 * its public member functions.
 */
 
template <typename ElementType>
class Stack {

 public:
	/*
	 * Constructor
	 * Usage: Stack<int> *stack = new Stack<int>();
	 * --------------------------------------------
	 * The constructor initializes a new stack, which is
	 * initially empty.
	 */

	Stack();

	/*
	 * Destructor
	 * Usage: delete stack;
	 * --------------------
	 * The destructor frees the storage associated with the stack.
	 */

	~Stack();

	/*
	 * Member function: Push
	 * Usage: stack->Push(element);
	 * ----------------------------
	 * This function pushes the specified element onto the stack.
	 */

	void Push(ElementType element);
	
	/*
	 * Member function: Pop
	 * Usage: element = stack->Pop();
	 * ------------------------------
	 * This function pops the top element from the stack and returns
	 * that value.  The first value popped is always the last one
	 * that was pushed.  If the stack is empty when Pop is called,
	 * the function calls Error with an appropriate message.
	 */

	ElementType Pop();

	/*
	 * Member functions: IsEmpty, IsFull
	 * Usage: if (stack->IsEmpty()) . . .
	 *        if (stack->IsFull()) . . .
	 * ----------------------------------
	 * This functions test whether the stack is empty or full.
	 */

	bool IsEmpty();
	bool IsFull();

	/*
	 * Member function: Depth
	 * Usage: depth = stack->Depth();
	 * ------------------------------
	 * This function returns the number of elements currently pushed
	 * on the stack.
	 */

	int Depth();

	/*
	 * Member function: ElementAt
	 * Usage: element = stack->ElementAt(index);
	 * -----------------------------------------
	 * This function returns the element at the specified index in
	 * the stack, where the top of the stack is defined as index 0.
	 * For example, calling stack->ElementAt(0) returns the top
	 * element on the stack without removing it.  If the caller tries
	 * to select an out-of-range element, ElementAt calls Error.
	 * Note: This function is not a fundamental stack operation and
	 * is instead provided principally to facilitate debugging.
	 */

	ElementType ElementAt(int index);
	
	/*
	 * Member function: Copy
	 * Usage: stack2 = stack1->Copy();
	 * -------------------------------
	 * This function returns a new stack of the same base type as the
	 * receiver that contains the same elements in the same order.  
	 * Note: This function is not a fundamental stack operation and
	 * is instead provided principally for convenience.
	 */

	Stack *Copy();
	

  private: 
    struct cellT {
        ElementType element;
        cellT *link;
    };
	cellT *start;
};

#include "stack.cpp"

#endif

