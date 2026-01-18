// Hande Köksal 22401938

#include <iostream>
#include "TimeBranch.h"
using namespace std;

TimeBranch::TimeBranch() {

}

TimeBranch::TimeBranch(const int pastCapacity, const int futureCapacity, const string startLocation, const int branchId) {
    this->pastCapacity = pastCapacity;
    this->futureCapacity = futureCapacity;
    currLocation = startLocation;
    this->branchId = branchId;
    initializeStacks();
}

TimeBranch::~TimeBranch() {
    delete pastStack;
    delete futureStack;
    delete stoneStack;
}

void TimeBranch::initializeStacks() {
    pastStack = new PastStack(pastCapacity);
    futureStack = new FutureStack(futureCapacity);
    stoneStack = new StoneStack();
}

int TimeBranch::getBranchID() {
    return branchId;
}

// Functions to print stacks from bottom to top
// The parameters are stacks that are pass by value
// So these functions doesn't do anything to the original stacks
void TimeBranch::printBottomToTop_Past(PastStack ogPast) {
    PastStack temp(ogPast.limit);

    while (!ogPast.isEmpty()) {
        temp.push(ogPast.peek());
        ogPast.pop();
    }

    bool first = true;
    while (!temp.isEmpty()) {
        if (!first) {
            cout << ", ";
        }
        cout << temp.peek();
        temp.pop();
        first = false;
    }
}

void TimeBranch::printBottomToTop_Future(FutureStack ogFuture) {
    FutureStack temp(ogFuture.limit);

    while (!ogFuture.isEmpty()) {
        temp.push(ogFuture.peek());
        ogFuture.pop();
    }

    bool first = true;
    while (!temp.isEmpty()) {
        if (!first) {
            cout << ", ";
        }
        cout << temp.peek();
        temp.pop();
        first = false;
    }
}

void TimeBranch::printBottomToTop_Stone(StoneStack ogStone) {
    StoneStack temp;

    while (!ogStone.isEmpty()) {
        temp.push(ogStone.peek());
        ogStone.pop();
    }

    bool first = true;
    while (!temp.isEmpty()) {
        if (!first) {
            cout << ", ";
        }
        cout << temp.peek();
        temp.pop();
        first = false;
    }
}

void TimeBranch::printInfo() {
    cout << "Past   : [ "; printBottomToTop_Past(*pastStack); cout << " ]" << endl;
    cout << "Current: ( " << currLocation << " )" << endl;
    cout << "Future : [ "; printBottomToTop_Future(*futureStack); cout << " ]" << endl;
    cout << "Stones : [ "; printBottomToTop_Stone(*stoneStack); cout << " ]" << endl;
}

bool TimeBranch::searchPastStack(PastStack past, string location) {
    while (!past.isEmpty()) {
        if (past.peek() == location) {
            return true;
        }
        past.pop();
    }
    return false;
}

bool TimeBranch::searchFutureStack(FutureStack future, string location) {
    while (!future.isEmpty()) {
        if (future.peek() == location) {
            return true;
        }
        future.pop();
    }
    return false;
}

int TimeBranch::distanceInFuture(FutureStack future, string location) {
    int distance = 0;

    while (future.top >= 0) {
        if (future.peek() == location) {
            return distance;
        }
        future.pop();
        distance++;
    }

    return -1;
}

int TimeBranch::getPastCapacity() {
    return pastCapacity;
}

int TimeBranch::getFutureCapacity() {
    return futureCapacity;
}