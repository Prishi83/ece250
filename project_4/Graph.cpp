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
        delete entity_nodes_list[i];      // delete all pointers and set them to nullptr
        entity_nodes_list[i] = nullptr;
    }
    entity_nodes_list.clear();  // vector method to remove all elements from vector
}


// Load dataset (.txt file) into graph (type = "entities" or "relationships")
void Graph::load_dataset(string filename, string type) {
    ifstream file(filename);  // Open input file
        string line;

    if (file.is_open()) {
        while (getline(file, line)) {   // Read each line of the file
            istringstream stream(line);  // Use stream to parse the line
            string entity_ID, entity_name, entity_type;  // For entity files
            string relation_sourceID, relation_label, relation_destinationID;   // For relationship files
            double relation_weight; // For relationship files

            if (type == "entities") {
                // Parse line using ' ' as a delimiter
                getline(stream, entity_ID, ' ');
                getline(stream, entity_name, ' ');
                getline(stream, entity_type, ' ');
                insert_entity_node(entity_ID, entity_name, entity_type); // Insert entity node into graph
            }

            else if (type == "relationships") {
                // Parse line using ' ' as a delimiter
                getline(stream, relation_sourceID, ' ');
                getline(stream, relation_label, ' ');
                getline(stream, relation_destinationID, ' ');
                stream >> relation_weight;
                insert_relationship_edge(relation_sourceID, relation_label, relation_destinationID, relation_weight); // Insert relationship edge into graph
            }
        }
        file.close();
    }
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