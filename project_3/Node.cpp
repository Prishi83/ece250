#include "Node.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;


// Constructor definition
Node::Node() {
    is_terminal = false;
    value = "";
}


// Destructor definition
Node::~Node() {
    
}


// Returns if the node is a terminal node or not
bool Node::is_terminal_node() {
    return is_terminal;
}


// Indicate if the node is a terminal node or not
void Node::set_terminal_node(bool new_terminal_status) {
    is_terminal = new_terminal_status;
}


// Return value of the node
string Node::node_value() {
    return value;
}


// Set the node's value
void Node::set_node_value(string new_value) {
    value = new_value;
}