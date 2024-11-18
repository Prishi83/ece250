#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>
using namespace std;

class Node {
private:
    bool is_terminal;   // Indicates if the node is a terminal node
    string value;    // The classification value stored in the node

public:
    vector <Node *> children;  // Vector of child nodes

    Node();   // Constructor
    ~Node();  // Destructor

    bool is_terminal_node();    // Returns if the node is a terminal node or not
    void set_terminal_node(bool new_terminal_status);  // Indicate if the node is a terminal node or not
    string node_value();    // Return value of the node
    void set_node_value(string new_value); // Set the node's value
};

#endif