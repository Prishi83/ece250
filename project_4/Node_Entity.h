#ifndef NODE_ENTITY_H
#define NODE_ENTITY_H

#include <vector>
#include <string>
#include <tuple>
using namespace std;

class Node_Entity {
private:
    vector < tuple < Node_Entity * , double, string > > edges_list; // Vector contains the edges of a node
                                                                    // tuple contains: pointer to adjacent node, edge's weight, edge's label
    string entity_id;   // entity node id
    string entity_name; // entity node name
    string entity_type; // entity node type

public:
    Node_Entity();   // Constructor
    ~Node_Entity();  // Destructor

    void set_edge(Node_Entity * adjacent_node, double edge_weight, string edge_label); // Insert or update (weight & label) edge between current & adjacent node
                                                                                        // Create a tuple of:
                                                                                        //    pointer to adjacent node, edge's weight, edge's labe;
                                                                                        // Add this tuple to edges_list

    void delete_edge(Node_Entity * adjacent_node);   // Delete edge between current and adjacent node
                                                    // Find and delete adjacent node's tuple from edges_list of current node

    // For accessing private members from this class when working in the Graph class:
    vector < tuple < Node_Entity * , double, string > > get_edges_list();    // Get all of the edges (adjacent nodes) for node

    string get_entity_id();    // get entity node's id
    void set_entity_id(string new_id);    // update/set entity node's id
    
    string get_entity_name();  // get entity node's name
    void set_entity_name(string new_name);  // update/set entity node's name

    string get_entity_type();  // get entity node's type
    void set_entity_type(string new_type);  // update/set entity node's type
};

#endif