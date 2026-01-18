// Hande Köksal 22401938
// Partially taken from the lecture slides

#include <iostream>
#include "FutureStack.h"
using namespace std;

FutureStack::FutureStack() {
    top = -1;
}

FutureStack::FutureStack(const int limit) {
    top = -1;
    this->limit = limit;
    futureLocations = new string[limit];
}

FutureStack::FutureStack(const FutureStack& other) {
    limit = other.limit;
    top = other.top;
    futureLocations = new string[limit];
    for (int i = 0; i <= top; i++) {
        futureLocations[i] = other.futureLocations[i];
    }
}

FutureStack& FutureStack::operator=(const FutureStack& other) {
    if (this == &other) return *this;

    delete[] futureLocations;

    limit = other.limit;
    top = other.top;
    futureLocations = new string[limit];
    for (int i = 0; i <= top; i++) {
        futureLocations[i] = other.futureLocations[i];
    }

    return *this;
}

FutureStack::~FutureStack() {
    delete[] futureLocations;
}

bool FutureStack::isEmpty() const {
    return top < 0;
}

bool FutureStack::push(const string& newEntry) {
    bool result = false;
    if (top < limit-1) {
        top++;
        futureLocations[top] = newEntry;
        result = true;
    }

    return result;
}

bool FutureStack::pop() {
    bool result = false;
    if (!isEmpty()) {
        top--;
        result = true;
    }
    
    return result;
}

string FutureStack::peek() const {
    if (!isEmpty()) {
        return futureLocations[top];
    }
    
    return "";
}

void FutureStack::clear() {
    while (!(isEmpty())) {
        pop();
    }
}