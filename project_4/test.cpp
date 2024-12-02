#include <iostream>
#include <string>
#include "Graph.h" // Include the Graph header file
using namespace std;

int main() {
    Graph graph;   // Create an object of the Graph class
    string command;   // Store input command

    while (cin >> command) {
        if (command == "LOAD") {
            string filename;
            string type;    // will be either "entities" or "relationships"
            cin >> filename;
            cin >> type;

            graph.load_dataset(filename, type);
            cout << "success" << endl;
        }

        else if (command == "RELATIONSHIP") {
            string source_ID;
            string label;
            string destination_ID;
            double weight;
            cin >> source_ID;
            cin >> label;
            cin >> destination_ID;
            cin >> weight;

            graph.insert_relationship_edge(source_ID, label, destination_ID, weight);
        }

        else if (command == "ENTITY") {
            string ID;
            string name;
            string type;
            cin >> ID;
            cin >> name;
            cin >> type;
            
            graph.insert_entity_node(ID, name, type);
            cout << "success" << endl;
        }

        else if (command == "PRINT") {
            string ID;
            cin >> ID;

            graph.print_adjacent_nodes(ID);
        }

        else if (command == "DELETE") {
            string ID;
            cin >> ID;
            graph.delete_node(ID);  // delete node with ID "ID" and any edges that contain it
        }

        else if (command == "PATH") {
            string ID_1;
            cin >> ID_1;
            string ID_2;
            cin >> ID_2;
            graph.highest_weight_path(ID_1, ID_2);  // print nodes and labels along highest weight path b/w 2 nodes
        }

        else if (command == "HIGHEST") {
            graph.highest_weight_path_nodes();  // print 2 nodes with highest weight path b/w them
        }

        else if (command == "FINDALL") {
            string field_type;  // "name" or "type"
            cin >> field_type;
            string field_string;
            cin >> field_string;
            graph.find_all_nodes(field_type, field_string);  // print all nodes w/ given field str
        }

        else if (command == "EXIT") {
            break;
        }
    }

    return 0;
}