#include <iostream>
#include <stack>
#include <queue>

using namespace std;

void ReverseQueue(queue<int> &q);

int main()
{
    queue<int> q;
    queue<int> temp;
    for(int i = 0; i < 10; i++)
    {
        q.push(i);
    }
    temp = q;
    cout << "the origin order is: ";
    for(int i = temp.size(); i > 0; i--)
    {
        if(i == 1)
            cout << temp.front();

        else
            cout << temp.front() << ",";
        temp.pop();
    }
    cout << endl;
    ReverseQueue(q);
    cout << "the change order is: ";
    for(int i = q.size(); i > 0; i--)
    {
        if(i == 1)
            cout << q.front();
        else
            cout << q.front() << ",";
        q.pop();
    }
    cout << endl;
    return 0;
}

void ReverseQueue(queue<int> &q)
{
    stack<int> s;
    while(!q.empty())
    {
        s.push(q.front());
        q.pop();
    }
    while(!s.empty())
    {
        q.push(s.top());
        s.pop();
    }
}
