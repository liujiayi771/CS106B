#include <iostream>
#include "simpio.h"
#include "vector.h"
#include "genlib.h"
#include "strutils.h"
#include "cmpfn.h"
#include "random.h"

using namespace std;

template <typename Type>
bool lessThan(int i, int j, Vector<Type> & v, int (cmpFn)(Type, Type))
{
        return cmpFn(v[i - 1] , v[j - 1]) < 0;
}

template <typename Type>
void exchange(Vector<Type> & v, int i, int j)
{
        Type t = v[i - 1];
        v[i - 1] = v[j - 1];
        v[j - 1] = t;
}

template <typename Type>
void sink(Vector<Type> &v, int (cmpFn)(Type one, Type two), int k, int N )
{
	while (2 * k <= N) 
	{
		int j = 2 * k;
		if (j < N && lessThan(j, j + 1, v, cmpFn)) 
			j ++;
		if (!lessThan(k, j, v, cmpFn)) 
			break;
		exchange(v, k, j);
		k = j;
	}
}

template <typename Type>
void Sort(Vector<Type> & v, int (cmpFn)(Type, Type) = OperatorCmp )
{
	int N = v.size();
	for (int k = N / 2; k >= 1; k --)
        {
		sink(v, cmpFn, k, N);
	}

	while (N > 1)
	{
		exchange(v, 1, N--);
		sink(v, cmpFn, 1, N );
	}
}

int main()
{
        Vector<int> testv;

	for (int i = 0; i < 10000; i++ ) 
	{
		int r = RandomInteger(0,1000);
		testv.add(r);
	}

	double start = double (clock()) / CLOCKS_PER_SEC;

	Sort(testv);

	double finish = double (clock()) / CLOCKS_PER_SEC;

	double elapsed = finish - start;

	cout << "Heap Sort takes: " << RealToString(elapsed) << " seconds. " << endl;

        return 0;
}
