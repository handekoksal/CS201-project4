// Hande Köksal 22401938

#ifndef TIME_BRANCH_
#define TIME_BRANCH_

#include <string>
#include "PastStack.h"
#include "FutureStack.h"
#include "StoneStack.h"

class TimeBranch {
public:
    TimeBranch();
    TimeBranch(const int pastCapacity, const int futureCapacity, const std::string startLocation, const int branchId);
    ~TimeBranch();
    void initializeStacks();
    std::string currLocation;
    PastStack* pastStack;
    FutureStack* futureStack;
    StoneStack* stoneStack;
    int getBranchID();
    void printInfo();
    bool searchPastStack(PastStack past, string location);
    bool searchFutureStack(FutureStack future, string location);
    int distanceInFuture(FutureStack future, string location);
    int getPastCapacity();
    int getFutureCapacity();

private:
    int pastCapacity;
    int futureCapacity;
    int branchId;
    void printBottomToTop_Past(PastStack ogStack);
    void printBottomToTop_Future(FutureStack ogStack);
    void printBottomToTop_Stone(StoneStack ogStack);
};
#endif