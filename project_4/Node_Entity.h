#ifndef NODE_ENTITY_H
#define NODE_ENTITY_H

#include <vector>
#include <string>
#include <tuple>
using namespace std;

class Node_Entity {
private:
    vector < tuple < Node_Entity * , double, string > > edges_list; // Vector contains the edges of a node
                                                                    // tuple contains: pointer to adjacent node,
                                                                    //                 edge's weight,
                                                                    //                 edge's label
    string entity_id;   // entity node id
    string entity_name; // entity node name
    string entity_type; // entity node type

public:
    Node_Entity();   // Constructor
    ~Node_Entity();  // Destructor

    vector < tuple < Node_Entity * , double, string > > get_edges();    // Get all of the edges (adjacent nodes)
    void insert_edge(Node_Entity * adjacent_node, double edge_weight, string edge_label); // Insert edge b/w current & adjacent node
                                                                                  // Create a tuple of:
                                                                                  //    pointer to adjacent node,
                                                                                  //    edge's weight,
                                                                                  //    edge's labe;
                                                                                  // Add this tuple to edges_list
    void delete_edge(Node_Entity * adjacent_node);   // Delete edge between current and adjacent node
                                                    // Find and delete adjacent node's tuple from edges_list of current node

    // For accessing private variables in the Graph class:
    string get_entity_id();    // get entity node's id
    string get_entity_name();  // get entity node's name
    string get_entity_type();  // get entity node's type
};

#endif