#include "Node_Entity.h"
#include <algorithm>
#include <iostream>
using namespace std;

// Constructor definition
Node_Entity::Node_Entity() {
    edges_list = vector < tuple < Node_Entity* , double, string > > ();   // Holds all edges (adjacent nodes)
    string entity_id = "";   // entity node id
    string entity_name = ""; // entity node name
    string entity_type = ""; // entity node type
}


// Destructor definition
Node_Entity::~Node_Entity() { 
}


// Get list of edges (adjacent nodes) for current node
vector < tuple < Node_Entity* , double, string > > Node_Entity::get_edges() {
    return edges_list;
}



// Insert edge between current and an adjacent node
    // Create a tuple of: pointer to adjacent node, edge's weight, edge's label
    // Add this tuple to edges_list
void Node_Entity::insert_edge(Node_Entity* adjacent_node, double weight, string label) {

}


// Delete edge between current and an adjacent node
    // Find and delete adjacent node's tuple from edges_list of current node
void Node_Entity::delete_edge(Node_Entity* adjacent_node) {

}


// Get the node's id    
string Node_Entity::get_entity_id(){
    return entity_id;
}


// Get the node's name
string Node_Entity::get_entity_name() {
    return entity_name;
}


// Get the node's type
string Node_Entity::get_entity_type() {
    return entity_type;
}