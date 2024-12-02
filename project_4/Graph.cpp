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
    Node_Entity * source_node = nullptr;        // pointer to source node
    Node_Entity * destination_node = nullptr;   // pointer to desitination node

    bool source_node_in_graph = false;
    bool destination_node_in_graph = false;

    bool edge_in_graph = false;
    
    // Iterate through all nodes to see if source and destination nodes exist in the graph
    for (int i=0; i<entity_nodes_list.size(); i++) {
        if (entity_nodes_list[i]->get_entity_id() == source_ID) {
            source_node = entity_nodes_list[i];
            source_node_in_graph = true;
        }

        if (entity_nodes_list[i]->get_entity_id() == destination_ID) {
            destination_node = entity_nodes_list[i];
            destination_node_in_graph = true;
        }
    }

    // Add/update edge if both source and destination nodes exist in the graph
    if ((source_node_in_graph == true) && (destination_node_in_graph == true)) {
        source_node->set_edge(destination_node, weight, label);
        destination_node->set_edge(source_node, weight, label);

        cout << "success" << endl;
    }
    
    else {
        cout << "failure" << endl;  // failure if source or destination node DNE in the graph
    }
}


// Insert a new entity node
void Graph::insert_entity_node(string ID, string name, string type) {
    bool entity_in_graph = false;

    for (i =0; i<entity_nodes_list.size(); i++) {
        if (entity_nodes_list[i]->get_entity_id() == ID) {  // check if entity ID is already in graph; update if it is
            entity_nodes_list[i]->set_entity_name(name);
            entity_nodes_list[i]->set_entity_type(type);
            entity_in_graph = true;
        }
    }

    if (!entity_in_graph) {   // create and add a new node if it doesnt already exist in the graph
        Node_Entity * node = new Node_Entity();
        node->set_entity_id(ID);
        node->set_entity_name(name);
        node->set_entity_type(type);
        entity_nodes_list.push_back(node);
    }
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