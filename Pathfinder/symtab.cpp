/*
 * File: symtab.cpp
 * ----------------
 * This file implements the symbol table abstraction
 * using a hashtable implementation. This provides for
 * zippy O(1) performance on enter and lookup operations.
 */

#include "symtab.h"

/*
 * Class: Symtab
 * -------------
 * In this implementation, the underlying organization of the
 * data is a hash table organized as an array of "buckets",
 * in which each bucket is a linked list of elements
 * that share the same hash code.
 */

/* Public member functions */

template <typename ValueType>
Symtab<ValueType>::Symtab()
{
    for (int i = 0; i < NBuckets; i++) {
        buckets[i] = NULL;
    }
    numEntries = 0;
}

template <typename ValueType>
Symtab<ValueType>::~Symtab()
{
    for (int i = 0; i < NBuckets; i++) {
        FreeBucketChain(buckets[i]);
    }
}

template <typename ValueType>
int Symtab<ValueType>::NumEntries()
{
    return (numEntries);
}

template <typename ValueType>
void Symtab<ValueType>::Enter(string key, ValueType value)
{
    int bucket;
    cellT *cp;

    bucket = Hash(key, NBuckets);
    cp = FindCell(buckets[bucket], key);
    if (cp == NULL) {
        cp = new cellT;
        cp->key = key;
        cp->link = buckets[bucket];
        buckets[bucket] = cp;
        numEntries++;
    }
    cp->value = value;
}

 template <typename ValueType>
bool Symtab<ValueType>::Lookup(string key, ValueType & value)
{
    int bucket;
    cellT *cp;

    bucket = Hash(key, NBuckets);
    cp = FindCell(buckets[bucket], key);
    if (cp == NULL) return (false);
    value = cp->value;
    return (true);
}

/* Private member functions */


/*
 * Private member function: FreeBucketChain
 * Usage: FreeBucketChain(cp);
 * ---------------------------
 * This function takes a chain pointer and frees all the cells
 * in that chain.
 */

template <typename ValueType>
void Symtab<ValueType>::FreeBucketChain(cellT *cp)
{
    cellT *next;

    while (cp != NULL) {
        next = cp->link;
        delete cp;
        cp = next;
    }
}

/*
 * Private member function: FindCell
 * Usage: cp = FindCell(cp, key);
 * ------------------------------
 * This function finds a cell in the chain beginning at cp that
 * matches key.  If a match is found, a pointer to that cell is
 * returned.  If no match is found, the function returns NULL.
 */

template <typename ValueType>
typename Symtab<ValueType>::cellT 
         *Symtab<ValueType>::FindCell(cellT *cp, string key)
{
    while (cp != NULL && key != cp->key) {
        cp = cp->link;
    }
    return (cp);
}

 /*
 * Private member function: Hash
 * Usage: bucket = Hash(key, nBuckets);
 * ------------------------------------
 * This function takes the key and uses it to derive a hash code,
 * which is an integer in the range [0, nBuckets - 1].  The hash
 * code is computed using a method called linear congruence.
 */

#define Multiplier -1664117991L

template <typename ValueType>
int Symtab<ValueType>::Hash(string s, int nBuckets)
{
    unsigned long hashcode;

    hashcode = 0;
    for (int i = 0; i < s.length(); i++) {
        hashcode = hashcode * Multiplier + s[i];
    }
    return (hashcode % nBuckets);
}

template <typename ValueType>
void Symtab<ValueType>::MapEntries(mapFnT fn)
{
    for (int i = 0; i < NBuckets; i++) {
        for (cellT *cp = buckets[i]; cp != NULL; cp = cp->link) {
            fn(cp->key, cp->value);
        }
    }
}

template <typename ValueType>
Iterator<string> *Symtab<ValueType>::CreateIterator()
{
    Iterator<string> *iter = new Iterator<string>;

    for (int i = 0; i < NBuckets; i++) {
        for (cellT *cp = buckets[i]; cp != NULL; cp = cp->link) {
            iter->AddElement(cp->key);
        }
    }
    return (iter);
}
