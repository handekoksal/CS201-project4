// Hande Köksal 22401938
// Taken from the lecture slides

#ifndef NODE_H
#define NODE_H

#include <string>

class Node {
private:
    std::string item;
    Node* next;

public:
    Node() : next(nullptr) {}
    Node(const std::string& anItem) : item(anItem), next(nullptr) {}
    Node(const std::string& anItem, Node* nextNodePtr) : item(anItem), next(nextNodePtr) {}

    void setItem(const std::string& anItem) { item = anItem; }
    void setNext(Node* nextNodePtr) { next = nextNodePtr; }

    std::string& getItem() { return item; }
    const std::string& getItem() const { return item; }
    Node* getNext() const { return next; }
};

#endif