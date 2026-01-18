// Hande Köksal 22401938
// Partially taken from the lecture slides

#include <iostream>
#include "PastStack.h"
using namespace std;

PastStack::PastStack() {
    top = -1;
}

PastStack::PastStack(const int limit) {
    top = -1;
    this->limit = limit;
    pastLocations = new string[limit];
}

PastStack::PastStack(const PastStack& other) {
    limit = other.limit;
    top = other.top;
    pastLocations = new string[limit];
    for (int i = 0; i <= top; i++) {
        pastLocations[i] = other.pastLocations[i];
    }
}

PastStack& PastStack::operator=(const PastStack& other) {
    if (this == &other) return *this;

    delete[] pastLocations;

    limit = other.limit;
    top = other.top;
    pastLocations = new string[limit];
    for (int i = 0; i <= top; i++) {
        pastLocations[i] = other.pastLocations[i];
    }

    return *this;
}

PastStack::~PastStack() {
    delete[] pastLocations;
}

bool PastStack::isEmpty() const {
    return top < 0;
}

bool PastStack::push(const string& newEntry) {
    bool result = false;
    if (top < limit-1) {
        top++;
        pastLocations[top] = newEntry;
        result = true;
    }

    return result;
}

bool PastStack::pop() {
    bool result = false;
    if (!isEmpty()) {
        top--;
        result = true;
    }
    
    return result;
}

string PastStack::peek() const {
    if (!isEmpty()) {
        return pastLocations[top];
    }
    
    return "";
}