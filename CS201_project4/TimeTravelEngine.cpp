// Hande Köksal 22401938

#include <iostream>
#include "TimeTravelEngine.h"
using namespace std;

// Deafault constructor doesn't do anything 
// But it is necesary for allocating arrays
TimeTravelEngine::TimeTravelEngine() {
    branchCount = 0;
}

// allBranches is an array of pointers
// First, delete the contents
// Then, delete the array itself
TimeTravelEngine::~TimeTravelEngine() {
    if (branchCount > 0) {
        for (int i = 0; i < branchCount; i++) {
            delete allBranches[i];
        }

        delete[] allBranches;
    }
}

int TimeTravelEngine::createTimeBranch(const int pastCapacity, const int futureCapacity, const string startLocation, const int branchId) {
    if (branchExists(branchId)) {
        cout << "Cannot create time branch. A branch with ID " << branchId <<" already exists." << endl;
        return branchId;
    }
    
    // First element
    if (branchCount == 0) {
       allBranches = new TimeBranch*[1];
       allBranches[0] = new TimeBranch(pastCapacity, futureCapacity, startLocation, branchId);
    }
    // Inserting according to the ID's
    // Sorted
    else {
        TimeBranch** temp = new TimeBranch*[branchCount+1];
        int index = 0;
        while (index < branchCount && allBranches[index]->getBranchID() < branchId) {
            temp[index] = allBranches[index];
            index++;
        }

        temp[index] = new TimeBranch(pastCapacity, futureCapacity, startLocation, branchId);

        for (int i = index; i < branchCount; i++) {
            temp[i + 1] = allBranches[i];
        }

        delete[] allBranches;
        allBranches = temp;
    }

    branchCount++;
    cout << "Created time branch with ID " << branchId << "." << endl;
    return branchId;
}

void TimeTravelEngine::deleteTimeBranch(const int branchId) {
    if (!branchExists(branchId)) {
        cout << "Cannot delete branch. There is no branch with ID " << branchId << "." << endl;
        return;
    }

    if (branchCount == 1) {
        delete allBranches[0];
        delete[] allBranches;
        allBranches = nullptr;
        branchCount = 0;

        cout << "Deleted time branch " << branchId << "." << endl;
        return;
    }

    TimeBranch** temp = new TimeBranch*[branchCount-1];
    int count = 0;
    for (int i = 0; i < branchCount; i++) {
        if (allBranches[i]->getBranchID() == branchId) {
            delete allBranches[i];
        }
        else {
            temp[count] = allBranches[i];
            count++;
        }
    }

    delete[] allBranches;
    allBranches = temp;
    branchCount--;
    cout << "Deleted time branch " << branchId << "." << endl;
}

void TimeTravelEngine::printAllBranches() const {
    if (branchCount == 0) {
        cout << "There are no time branches to show." << endl;
        return;
    }

    cout << "Time branches in the system:" << endl;
    for (int i = 0; i < branchCount; i++) {
        cout << "Branch " << allBranches[i]->getBranchID() << ":" << endl;
        allBranches[i]->printInfo();
        if (i != branchCount-1) {
            cout << endl;
        }
    }
}

void TimeTravelEngine::travelTo(const int branchId, const string newLocation) {
    TimeBranch* branch = getBranchByID(branchId);
    if (branch == nullptr) {
        cout << "Cannot travel. There is no branch with ID " << branchId << "." << endl;
        return;
    }

    if (!branch->pastStack->push(branch->currLocation)) {
        cout << "Cannot travel to " << newLocation << " in branch " << branchId << ". Past stack capacity exceeded." << endl;
        return;
    }
    
    branch->currLocation = newLocation;
    branch->futureStack->clear();
    cout << "Traveled to " << newLocation << " in branch " << branchId << "." << endl;
}

void TimeTravelEngine::fastForward(const int branchId, const int k) {
    TimeBranch* branch = getBranchByID(branchId);
    if (branch == nullptr) {
        cout << "There is no branch with ID " << branchId << "." << endl;
        return;
    }

    int stepsToTake = min(k, branch->futureStack->top + 1);
    if (branch->pastStack->top + stepsToTake >= branch->pastStack->limit) {
        cout << "Cannot fast forward " << stepsToTake << " steps in branch " << branchId << ". Past stack capacity exceeded." << endl;
        return;
    }

    int steps = 0;
    while (steps < stepsToTake && branch->futureStack->top >= 0) {
        branch->pastStack->push(branch->currLocation);
        branch->currLocation = branch->futureStack->peek();
        branch->futureStack->pop();
        steps++;
    }

    cout << "Fast forwarded " << steps << " steps in branch " << branchId << "." << endl;
}

void TimeTravelEngine::rewind(const int branchId, const int k) {
    TimeBranch* branch = getBranchByID(branchId);
    if (branch == nullptr) {
        cout << "There is no branch with ID " << branchId << "." << endl;
        return;
    }

    int stepsToTake = min(k, branch->pastStack->top + 1);
    if (branch->futureStack->top + stepsToTake >= branch->futureStack->limit) {
        cout << "Cannot rewind " << stepsToTake << " steps in branch " << branchId << ". Future stack capacity exceeded." << endl;
        return;
    }

    int steps = 0;
    while (steps < stepsToTake && branch->pastStack->top >= 0) {
        branch->futureStack->push(branch->currLocation);
        branch->currLocation = branch->pastStack->peek();
        branch->pastStack->pop();
        steps++;
    }

    cout << "Rewound " << steps << " steps in branch " << branchId << "." << endl;
}

void TimeTravelEngine::placeTimeStone(const int branchId) {
    TimeBranch* branch = getBranchByID(branchId);
    if (branch == nullptr) {
        cout << "There is no branch with ID " << branchId << "." << endl;
        return;
    }

    branch->stoneStack->push(branch->currLocation);
    cout << "Time stone placed at " << branch->currLocation << "." << endl;
}

void TimeTravelEngine::activateTimeStone(const int branchId) {
    TimeBranch* branch = getBranchByID(branchId);
    if (branch == nullptr) {
        cout << "There is no branch with ID " << branchId << "." << endl;
        return;
    }

    if (branch->stoneStack->isEmpty()) {
        cout << "Cannot activate time stone. No time stones available." << endl;
        return;
    }

    string stoneLocation = branch->stoneStack->peek();

    if (stoneLocation.compare(branch->currLocation) == 0) {
        branch->futureStack->clear();
        branch->stoneStack->pop();
        cout << "Time stone activated. The traveler is now at " << stoneLocation << "." << endl;
        return;
    }

    if (branch->searchPastStack(*(branch->pastStack), stoneLocation)) {
        while (branch->currLocation.compare(stoneLocation) != 0) {
            rewindForStone(branch);
        }

        cout << "Time stone activated. The traveler is now at " << stoneLocation << "." << endl;
        branch->stoneStack->pop();
        branch->futureStack->clear();
        return;
    }

    else if (branch->searchFutureStack(*(branch->futureStack), stoneLocation)) {
        int distance = branch->distanceInFuture(*(branch->futureStack), stoneLocation);
        if (branch->pastStack->top + distance >= branch->pastStack->limit) {
            branch->stoneStack->pop();
            cout << "Time stone discarded. Past stack capacity exceeded." << endl;
            return;
        }

        while (branch->currLocation.compare(stoneLocation) != 0) {
            fastForwardForStone(branch);
        }

        cout << "Time stone activated. The traveler is now at " << stoneLocation << "." << endl;
        branch->stoneStack->pop();
        branch->futureStack->clear();
        return;
    }

    else {
        branch->stoneStack->pop();
        cout << "Time stone discarded. The recorded moment is no longer reachable." << endl;
        return;
    }
}

void TimeTravelEngine::printTimeBranch(const int branchId) const {
    TimeBranch* branchToPrint = getBranchByID(branchId);
    if (branchToPrint != nullptr) {
        branchToPrint->printInfo();
        return;
    }

    cout << "Cannot print branch. There is no branch with ID " << branchId << "." << endl; 
}

int TimeTravelEngine::mergeBranches(const int branchId1, const int branchId2, const int newBranchId) {
    TimeBranch* branch1 = getBranchByID(branchId1);
    TimeBranch* branch2 = getBranchByID(branchId2);
    if (branch1 == nullptr || branch2 == nullptr) {
        cout << "Cannot merge branches. Missing branch IDs." << endl;
        return -1;
    }

    if (branch1->currLocation.compare(branch2->currLocation) != 0) {
        cout << "Cannot merge branches. Current locations do not match." << endl;
        return -1;
    }

    if (branchExists(newBranchId)) {
        cout << "Cannot merge branches. A branch with ID " << newBranchId << " already exists." << endl;
        return -1;
    }

    // Calculate parameters
    int pastCap = branch1->getPastCapacity() + branch2->getPastCapacity();
    int futureCap = branch1->getFutureCapacity() + branch2->getFutureCapacity();
    string startLoc = branch1->currLocation;

    // Create time branch
    createForMerge(pastCap, futureCap, startLoc, newBranchId);

    // Stacks
    TimeBranch* branchNew = getBranchByID(newBranchId);

    // Past stacks
    PastStack rewindPast1 = *(branch1->pastStack);
    PastStack tempPast1(branch1->getPastCapacity());
    while (!rewindPast1.isEmpty()) {
        tempPast1.push(rewindPast1.peek());
        rewindPast1.pop();
    }
    while (!tempPast1.isEmpty()) {
        branchNew->pastStack->push(tempPast1.peek());
        tempPast1.pop();
    }

    PastStack rewindPast2 = *(branch2->pastStack);
    PastStack tempPast2(branch2->getPastCapacity());

    while (!rewindPast2.isEmpty()) {
        tempPast2.push(rewindPast2.peek());
        rewindPast2.pop();
    }

    while (!tempPast2.isEmpty()) {
        branchNew->pastStack->push(tempPast2.peek());
        tempPast2.pop();
    }

    // Future stacks
    FutureStack rewindFuture1 = *(branch1->futureStack);
    FutureStack tempFuture1(branch1->getFutureCapacity());
    while (!rewindFuture1.isEmpty()) {
        tempFuture1.push(rewindFuture1.peek());
        rewindFuture1.pop();
    }
    while (!tempFuture1.isEmpty()) {
        branchNew->futureStack->push(tempFuture1.peek());
        tempFuture1.pop();
    }

    FutureStack rewindFuture2 = *(branch2->futureStack);
    FutureStack tempFuture2(branch2->getFutureCapacity());

    while (!rewindFuture2.isEmpty()) {
        tempFuture2.push(rewindFuture2.peek());
        rewindFuture2.pop();
    }

    while (!tempFuture2.isEmpty()) {
        branchNew->futureStack->push(tempFuture2.peek());
        tempFuture2.pop();
    }

    // Stone stacks
    StoneStack rewindStone1 = *(branch1->stoneStack);
    StoneStack tempStone1;
    while (!rewindStone1.isEmpty()) {
        tempStone1.push(rewindStone1.peek());
        rewindStone1.pop();
    }
    while (!tempStone1.isEmpty()) {
        branchNew->stoneStack->push(tempStone1.peek());
        tempStone1.pop();
    }

    StoneStack rewindStone2 = *(branch2->stoneStack);
    StoneStack tempStone2;

    while (!rewindStone2.isEmpty()) {
        tempStone2.push(rewindStone2.peek());
        rewindStone2.pop();
    }

    while (!tempStone2.isEmpty()) {
        branchNew->stoneStack->push(tempStone2.peek());
        tempStone2.pop();
    }

    // Delete time branch 1 and 2
    deleteForMerge(branchId1);
    deleteForMerge(branchId2);

    cout << "Time branches " << branchId1 << " and " << branchId2 << " merged into new branch " << newBranchId << "." << endl;
    return newBranchId;
}

bool TimeTravelEngine::branchExists(int id) {
    for (int i = 0; i < branchCount; i++) {
        if (allBranches[i]->getBranchID() == id) {
            return true;
        }
    }
    
    return false;
}

TimeBranch* TimeTravelEngine::getBranchByID(int id) const {
    for (int i = 0; i < branchCount; i++) {
        if (allBranches[i]->getBranchID() == id) {
            return allBranches[i];
        }
    }

    return nullptr;
}

void TimeTravelEngine::rewindForStone(TimeBranch* branch) {
    int stepsToTake = 1;

    int steps = 0;
    while (steps < stepsToTake && branch->pastStack->top >= 0) {
        branch->currLocation = branch->pastStack->peek();
        branch->pastStack->pop();
        steps++;
    }
}

void TimeTravelEngine::fastForwardForStone(TimeBranch* branch) {
    int stepsToTake = 1;
    int steps = 0;
    while (steps < stepsToTake && branch->futureStack->top >= 0) {
        branch->pastStack->push(branch->currLocation);
        branch->currLocation = branch->futureStack->peek();
        branch->futureStack->pop();
        steps++;
    }
}

void TimeTravelEngine::createForMerge(const int pastCapacity, const int futureCapacity, const string startLocation, const int branchId) {
    // First element
    if (branchCount == 0) {
       allBranches = new TimeBranch*[1];
       allBranches[0] = new TimeBranch(pastCapacity, futureCapacity, startLocation, branchId);
    }
    // Inserting according to the ID's
    // Sorted
    else {
        TimeBranch** temp = new TimeBranch*[branchCount+1];
        int index = 0;
        while (index < branchCount && allBranches[index]->getBranchID() < branchId) {
            temp[index] = allBranches[index];
            index++;
        }

        temp[index] = new TimeBranch(pastCapacity, futureCapacity, startLocation, branchId);

        for (int i = index; i < branchCount; i++) {
            temp[i + 1] = allBranches[i];
        }

        delete[] allBranches;
        allBranches = temp;
    }

    branchCount++;
}

void TimeTravelEngine::deleteForMerge(int branchId) {
    if (branchCount == 1) {
        delete allBranches[0];
        delete[] allBranches;
        allBranches = nullptr;
        branchCount = 0;
        return;
    }

    TimeBranch** temp = new TimeBranch*[branchCount-1];
    int count = 0;
    for (int i = 0; i < branchCount; i++) {
        if (allBranches[i]->getBranchID() == branchId) {
            delete allBranches[i];
        }
        else {
            temp[count] = allBranches[i];
            count++;
        }
    }

    delete[] allBranches;
    allBranches = temp;
    branchCount--;
}