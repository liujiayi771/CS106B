/*
 * File: cmpfn.h
 * --------------
 * This interface exports a comparison function template.
 */

#ifndef _cmpfn_h
#define _cmpfn_h

/*
/*
/* Function template: DefaultCmp
 * Usage:  int sign = DefaultCmp(val1, val2);
 * ------------------------------------------
 * This function template is a generic function to
 * compare two values using the built-in == and < operators.
 * It is supplied as a convenience for those situations
 * where a comparison function is required, but the type
 * has a built-in ordering that you would like to use.
 */

template <typename Type>
int DefaultCmp(Type one, Type two)
{
    if (one == two) return 0;
    else if (one < two) return -1;
    else return 1; 
}

#endif
