// Hande Köksal 22401938
// Partially taken from the lecture slides

#ifndef STONE_STACK_H
#define STONE_STACK_H

#include <string>
#include "Node.h"

class StoneStack {
public:
    StoneStack();
    StoneStack(const StoneStack& other);
    StoneStack& operator=(const StoneStack& other);
    ~StoneStack();
    bool isEmpty() const;
    bool push(const std::string& newItem);
    bool pop();
    std::string peek() const;

private:
    Node* topPtr;
};

#endif