// Hande Köksal 22401938
// Partially taken from the lecture slides

#include <iostream>
#include "StoneStack.h"
using namespace std;

StoneStack::StoneStack() {
    topPtr = nullptr;
}

StoneStack::StoneStack(const StoneStack& other) {
    topPtr = nullptr;

    StoneStack reverse;
    Node* current = other.topPtr;

    // First reversal (top → bottom)
    while (current != nullptr) {
        reverse.push(current->getItem());
        current = current->getNext();
    }

    // Second reversal (restore original order)
    while (!reverse.isEmpty()) {
        push(reverse.peek());
        reverse.pop();
    }
}

StoneStack& StoneStack::operator=(const StoneStack& other) {
    if (this == &other) return *this;

    while (!isEmpty()) pop();

    StoneStack reverse;
    Node* current = other.topPtr;

    while (current != nullptr) {
        reverse.push(current->getItem());
        current = current->getNext();
    }

    while (!reverse.isEmpty()) {
        push(reverse.peek());
        reverse.pop();
    }

    return *this;
}

StoneStack::~StoneStack() {
    while (!isEmpty()) {
        pop();
    }
}

bool StoneStack::isEmpty() const {
    return topPtr == nullptr;
}

bool StoneStack::push(const string& newItem) {
    Node* newNodePtr = new Node(newItem, topPtr);
    topPtr = newNodePtr;
    newNodePtr = nullptr;
    return true;
}

bool StoneStack::pop() {
    bool result = false;
    if (!isEmpty()) {
        Node* nodeToDeletePtr = topPtr;
        topPtr = topPtr->getNext();

        nodeToDeletePtr->setNext(nullptr);
        delete nodeToDeletePtr;
        nodeToDeletePtr = nullptr;

        result = true;
    }

    return result;
}

string StoneStack::peek() const {
    if (!isEmpty()) {
        return topPtr->getItem();
    }

    return "";
}