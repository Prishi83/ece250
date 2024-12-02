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
    // DO TRY-CATCH ERORR THING TO SEE IF ID INPUT IS VALID



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


// Delete node with ID "ID" and any edges that contain it
void Graph::delete_node(string ID) {
    // DO TRY-CATCH ERORR THING TO SEE IF ID INPUT IS VALID




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


// Get nodes and labels along highest weight path between 2 nodes
void Graph::highest_weight_path(string ID_1, string ID_2) {

}


// Get 2 nodes with highest weight path between them
void Graph::highest_weight_path_nodes() {

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




// Print the entire graph: all nodes and their edges
void Graph::print_graph() {
    for (int i = 0; i < entity_nodes_list.size(); i++) {
        Node_Entity* current_node = entity_nodes_list[i];
        cout << current_node->get_entity_id() << ": "; // Print the current node's ID

        vector<tuple<Node_Entity*, double, string>> edges_list = current_node->get_edges_list();
        for (int j = 0; j < edges_list.size(); j++) {
            Node_Entity* adjacent_node = get<0>(edges_list[j]);
            double weight = get<1>(edges_list[j]);
            string label = get<2>(edges_list[j]);

            cout << "(" << adjacent_node->get_entity_id() << ", " << label << ", " << weight << ")";
            if (j < edges_list.size() - 1) cout << " "; // Add space between edges
        }

        cout << endl; // Newline after each node's adjacency list
    }
}
