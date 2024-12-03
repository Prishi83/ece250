#include "Graph.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;
#include <cmath>


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


// Try-Catch helper function for PRINT, DELETE, PATH to check for any characters other than uppercase/lowercase/numeral
void check_input_characters_exception(string ID) {
    string accepted_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890";
    for (int i=0; i<(ID.size()); i++) {
        bool invalid_char_in_ID = true;
        for (int j=0; j<(accepted_chars.size()); j++) {
            if ((ID[i]) == (accepted_chars[j])) {  // Check for accepted characters
                invalid_char_in_ID = false; 
            }
        }
        if (invalid_char_in_ID) {
            throw illegal_exception();  // Throw exception if invalid character detected (try-catch block)
        }
    }
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
bool Graph::insert_relationship_edge(string source_ID, string label, string destination_ID, double weight) {
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
        return true;
    }
    else {
        return false;  // failure if source or destination node DNE in the graph
    }
}


// Insert a new entity node
void Graph::insert_entity_node(string ID, string name, string type) {
    bool entity_in_graph = false;

    for (int i =0; i<entity_nodes_list.size(); i++) {
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
    try {
        check_input_characters_exception(ID);

        bool node_in_graph = false;

        for (int i=0; i< entity_nodes_list.size(); i++) {
            if (entity_nodes_list[i]->get_entity_id() == ID) {   // Find node of given ID in the list of entity nodes
                node_in_graph = true;

                vector < tuple < Node_Entity * , double, string > > edges_list = entity_nodes_list[i]->get_edges_list(); // Get edges list of given ID node

                if (edges_list.empty()) {   // no adjacent nodes so print blank line
                    cout << endl;
                    return;
                }

                for (int j=0; j<edges_list.size(); j++) {   // Iterate through the adjacent nodes
                    cout << get<0>(edges_list[j])->get_entity_id() << " ";   // Print all IDs with a space in between
                }
                cout << endl;
            }
        }

        if (!node_in_graph) {
            cout << "failure" << endl; // node with given ID not in graph so failure
        }
    }

    catch (illegal_exception) {
        cout << "illegal argument" << endl;
    }
}


// Delete node with ID "ID" and any edges that contain it
void Graph::delete_node(string ID) {
    try {
        check_input_characters_exception(ID);
        
        // Find the node to delete
        bool node_in_graph = false;

        for (int i=0; i<entity_nodes_list.size(); i++) {
            if (entity_nodes_list[i]->get_entity_id() == ID) {   // Node is in graph
                node_in_graph = true;

                Node_Entity * target_node = entity_nodes_list[i];

                for (int j=0; j<entity_nodes_list.size(); j++) {
                    entity_nodes_list[j]->delete_edge(target_node); // delete edges from other nodes to target node
                }

                delete target_node;     // delete node memory
                entity_nodes_list.erase(entity_nodes_list.begin() + i); // remove node from node list (= deleted from graph)
            }
        }
        
        if (!node_in_graph) {  // node is not in graph
            cout << "failure" << endl;
        }
        else {
            cout << "success" << endl; // node found and deleted from graph
        }
    }

    catch (illegal_exception) {
        cout << "illegal argument" << endl;
    }
}


// Print nodes and labels along highest weight path between 2 nodes
void Graph::highest_weight_path(string ID_1, string ID_2) {
    try {
        check_input_characters_exception(ID_1);
        check_input_characters_exception(ID_2);
        
        // Node_Entity * source_node = nullptr;      // pointer to source node
        // Node_Entity * destination_node = nullptr; // pointer to desitination node
        // int source_node_index;
        // int destination_node_index;

        // bool source_node_in_graph = false;
        // bool destination_node_in_graph = false;

        // bool edge_in_graph = false;

        // for (i=0; i<entity_nodes_list.size(); i++)  {
        //     if (ID_1 == (entity_nodes_list[i]->get_entity_id())) {  // Find the node corresponding to ID_1
        //         source_node = entity_nodes_list[i];
        //         source_node_in_graph = true;
        //         source_node_index = i;
        //     }

        //     if (ID_2 == (entity_nodes_list[i]->get_entity_id())) {  // Find the node corresponding to ID_2
        //         destination_node = entity_nodes_list[i];
        //         destination_node_in_graph = true;
        //     }
        // }

        // if (!((source_node_in_graph == true) && (destination_node_in_graph == true))) { // source or destination node DNE in graph
        //     cout << "failure" << endl;
        //     return;
        // }

        // // DIJKSTRA'S ALGORITHM:
        // // Each element in each vector represents a node
        // vector<int> parent_list(entity_nodes_list.size(), -1);  // each element represents a node and holds its parents (used to create path later)
        // vector<double> distance_list(entity_nodes_list.size(), INFINITY); // Create vector of type double with size of total nodes
        //                                                                   // all elements initialized to infinity
        // vector<bool> visited_node_list(entity_nodes_list.size(), false); // Create vector of type bool with size of total nodes
        //                                                                  // all elements initialized to false since no nodes visited yet
        
        // distance_list[source_node_index] = 0;   // set distance of source node to 0
    }

    catch (illegal_exception) {
        cout << "illegal argument" << endl;
    }
}


// Get 2 nodes with highest weight path between them
void Graph::highest_weight_nodes() {
    if (!entity_nodes_list.empty()) {
        string source_node = "";
        string destination_node = "";
        double max_path_weight = -INFINITY; //initialize max weight to -infinity since we want the max weight (easier for comparison)

        // DFS for each node:
        for (int i=0; i< entity_nodes_list.size(); i++) {
            vector <bool> visited_nodes(entity_nodes_list.size(), false); //visited_nodes vector of size of total nodes; all elements init to false
            DFS_highest_weight_nodes(entity_nodes_list[i], 0, &max_path_weight, visited_nodes, &source_node, entity_nodes_list[i]->get_entity_id(), &destination_node);
        }

        if (max_path_weight == -INFINITY) {
            cout << "failure" << endl;   // No paths found (disconnected nodes)
        } else {
            cout << source_node << " " << destination_node << " " << max_path_weight << endl;
        }
    }

    else {
        cout << "failure" << endl;  // graph is empty or no edges
    }
}

// Helper function to implement DFS for highest_weight_nodes()
void Graph::DFS_highest_weight_nodes(Node_Entity* current_node, double current_weight, double *max_path_weight, vector <bool> visited_nodes, string *source_node, string source_node_id, string *destination_node) {
    int current_node_index;
    for (int i=0; i<entity_nodes_list.size(); i++) {
        if (current_node ==entity_nodes_list[i]) {   // get current_node's index in node list
            current_node_index = i;
        }
    }
    visited_nodes[current_node_index] = true;  // current node flagged as visited


    vector < tuple < Node_Entity *, double, string > > edges_list = current_node->get_edges_list();  // get list of adjacent nodes for current node

    for (int i=0; i<edges_list.size(); i++) {
        double edge_weight = get<1>(edges_list[i]);      // Weight of edge is index 1 of tuple
        Node_Entity * adjacent_node =  get<0>(edges_list[i]);   // Pointer to adjacent nodes is index 0 of tuple
        
        int adjacent_node_index;
        for (int j=0; j<entity_nodes_list.size(); j++) {
            if (adjacent_node == entity_nodes_list[j]) {
                adjacent_node_index = j;
            }
        }

        if (!visited_nodes[adjacent_node_index]) {  // Go through all adjacent nodes until they are all visited
            double new_weight = current_weight + edge_weight;

            if (new_weight > *max_path_weight) {  // if new_weight is max then update values of source/destination nodes and max weight
                *source_node = source_node_id;
                *destination_node = adjacent_node->get_entity_id();
                *max_path_weight = new_weight;
            }

            DFS_highest_weight_nodes(adjacent_node, new_weight, max_path_weight, visited_nodes, source_node, source_node_id, destination_node); // Recursive call for adjacent node
        }
    }

}


// Print all node id's w/ given field string
    // field_type = "name" or "type"
    // FINDALL name Mike_Cooper_Stachowsky
    // FINDALL type instructor
void Graph::find_all_nodes(string field_type, string field_string) {
    bool target_id_in_graph = false;

    for (int i=0; i<entity_nodes_list.size(); i++) {
        Node_Entity * node = entity_nodes_list[i];

        if (field_type == "name") {
            if (field_string == node->get_entity_name()) {  // given field string found
                target_id_in_graph = true;
                cout << node->get_entity_id() << " ";   // print the target node's id
            }
        }

        else if (field_type == "type") {
            if (field_string == node->get_entity_type()) {  // given field string found
                target_id_in_graph = true;
                cout << node->get_entity_id() << " ";   // print the target node's id
            }
        }
    }

    if (target_id_in_graph) {
        cout << endl;
    }

    else {
        cout << "failure" << endl;
    }
}