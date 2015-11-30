#include <iostream>
#include "random.h"

using namespace std;

struct pNode {
    int value;
    pNode * next;
};

pNode * appendLinkList(pNode * one, pNode * two);

int main()
{
    Randomize();
    pNode * headOne = new pNode;
    pNode * headTwo = new pNode;
    pNode * temp = headOne;
    for(int i = 0; i < 5; i++) {
        pNode * newNode = new pNode;
        newNode->value = RandomInteger(0,30);
        temp->next = newNode;
        temp = newNode;
    }
    temp = headTwo;
    for(int i = 0; i < 5; i++) {
        pNode * newNode = new pNode;
        newNode->value = RandomInteger(0,30);
        temp->next = newNode;
        temp = newNode;
    }
    cout << "Link list one: ";
    for(pNode * pnode = headOne->next; pnode != NULL; pnode = pnode->next) {
        cout << pnode->value << " ";
    }
    cout << endl << "Link list two: ";
    for(pNode * pnode = headTwo->next; pnode != NULL; pnode = pnode->next) {
        cout << pnode->value << " ";
    }
    pNode * append = appendLinkList(headOne, headTwo);
    cout << endl << "After append two link list: ";
    for(pNode * pnode = append->next; pnode != NULL; pnode = pnode->next) {
        cout << pnode->value << " ";
    }
    cout << endl;
    return 0;
}

pNode * appendLinkList(pNode * one, pNode * two)
{
    pNode * pnode = one;
    while(pnode->next != NULL) {
        pnode = pnode->next;
    }
    pnode->next = two->next;
    return one;
}
