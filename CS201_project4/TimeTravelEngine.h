// Hande Köksal 22401938

#ifndef TIME_TRAVEL_ENGINE_
#define TIME_TRAVEL_ENGINE_

#include <string>
#include "TimeBranch.h"
using namespace std;

class TimeTravelEngine {
public:
    // Functions given in the pdf -start-
    TimeTravelEngine();
    ~TimeTravelEngine();

    int createTimeBranch(const int pastCapacity, const int futureCapacity, const string startLocation, const int branchId);

    void deleteTimeBranch(const int branchId);
    void printAllBranches() const;

    void travelTo(const int branchId, const string newLocation);

    void fastForward(const int branchId, const int k);
    void rewind(const int branchId, const int k);

    void placeTimeStone(const int branchId);
    void activateTimeStone(const int branchId);

    void printTimeBranch(const int branchId) const;

    int mergeBranches(const int branchId1, const int branchId2, const int newBranchId);
    // Functions given in the pdf -end-

    TimeBranch** allBranches;
    int branchCount;

    bool branchExists(int id);
    TimeBranch* getBranchByID(int id) const;
    void rewindForStone(TimeBranch* branch);
    void fastForwardForStone(TimeBranch* branch);
    void createForMerge(const int pastCapacity, const int futureCapacity, const string startLocation, const int branchId);
    void deleteForMerge(int branchId);
};
#endif