#include <iostream>

#include "IntList.h"

using namespace std;

IntList::IntList() : dummyHead(new IntNode(0)), dummyTail(new IntNode(0)) {//initialize empty list
    dummyHead->next = dummyTail;
    dummyTail->prev = dummyHead;
}

IntList::~IntList() { //destructor
    IntNode *currNode = dummyHead;
    while(currNode!=dummyTail) {
        IntNode *tempNode = currNode;
        currNode = currNode->next;

        delete tempNode;
    }
    delete currNode;
}

void IntList::push_front(int value) {
    IntNode *newNode = new IntNode(value);
    IntNode *next = dummyHead->next;

    dummyHead->next = newNode;
    newNode->prev = dummyHead;
    newNode->next = next;
    next->prev = newNode;
}

void IntList::pop_front() {
    IntNode *currHead = dummyHead->next;
    IntNode *tempNext = dummyHead->next->next;

    dummyHead->next = tempNext;
    tempNext->prev = dummyHead;

    delete currHead;
    currHead->next = nullptr;
}

void IntList::push_back(int value) {
    IntNode *newNode = new IntNode(value);
    IntNode *prev = dummyTail->prev;

    newNode->next = dummyTail;
    newNode->prev = prev;

    dummyTail->prev = newNode;
    prev->next = newNode;
}

void IntList::pop_back() {
    IntNode *remove = dummyTail->prev;
    IntNode *newTail = dummyTail->prev->prev;

    delete remove;

    newTail->next = dummyTail;
    dummyTail->prev = newTail;

    remove->next = nullptr;
}

bool IntList::empty() const {
    if(dummyHead->next==dummyTail) {
        return true;
    }
    return false;
}

ostream &operator<<(ostream &out, const IntList &rhs) {
    if(!rhs.empty()) {
        if(rhs.dummyHead->next->next==rhs.dummyTail) { //only 1 item
            out<<rhs.dummyHead->next->data;
        }
        else {  
            IntNode *currNode = rhs.dummyHead->next;
            while(currNode!=rhs.dummyTail) {
                out<<currNode->data;
                if(currNode->next!=rhs.dummyTail) {
                    out<<" ";
                }
                currNode = currNode->next;
            }
        }
    }
    return out;
}

void IntList::printReverse() const {
    if(!empty()) {
        if(dummyHead->next->next==dummyTail) { //only 1 item
            cout<<dummyHead->next->data;
        }
        else {  
            IntNode *currNode = dummyTail->prev;
            while(currNode!=dummyHead) {
                cout<<currNode->data;
                if(currNode->prev!=dummyHead) {
                    cout<<" ";
                }
                currNode = currNode->prev;
            }
        }
    }
}
