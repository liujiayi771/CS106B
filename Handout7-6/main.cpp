#include <iostream>

using namespace std;

struct pNode {
    int value;
    pNode * next;
};

void RemoveDuplicates(pNode * & head);

int main()
{
    pNode * head = new pNode;
    head->value = 5;
    pNode * temp1 = new pNode;
    temp1->value = 5;
    head->next = temp1;
    pNode * temp2 = new pNode;
    temp2->value = 22;
    temp1->next = temp2;
    pNode * temp3 = new pNode;
    temp3->value = 37;
    temp2->next = temp3;
    pNode * temp4 = new pNode;
    temp4->value = 89;
    temp3->next = temp4;
    pNode * temp5 = new pNode;
    temp5->value = 89;
    temp4->next = temp5;
    pNode * temp6 = new pNode;
    temp6->value = 15;
    temp5->next = temp6;
    pNode * temp7 = new pNode;
    temp7->value = 15;
    temp6->next = temp7;
    pNode * temp8 = new pNode;
    temp8->value = 22;
    temp7->next = temp8;
    temp8->next = NULL;
    cout << "Before stutter: ";
    for(pNode * pnode = head; pnode != NULL; pnode = pnode->next) {
        cout << pnode->value << " ";
    }
    cout << endl << "After stutter: ";
    RemoveDuplicates(head);
    for(pNode * pnode = head; pnode != NULL; pnode = pnode->next) {
        cout << pnode->value << " ";
    }
    return 0;
}

void RemoveDuplicates(pNode * & head)
{
    pNode * prev = head;
    pNode * pnode = head->next;
    for( ; pnode != NULL; pnode = pnode->next) {
        if(prev->value == pnode->value) {
            prev->next = pnode->next;
            delete pnode;
        }
        prev = pnode;
    }
}
