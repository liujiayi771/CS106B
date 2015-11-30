#include <iostream>
#include "chunklist.h"

using namespace std;

ChunkList::ChunkList(): header(nullptr)
{
}

ChunkList::~ChunkList()
{
        while(header != NULL)
        {
                ChunkList::LNode* tempNode = header->next;
                delete header;
                header = tempNode;
        }
}

ChunkList::LNode* ChunkList::getHeader()
{
        return header;
}

void ChunkList::add(int newElem)
{
        if(this->header == NULL)
        {
                this->header = new ChunkList::LNode;
                ChunkList::LNode* newNode = new ChunkList::LNode;
                this->header->next = newNode;
        }

//        if(!this->header->next->value.isEmpty() &&
//           newElem >= this->header->next->value[0] &&
//           this->header->next->value.size() == MaxElemsPerBlock)
//        {
//                ChunkList::LNode* newNode = new ChunkList::LNode;
//                for(int i = MaxElemsPerBlock / 2 - 1; i < this->header->next->value.size(); i++)
//                {
//                        newNode->value.add(this->header->next->value[i]);
//                        this->header->next->value.removeAt(i);
//                }
//                for(int i = 0; i < this->header->next->value.size(); i++)
//                {
//                        if(this->header->next->value[i] <= newElem)
//                        {
//                                this->header->next->value.insertAt(i, newElem);
//                                break;
//                        }
//                }
//                ChunkList::LNode* tempNode = this->header->next->next;
//                this->header->next->next = newNode;
//                newNode->next = tempNode;
//                return;
//        }
//
//        if(!this->header->next->value.isEmpty() &&
//           newElem >= this->header->next->value[0] &&
//           this->header->next->value.size() < MaxElemsPerBlock)
//        {
//                this->header->next->value.insertAt(0, newElem);
//                return;
//        }

        ChunkList::LNode* temp = this->header->next;
        while(temp != NULL)
        {
                if(temp->value.isEmpty())
                {
                        temp->value.add(newElem);
                        break;
                }

                if(!temp->value.isEmpty() &&
                   newElem >= temp->value[0] &&
                   temp->value.size() == MaxElemsPerBlock)
                {
                        ChunkList::LNode* newNode = new ChunkList::LNode;
                        for(int i = MaxElemsPerBlock / 2; i < MaxElemsPerBlock; i++)
                        {
                                newNode->value.add(temp->value[i]);
                        }
                        for(int i = MaxElemsPerBlock / 2; i < MaxElemsPerBlock; i++)
                        {
                                temp->value.removeAt(temp->value.size() - 1);
                        }
                        for(int i = 0; i < temp->value.size(); i++)
                        {
                                if(temp->value[i] <= newElem)
                                {
                                        temp->value.insertAt(i, newElem);
                                        break;
                                }
                        }
                        ChunkList::LNode* tempNode = temp->next;
                        temp->next = newNode;
                        newNode->next = tempNode;
                        break;
                }

                if(!temp->value.isEmpty() &&
                   newElem >= temp->value[0] &&
                   temp->value.size() < MaxElemsPerBlock)
                {
                        temp->value.insertAt(0, newElem);
                        break;
                }

                if(temp->next == NULL &&
                   temp->value.size() == MaxElemsPerBlock)
                {
                        ChunkList::LNode* nextNode = new ChunkList::LNode;
                        nextNode->value.add(newElem);
                        temp->next = nextNode;
                        break;
                }

                if(temp->next == NULL &&
                   temp->value.size() < MaxElemsPerBlock &&
                   newElem <= temp->value[temp->value.size() - 1])
                {
                        temp->value.add(newElem);
                        break;
                }

                if(temp->value.size() < MaxElemsPerBlock &&
                   temp->value[0] >= newElem &&
                   temp->value[temp->value.size() - 1] <= newElem)
                {
                        for(int i = 0; i < temp->value.size(); i++)
                        {
                                if(temp->value[i] <= newElem)
                                {
                                        temp->value.insertAt(i, newElem);
                                        break;
                                }
                        }
                        temp->value.add(newElem);
                        break;
                }

                if(temp->value.size() == MaxElemsPerBlock &&
                   temp->value[0] >= newElem &&
                   temp->value[temp->value.size() - 1] <= newElem)
                {
                        ChunkList::LNode* newNode = new ChunkList::LNode;
                        for(int i = MaxElemsPerBlock / 2; i < MaxElemsPerBlock; i++)
                        {
                                newNode->value.add(temp->value[i]);
                        }
                        for(int i = MaxElemsPerBlock / 2; i < MaxElemsPerBlock; i++)
                        {
                                temp->value.removeAt(temp->value.size() - 1);
                        }
                        for(int i = 0; i < temp->value.size(); i++)
                        {
                                if(temp->value[i] <= newElem)
                                {
                                        temp->value.insertAt(i, newElem);
                                        break;
                                }
                        }
                        ChunkList::LNode* tempNode = temp->next;
                        temp->next = newNode;
                        newNode->next = tempNode;
                        break;
                }
                temp = temp->next;
        }
}

void ChunkList::remove(int removeElem)
{
        ChunkList::LNode* temp = this->header->next;
        ChunkList::LNode* previous = this->header;
        while(temp != NULL)
        {
                for(int i = 0; i < temp->value.size(); i++)
                {
                        if(temp->value[i] == removeElem)
                        {
                                temp->value.removeAt(i);
                                i--;
                        }
                }
                if(temp->value.isEmpty())
                {
                        ChunkList::LNode* old = temp;
                        previous->next = temp->next;
                        temp = previous;
                        delete old;
                }
                previous = temp;
                temp = temp->next;
        }
}

void ChunkList::display()
{
        ChunkList::LNode* temp = this->header->next;
        while(temp != NULL)
        {
                for(int i = 0; i < temp->value.size(); i++)
                {
                        cout << temp->value[i] << " ";
                }
                cout << endl << "-----------" << endl;
                temp = temp->next;
        }
}
