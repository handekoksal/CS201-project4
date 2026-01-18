// Hande Köksal 22401938
// Partially taken from the lecture slides

#ifndef FUTURE_STACK_
#define FUTURE_STACK_

#include <string>
using namespace std;

class FutureStack {
public:
    FutureStack();
    FutureStack(const int limit);
    FutureStack(const FutureStack& other);
    FutureStack& operator=(const FutureStack& other);
    ~FutureStack();
    int limit;
    string* futureLocations;
    int top;
    bool isEmpty() const;
    bool push(const string& newEntry);
    bool pop();
    string peek() const;
    void clear();
};
#endif