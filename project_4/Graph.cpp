#include "Graph.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;


// Constructor definition
Graph::Graph() {
    entity_nodes_list = vector < Node_Entity * > ();   // Vector of pointers of all nodes (entites)
}


// Destructor definition
Graph::~Graph() {
    for (int i = 0; i < entity_nodes_list.size(); i++) {
        delete entity_nodes_list[i];
        entity_nodes_list[i] = nullptr;
    }
    entity_nodes_list.clear();
}


// Load dataset (.txt file) into graph (filename = "entities" or "relationships")
void Graph::load_dataset(string filename) {

}


// Insert a new relationship edge
void Graph::insert_relationship_edge(string source_ID, string label, string destination_ID, double weight) {

}


// Insert a new entity node
void Graph::insert_entity_node(string ID, string name, string type) {

}


// Print all nodes adjacent to given ID node
void Graph::print_adjacent_nodes(string ID) {

}


// Delete node with ID "ID" and any edges that contain it
void Graph::delete_node(string ID) {

}


// Get nodes and labels along highest weight path between 2 nodes
void Graph::highest_weight_path(string ID_1, string ID_2) {

}


// Get 2 nodes with highest weight path between them
void Graph::highest_weight_path_nodes() {

}


// Print all node id's w/ given field string
void Graph::find_all_nodes(string field_type, string field_string) {

}