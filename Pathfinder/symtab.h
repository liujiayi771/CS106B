/*
 * File: symtab.h
 * --------------
 * This interface exports a simple symbol table class template.
 */

#ifndef _symtab_h
#define _symtab_h

#include <string>
#include "iterator.h"
#include "genlib.h"

/*
 * Class: Symtab
 * -------------
 * This class used to represent a symbol table.
 */

template <typename ValueType>
class Symtab {

  public:

	/*
	 * Constructor: Symtab
	 * Usage: table = new Symtab<double>();
	 * ------------------------------------
	 * The constructor allocates a new symbol table with no entries.
	 */

	Symtab();

	/*
	 * Destructor: ~Symtab
	 * Usage: delete table;
	 * --------------------
	 * The destructor frees the storage associated with the 
	 * symbol table.
	 */

	~Symtab();

	/*
	 * Member function: NumEntries
	 * Usage: table->NumEntries();
	 * ---------------------------
	 * This function returns the number of entries in the table.
	 */

	int NumEntries();

	/*
	 * Member function: Enter
	 * Usage: table->Enter(key, value);
	 * --------------------------------
	 * This function associates key with value in the symbol table.
	 * Each call to Enter supersedes any previous definition for key.
	 */

	void Enter(string key, ValueType value);

	 /*
	 * Function: Lookup
	 * Usage: if (table->Lookup(key, value))...
	 * ----------------------------------------
	 * If key is found in the symbol table, this function returns true 
	 * and assigns the reference parameter the associated value.  If 
	 * key is not found, the function returns false and the reference
	 * parameter is not assigned.
	 */

	bool Lookup(string key, ValueType & value);


	/*
	 * Type: mapFnT
	 * ------------
	 * This type defines the prototype of functions that can be used
	 * to map over the entries in a symbol table.
	 */

	typedef void (*mapFnT)(string key, ValueType value);

	/*
	 * Member function: MapEntries
	 * Usage: table->MapEntries(fn);
	 * -----------------------------
	 * This function goes through every entry in the symbol table
	 * and calls the function fn, passing it the following arguments:
	 * the current key and its associated value.
	 */

	void MapEntries(mapFnT fn);

	/*
	 * Member function: CreateIterator
	 * Usage: iter = table->CreateIterator();
	 * --------------------------------------
	 * This function creates a new Iterator containing the keys
	 * from the symbol table.
	 */

	Iterator<string> *CreateIterator();

  private:

  #define NBuckets 101

	  struct cellT {
	    string key;
	    ValueType value;
	    cellT *link;
	  };

	  cellT *buckets[NBuckets];
	  int numEntries;

	  void FreeBucketChain(cellT *cp);
	  cellT *FindCell(cellT *cp, string s);
	  int Hash(string s, int numBuckets);

};

#include "symtab.cpp"

#endif

