#include <iostream>
#include "queue.h"

using namespace std;

struct recordingT {
    string title;
    string genre;
    int rating;
};

template <typename Type>
void Filter(Queue<Type> & record, bool (judgeFn)(Type show));

bool IsBadAnimation(recordingT show)
{
    return (show.genre == "animation" && show.rating < 8);
}

int main()
{
    recordingT one, two, three, four, five;
    one.genre = "abcd";one.rating = 7;one.title = "cdef";
    two.genre = "animation";two.rating = 8;two.title = "uidf";
    three.genre = "animation";three.rating = 5;three.title = "asdf";
    four.genre = "type";four.rating = 9;four.title = "adqwr";
    five.genre = "gghy";five.rating = 3;five.title = "tyuqwe";
    Queue<recordingT> data;
    data.enqueue(one);data.enqueue(two);data.enqueue(three);
    data.enqueue(four);data.enqueue(five);
    Queue<recordingT> copy = data;
    cout << "Before filter: " << endl;
    while(!copy.isEmpty()) {
        recordingT temp = copy.dequeue();
        cout << "genre: " << temp.genre << " title: " << temp.title << " rating: " << temp.rating << endl;
    }
    Filter(data, IsBadAnimation);
    cout << endl;
    cout << "After filter: " << endl;
    while(!data.isEmpty()) {
        recordingT temp = data.dequeue();
        cout << "genre: " << temp.genre << " title: " << temp.title << " rating: " << temp.rating << endl;
    }
    return 0;
}

template <typename Type>
void Filter(Queue<Type> & record, bool (judgeFn)(Type show))
{
    Queue<recordingT> newRecord;
    while(!record.isEmpty()) {
        recordingT temp = record.dequeue();
        if(!judgeFn(temp)) {
            newRecord.enqueue(temp);
        }
    }
    while(!newRecord.isEmpty()) {
        record.enqueue(newRecord.dequeue());
    }
}
