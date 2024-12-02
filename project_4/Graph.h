#ifndef GRAPH_H
#define GRAPH_H

#include "Node_Entity.h"    // Include the Node_Entity class
#include "illegal_exception.h"  // Include the illegal_exception class for try/catch error
#include <string>
#include <vector>
#include <tuple>
using namespace std;

class Graph {
private:
    vector < Node_Entity * > entity_nodes_list;   // Vector of all nodes (entites)
                                                  // Pointers (Node_Entity *) point to objects of type Node_Entity
                                                  // each pointer represents a node

    //Node_Entity* find_node(string ID); // Helper function for finding a node given its id

public:
    Graph();   // Constructor
    ~Graph();  // Destructor

    void load_dataset(string filename);  // Load dataset (.txt file) into graph (filename = "entities" or "relationships")
    void insert_relationship_edge(string source_ID, string label, string destination_ID, double weight);  // Insert a new relationship edge
    void insert_entity_node(string ID, string name, string type);  // Insert a new entity node
    void print_adjacent_nodes(string ID);  // Print all nodes adjacent to given ID node
    void delete_node(string ID);  // Delete node with ID "ID" and any edges that contain it
    void highest_weight_path(string ID_1, string ID_2);  // Print nodes and labels along highest weight path b/w 2 nodes
    void highest_weight_path_nodes();  // Print 2 nodes with highest weight path b/w them
    void find_all_nodes(string field_type, string field_string);  // Print all node id's w/ given field string
};

#endif