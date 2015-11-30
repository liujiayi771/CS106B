#include <iostream>

using namespace std;

struct pNode {
    int value;
    pNode * next;
};

void Stutter(pNode * & head);

int main()
{
    pNode * head = new pNode;
    head->value = 11;
    pNode * temp1 = new pNode;
    temp1->value = 5;
    head->next = temp1;
    pNode * temp2 = new pNode;
    temp2->value = 21;
    temp1->next = temp2;
    pNode * temp3 = new pNode;
    temp3->value = 7;
    temp2->next = temp3;
    pNode * temp4 = new pNode;
    temp4->value = 7;
    temp4->next = NULL;
    temp3->next = temp4;
    cout << "Before stutter: ";
    for(pNode * pnode = head; pnode != NULL; pnode = pnode->next) {
        cout << pnode->value << " ";
    }
    cout << endl << "After stutter: ";
    Stutter(head);
    for(pNode * pnode = head; pnode != NULL; pnode = pnode->next) {
        cout << pnode->value << " ";
    }
    return 0;
}

void Stutter(pNode * & head)
{
    pNode * prev = head;
    pNode * pnode = head->next;
    for( ; pnode != NULL; pnode = pnode->next) {
        pNode * newNode = new pNode;
        newNode->value = prev->value;
        prev->next = newNode;
        newNode->next = pnode;
        prev = pnode;
    }
    pNode * last = new pNode;
    last->value = prev->value;
    prev->next = last;
    last->next = NULL;
}
