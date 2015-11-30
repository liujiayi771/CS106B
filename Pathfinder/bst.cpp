/*
 * File: bst.cpp
 * --------------
 * This file implements the bst.h interface, which provides a
 * general implementation of binary search trees.
 */

#include "bst.h"


template <typename DataType>
BST<DataType>::BST(cmpFnT clientFn)
{
    root = NULL;
    cmpFn = clientFn;
}

template <typename DataType>
BST<DataType>::~BST()
{
    RecFreeTree(root);
}

template <typename DataType>
void BST<DataType>::RecFreeTree(treeT t)
{
    if (t != NULL) {
		RecFreeTree(t->left);
		RecFreeTree(t->right);
		delete t;
  	}	
}

/*
 * Implementation notes: Find, RecFindNode
 * ----------------------------------------------
 * The Find function simply calls RecFindNode to do
 * the work.  The recursive function takes the current
 * node along with the original argument. If found, 
 * it overwrites the reference parameter with the copy
 * of returns a pointer to the data.
 */

template <typename DataType>
DataType *BST<DataType>::Find(DataType key)
{
    treeT found = RecFindNode(root, key);
    if (found != NULL) {
    	   return (&found->data);
    }
    return (NULL);
}

template <typename DataType>
typename BST<DataType>::treeT BST<DataType>::RecFindNode(treeT t, 
                                                       DataType & key)
{
    int sign;

    if (t == NULL) return (NULL);
    sign = cmpFn(key, t->data);
    if (sign == 0) return (t);
    if (sign < 0) {
        return (RecFindNode(t->left, key));
    } else {
        return (RecFindNode(t->right, key));
    }
}

/*
 * Implementation notes: Insert, RecInsertNode
 * -------------------------------------------
 * The Insert function is implemented as a simple wrapper
 * to RecInsertNode, which does all the work.  The difference
 * between the prototypes is that RecInsertNode takes a reference
 * to the root of the current subtree as an extra argument.
 * For reasons of efficiency (we don't know how large DataType
 * might be), we pass it by reference.
 */

template <typename DataType>
bool BST<DataType>::Insert(DataType data)
{
    bool createdNewNode;
    RecInsertNode(root, data, createdNewNode);
    return createdNewNode;
}

template <typename DataType>
int BST<DataType>::RecInsertNode(treeT & t, DataType & data, bool &createdNewNode)
{
    int delta;

    if (t == NULL) {
        t = new nodeT;
        t->data = data;
        t->bf = 0;
        t->left = t->right = NULL;
        createdNewNode = true;
        return (+1);
    }
    int sign = cmpFn(data, t->data);
    if (sign == 0) {
    	t->data = data;
    	createdNewNode = false;
    	return (0);
	}
    if (sign < 0) {
        delta = RecInsertNode(t->left, data, createdNewNode);
        if (delta == 0) return (0);
        switch (t->bf) {
          case +1: t->bf =  0; return (0);
          case  0: t->bf = -1; return (+1);
          case -1: FixLeftImbalance(t); return (0);
        }
    } else {
        delta = RecInsertNode(t->right, data, createdNewNode);
        if (delta == 0) return (0);
        switch (t->bf) {
          case -1: t->bf =  0; return (0);
          case  0: t->bf = +1; return (+1);
          case +1: FixRightImbalance(t); return (0);
        }
    }
    return 0; // never gets here
}


/*
 * Function: FixLeftImbalance
 * Usage: FixLeftImbalance(t);
 * ---------------------------
 * This function is called when a node has been found that
 * is out of balance with the longer subtree on the left.
 * Depending on the balance factor of the left child, the
 * code performs a single or double rotation.
 */

template <typename DataType>
void BST<DataType>::FixLeftImbalance(treeT & t)
{
    treeT child;
    int oldBF;

    child = t->left;
    if (child->bf != t->bf) {
        oldBF = child->right->bf;
        RotateLeft(t->left);
        RotateRight(t);
        t->bf = 0;
        switch (oldBF) {
          case -1: t->left->bf = 0; t->right->bf = +1; break;
          case  0: t->left->bf = t->right->bf = 0; break;
          case +1: t->left->bf = -1; t->right->bf = 0; break;
        }
    } else {
        RotateRight(t);
        t->right->bf = t->bf = 0;
    }
}

/*
 * Function: RotateLeft
 * Usage: RotateLeft(t);
 * ---------------------
 * This function performs a single left rotation of the tree
 * that is passed by reference.  The balance factors
 * are unchanged by this function and must be corrected at a
 * higher level of the algorithm.
 */

template <typename DataType>
void BST<DataType>::RotateLeft(treeT & t)
{
    treeT child;

    child = t->right;
    t->right = child->left;
    child->left = t;
    t = child;
}


/*
 * Function: FixRightImbalance
 * Usage: FixRightImbalance(t);
 * ---------------------------
 * This function is called when a node has been found that
 * is out of balance with the longer subtree on the right.
 * Depending on the balance factor of the right child, the
 * code performs a single or double rotation.
 */


template <typename DataType>
void BST<DataType>::FixRightImbalance(treeT & t)
{
    treeT child;
    int oldBF;

    child = t->right;
    if (child->bf != t->bf) {
        oldBF = child->left->bf;
        RotateRight(t->right);
        RotateLeft(t);
        t->bf = 0;
        switch (oldBF) {
          case -1: t->right->bf = 0; t->left->bf = +1; break;
          case  0: t->right->bf = t->left->bf = 0; break;
          case +1: t->right->bf = -1; t->left->bf = 0; break;
        }
    } else {
        RotateLeft(t);
        t->left->bf = t->bf = 0;
    }
}

/*
 * Function: RotateRight
 * Usage: RotateRight(t);
 * ----------------------
 * This function performs a single right rotation of the tree
 * that is passed by reference.  The balance factors
 * are unchanged by this function and must be corrected at a
 * higher level of the algorithm.
 */

template <typename DataType>
void BST<DataType>::RotateRight(treeT & t)
{
    treeT child;

    child = t->left;
    t->left = child->right;
    child->right = t;
    t = child;
}



 /*
 * Implementation notes: Remove, RecRemoveNode
 * -------------------------------------------
 * The first step in removing a node is to find it using binary
 * search, which is performed by these two functions.  If the
 * node is found, RemoveTargetNode does the actual deletion.
 */

template <typename DataType>
bool BST<DataType>::Remove(DataType data)
{
    return (RecRemoveNode(root, data));
}

template <typename DataType>
bool BST<DataType>::RecRemoveNode(treeT & t, DataType & data)
{
    int sign;

    if (t == NULL) return (false);
    sign = cmpFn(data, t->data);
    if (sign == 0) {
        RemoveTargetNode(t);
        return (true);
    } else if (sign < 0) {
        return (RecRemoveNode(t->left, data));
    } else {
	     return (RecRemoveNode(t->right, data));
    }
}

/*
 * Implementation notes: RemoveTargetNode
 * --------------------------------------
 * This function removes the node which is passed by
 * reference as t.  The easy case occurs when either of the
 * children is NULL; all you need to do is replace the node with
 * its non-NULL child.  If both children are non-NULL, this code
 * finds the rightmost descendent of the left child; this node
 * may not be a leaf, but will have no right child.  Its left
 * child replaces it in the tree, after which the replacement
 * node is moved to the position occupied by the target node.
 */

 template <typename DataType>
void BST<DataType>::RemoveTargetNode(treeT  & t)
{
    treeT toDelete = t;

    if (t->left == NULL) {
        t = t->right;
    } else if (t->right == NULL) {
        t = t->left;
    } else {
        treeT newRoot = t->left, parent = t;

        while (newRoot->right != NULL) {
            parent = newRoot;
            newRoot = newRoot->right;
        }
        if (parent != t) {
           parent->right = newRoot->left;
           newRoot->left = t->left;
    	    }
    	    newRoot->right = t->right;
        t = newRoot;
    }
    delete toDelete;
}
 
/*
 * Implementation notes: CreateIterator, RecAddToIterator
 * ------------------------------------------------------
 * The CreateIterator function is implemented as a wrapper to the
 * recursive function RecAddToIterator, which does the actual work
 * of adding all the values to the iterator during an InOrder walk.
 */

template <typename DataType>
Iterator<DataType> *BST<DataType>::CreateIterator()
{
    Iterator<DataType> *iterator = new Iterator<DataType>;
    RecAddToIterator(iterator, root);
    return (iterator);
}

template <typename DataType>
void BST<DataType>::RecAddToIterator(Iterator<DataType> * iter, 
                                     treeT t)
{
    if (t != NULL) {
        RecAddToIterator(iter, t->left);
        iter->AddElement(t->data);
        RecAddToIterator(iter, t->right);
    }
}

