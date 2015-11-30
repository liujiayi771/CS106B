/*
 * File: bst.h
 * -----------
 * This file provides an interface for a general binary search
 * tree class template.
 */

#ifndef _bst_h
#define _bst_h

#include "cmpfn.h"
#include "iterator.h"

/*
 * Class: BST
 * ----------
 * This is the class template for a binary search tree.
 */

template <typename DataType>
class BST {

  public:

/* Type: cmpFnT
 * ------------
 * This typedef describes the signature of a comparison
 * function that takes two parameters of type DataTypes and
 * returns a negative, positive, or zero result to indicate
 * the appropriate ordering of the two values. 
 */
typedef int (*cmpFnT)(DataType one, DataType two);

/*
 * Constructor: BST
 * Usage: bst = new BST(CompareStudents);
 * --------------------------------------
 * This function initializes a new empty binary search tree.
 * The one argument is a comparison function, which is called
 * to compare data values.  This argument is optional, if not
 * given, the DefaultCmp function from cmpfn.h is used, which
 * applies the built-in operator < to its operands. If the
 * behavior of < on your DataType is defined and sufficient,
 * you do not need to supply your own comparison function.
 */

BST(cmpFnT clientCmpFn = DefaultCmp);

/*
 * Destructor: ~BST
 * Usage: delete bst;
 * ------------------
 * This function frees the storage for a tree.
 */

~BST();

/*
 * Member function: Find
 * Usage:  if (bst->Find(key) != NULL)...
 * ---------------------------------------
 * This function applies the binary search algorithm to find a
 * particular key in the tree represented by bst.  The second
 * argument is the key to use for comparison. If a node
 * matching the key appears in the tree, Find returns a
 * pointer to the data in that node; if not, Find returns
 * NULL.
 */

DataType *Find(DataType key);

/*
 * Member function: Insert
 * Usage: bst->Insert(data);
 * -------------------------
 * This function is used to insert a new node into a binary search
 * tree.  The data argument is compared with the data in existing 
 * nodes to find the proper position.   If a node with the same 
 * key already exists, the previous data contents are overwritten 
 * with the new value.  If no such key is not found, Insert 
 * allocates a new node and copies the data to it. The return
 * value is true if a new node was created, false otherwise.
 */

bool Insert(DataType data);

/*
 * Member function: Remove
 * Usage: bst->Remove(key);
 --------------------------
 * This function removes a node in the tree that matches the
 * specified key. If the key is not found in the tree, the tree 
 * is unchanged. The return value is true if a match was
 * found and removed, false otherwise.
 */

bool Remove(DataType key);

/*
 * Member function: CreateIterator
 * Usage: iter = bst->CreateIterator();
 * ------------------------------------
 * This function creates a new Iterator containing every data
 * value in the binary search tree.  The order of the values in
 * the iterator is determined by an InOrder walk of the tree.
 */

Iterator<DataType> *CreateIterator();

 
  private:

struct nodeT {
    DataType data;
    nodeT *left, *right;
    int bf;
};
typedef nodeT *treeT;

treeT root;
cmpFnT cmpFn;

/* Internal helper member functions, not accessible by client */

treeT RecFindNode(treeT t, DataType & key);
int RecInsertNode(treeT & t, DataType & key, bool &createdNewNode);
bool RecRemoveNode(treeT &, DataType & key);
void RemoveTargetNode(treeT & t);
void RecAddToIterator(Iterator<DataType> *iterator, treeT t);
void RecFreeTree(treeT t);
void FixRightImbalance(treeT &t);
void FixLeftImbalance(treeT &t);
void RotateRight(treeT &t);
void RotateLeft(treeT &t);

};

#include "bst.cpp"

#endif
