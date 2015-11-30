#include <iostream>
#include "set.h"

using namespace std;

struct pairT
{
        string first, second;
};

Set<pairT> CartesianProduct(Set<string> & one, Set<string> & two);
int PairCmpFn(pairT a, pairT b);

int main()
{
        Set<string> one, two;
        Set<pairT> cartesianProduct(PairCmpFn);
        one.add("A");
        one.add("B");
        one.add("C");
        two.add("X");
        two.add("Y");
        cartesianProduct = CartesianProduct(one, two);
        Set<pairT>::Iterator it = cartesianProduct.iterator();
        while(it.hasNext())
        {
                pairT temp = it.next();
                cout << "(" << temp.first << ", " << temp.second << ")" << endl;
        }
        return 0;
}

Set<pairT> CartesianProduct(Set<string> & one, Set<string> & two)
{
        Set<pairT> result;
        Set<string>::Iterator itOne = one.iterator();
        Set<string>::Iterator itTwo = two.iterator();
        while(itOne.hasNext())
        {
                string tempOne = itOne.next();
                while(itTwo.hasNext())
                {
                        string tempTwo = itTwo.next();
                        pairT temp;
                        temp.first = tempOne;
                        temp.second = tempTwo;
                        result.add(temp);
                }
        }
        return result;
}

int PairCmpFn(pairT one, pairT two)
{
        if (one.first == two.first && one.second == two.second)
        {
                return 0;
        }
        else if (one.first < two.first)
        {
                return -1;
        }
        else if (one.first == two.first && one.second < two.second)
        {
                return -1;
        }
        else
        {
                return 1;
        }
}
