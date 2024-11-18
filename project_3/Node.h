#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>
using namespace std;

class Node {
private:
    vector<Node*> children;  // Fixed-size vector of child nodes
    bool isTerminal;   // Indicates if the node is a terminal node
    string value;    // The classification value stored in the node

public:
    Node();   // Constructor
    ~Node();  // Destructor

    Node* return_child_node(int index);   // Return the child node at an index
    void set_child_node(int index, Node* child);  // Set a child node at an index
    bool is_terminal_node();    // Returns if the node is a terminal node or not
    void set_terminal_node(bool terminal);  // Indicate if the node is a terminal node or not
    string return_node_value();    // Return value of the node
    void set_node_value(string val); // Set the node's value
};

#endif