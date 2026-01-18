// Hande Köksal 22401938
// Partially taken from the lecture slides

#ifndef PAST_STACK_
#define PAST_STACK_

#include <string>
using namespace std;

class PastStack {
public:
    PastStack();
    PastStack(const int limit);
    PastStack(const PastStack& other);
    PastStack& operator=(const PastStack& other);
    ~PastStack();
    int limit;
    string* pastLocations;
    int top;
    bool isEmpty() const;
    bool push(const string& newEntry);
    bool pop();
    string peek() const;
};
#endif