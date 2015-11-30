#include <iostream>
#include "stack.h"

const int CURSOR_BEGIN = 23;
using namespace std;

struct cellT {
    char character;
    cellT * next  = NULL;
};

void moveToWordBegin_array(const char * text, int & cursor);
void moveToWordBegin_stack(Stack<char> & before, Stack<char> & after);
void moveToWordBegin_singly_link_list(cellT * head, int & cursor);

int main()
{
    string str = "The quick brown fox jumped over the lazy";
    const char * text = str.c_str();
    Stack<char> before;
    Stack<char> after;
    cellT * head = new cellT;
    cellT * temp = head;
    int counter = 0;
    for(int i = 0; i <str.size(); i++) {
        cellT * newCell = new cellT;
        newCell->character = str[i];
        temp->next = newCell;
        temp = newCell;
    }
    int cursor = CURSOR_BEGIN;
    moveToWordBegin_array(text, cursor);
    cout << "Test for array implementation: " << cursor << endl;
    for(int i = 0; i < CURSOR_BEGIN; i++) {
        before.push(str[i]);
    }
    for(int i = CURSOR_BEGIN; i < str.size(); i++) {
        after.push(str[i]);
    }
    moveToWordBegin_stack(before, after);
    cout << "Test for stack implementation: " << before.size() << endl;
    cursor = CURSOR_BEGIN;
    moveToWordBegin_singly_link_list(head, cursor);
    cout << "Test for singly link list implementation: " << cursor << endl;
    return 0;
}

void moveToWordBegin_array(const char * text, int & cursor)
{
    while(cursor - 1 >= 0 && text[cursor - 1] == ' ') {
        cursor --;
    }
    while(cursor - 1 >= 0 && text[cursor - 1] != ' ') {
        cursor --;
    }
}

void moveToWordBegin_stack(Stack<char> & before, Stack<char> & after)
{
    while(!before.isEmpty() && before.peek() == ' ') {
        after.push(before.pop());
    }
    while(!before.isEmpty() && before.peek() != ' ') {
        after.push(before.pop());
    }
}

void moveToWordBegin_singly_link_list(cellT * head, int & cursor)
{
    cellT * pNode = head->next;
    cellT * prev = head->next;
    for(int i = 0; i < cursor - 1; i++) {
        prev = pNode;
        pNode = pNode->next;
    }
    char temp = pNode->character;
    while(temp == ' ') {
        cursor --;
        pNode = head->next;
        prev = head->next;
        for(int i = 0; i < cursor - 1; i++) {
            prev = pNode;
            pNode = pNode->next;
        }
        temp = pNode->character;
    }
    while(temp != ' ') {
        cursor --;
        pNode = head->next;
        prev = head->next;
        for(int i = 0; i < cursor - 1; i++) {
            prev = pNode;
            pNode = pNode->next;
        }
        temp = pNode->character;
    }

}
