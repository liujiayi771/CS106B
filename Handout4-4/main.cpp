#include <iostream>
#include "vector.h"

using namespace std;

struct Cell {
    Cell * next;
    int value;
};

Cell * ConvertToList_Iterative(Vector<int> input);
Cell * ConvertToList_Recursive(Vector<int> input, int index);
int SumList_Iterative(Cell *list);
int SumList_Recursive(Cell *list);

int main()
{
    Vector<int> data;
    for(int i = 0; i < 10; i++) {
        data.add(i);
    }
    cout << "Vector value: ";
    for(int i = 0; i < data.size(); i++) {
        cout << data[i] << " ";
    }
    cout << endl;
    Cell * list1 = ConvertToList_Iterative(data);
    cout << "Link list value(iterative): ";
    for(Cell * pNode = list1->next; pNode != NULL; pNode = pNode->next) {
        cout << pNode->value << " ";
    }
    cout << endl;
    Cell * list2 = ConvertToList_Recursive(data, 0);
    cout << "Link list value(Recursive): ";
    for(Cell * pNode = list2; pNode != NULL; pNode = pNode->next) {
        cout << pNode->value << " ";
    }
    cout << endl;
    cout << "Sum of link list(Iterative): ";
    cout << SumList_Iterative(list2);
    cout << endl;
    cout << "Sum of link list(Recursive): ";
    cout << SumList_Recursive(list2);
    cout << endl;
    return 0;
}

Cell * ConvertToList_Iterative(Vector<int> input)
{
    Cell * head = new Cell;
    Cell * temp = head;
    for(int i = 0; i < input.size(); i++) {
        Cell * pNode = new Cell;
        pNode->value = input[i];
        pNode->next = NULL;
        temp->next = pNode;
        temp = pNode;
    }
    return head;
}

Cell * ConvertToList_Recursive(Vector<int> input, int index)
{
    if(index >= input.size()) {
        return NULL;
    }
    Cell * pNode = new Cell;
    pNode->value = input[index];
    pNode->next = ConvertToList_Recursive(input, index + 1);
    return pNode;
}

int SumList_Iterative(Cell *list)
{
    int sum = 0;
    for(Cell * pNode = list; pNode != NULL; pNode = pNode->next) {
        sum += pNode->value;
    }
    return sum;
}

int SumList_Recursive(Cell *list)
{
    if(list == NULL) {
        return 0;
    } else {
        return list->value + SumList_Recursive(list->next);
    }
}
