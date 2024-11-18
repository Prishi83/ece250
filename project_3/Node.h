#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>
using namespace std;

class Node {
private:
    vector<Node*> children; // Fixed-size vector of child nodes
    bool isTerminal;             // Indicates if the node is a terminal node
    string value;           // The classification value stored in the node

public:
    Node();                      // Constructor
    ~Node();                     // Destructor

    Node* getChild(int index);   // Returns a child node at a specific index
    void setChild(int index, Node* child); // Sets a child node at a specific index

    bool getIsTerminal();        // Returns whether the node is terminal
    void setIsTerminal(bool terminal); // Sets the terminal status of the node

    string getValue();      // Returns the value of the node
    void setValue(string val); // Sets the value of the node
};

#endif