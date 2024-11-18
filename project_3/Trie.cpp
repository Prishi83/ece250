#include "Trie.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;


// Constructor definition
Trie::Trie() {
    root = new Node();
    size = 0;
}


// Destructor definition
Trie::~Trie() {
    delete root;    // delete all nodes
}


// LOAD classifications from an input file
void Trie::load_input(string filename) {
    ifstream file(filename);  // Open input file
    string line;

    if (file.is_open()) {
        while (getline(file, line)) {   // Read each line of the file
            Node* current = root;  // Start at trie's root node
            istringstream stream(line);  // Use stream to parse the line
            string classification_string;
            bool is_duplicate_classification = true;

            // Parse through classification string by using commas as the delimiter and traverse trie
            while (getline(stream, classification_string, ',')) {
                // Traverse children to see if classification has already been added to the trie
                bool classification_exists = false;
                for (int i=0; i < (current->children.size()); i++) {
                    // If classification already exists (current node's child has value of classification_string), move into that child node
                    if (current->children[i]->node_value() == classification_string) {
                        current = current->children[i];  // Move to that child node
                        classification_exists = true;
                        break; // break loop when classification_string is found
                    }
                }

                // If the classification_string does not exist in the trie, insert a new child node
                if (!classification_exists) {
                    is_duplicate_classification = false;  // not a duplicate classification
                    current->set_terminal_node(false);   // Set terminal node status to false since we will add a child to this node
                    Node* new_classification_node = new Node();
                    new_classification_node->set_node_value(classification_string);  // Set classsification as the new node's value
                    current->children.push_back(new_classification_node);  // Add new node to the children vector
                    current = new_classification_node;  // Move to new child node
                }

                // If the current node is a terminal node (last node in the classification path; has no chlidren) and is not a duplicate, mark it
                if (!is_duplicate_classification) {
                    current->set_terminal_node(true);
                    size++;  // Update trie size
                }      
            }      
        }
        file.close();
    }
};


// INSERT classification into trie
void Trie::insert_classification(string classification) {
    try {
        Node* current = root;  // Start at trie's root node
        istringstream stream(classification); // Classification string
        string classification_string;   // Used to store the extracted parts of the string input
        bool is_duplicate_classification = true;
        string alphabet_capital = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

        // Parse through classification string by using commas as the delimiter and traverse trie
        while (getline(stream, classification_string, ',')) {
            for (int i=0; i < (classification_string.size()); i++) {
                for (int j=0; j < (alphabet_capital.size()); j++) {
                    if ((classification_string[i]) == (alphabet_capital[j])) {  // Check for capital letters
                        throw illegal_exception();  // Throw exception if capital letter detected (try-catch block)
                    }
                }
            }

            // Traverse children to see if classification has already been added to the trie
            bool classification_exists = false;
            for (int i=0; i < (current->children.size()); i++) {
                // If classification already exists (current node's child has value of classification_string), move into that child node
                if (current->children[i]->node_value() == classification_string) { //&& current->children[i] != nullptr) {
                    current = current->children[i];  // Move to that child node
                    classification_exists = true;
                    break; // break when classification_string is found
                }
            }

            if (!classification_exists) {  // classification_string does not exist in the trie, so insert a new child node
                is_duplicate_classification = false;
                current->set_terminal_node(false);   // Set terminal node to false since we will add a child to this node
                Node* new_classification_node = new Node();
                new_classification_node->set_node_value(classification_string);  // Set the classification_string as the new node's value
                current->children.push_back(new_classification_node);  // Add new node to the children vector
                current = new_classification_node;  // Move to new child node
            }
        }

        // Check if current node is a duplicate classification and is a terminal node
        if (is_duplicate_classification && current->is_terminal_node()) {
            cout << "failure" << endl;
            return;
        }

        // Mark the terminal node if its not a dpulicate and it has no children
        if (!is_duplicate_classification) {
            current->set_terminal_node(true);   // Method implemented in Node class
            size++;  // Update trie's size
        }

        cout << "success" << endl;  // Insertion was successful
    }

    catch (illegal_exception) {
        cout << "illegal argument" << endl;   // Print if capital letters detected in classification
    }
}


// CLASSIFY input string using trie
string Trie::classify_input(string input) {

}


// ERASE (remove) classification and its children
bool Trie::erase_classification(string classification) {

}


// PRINT all classifications in trie
string Trie::print_classifications() {

}


// Check if trie is EMPTY
bool Trie::is_trie_empty() {
    if (root->children.empty()) {
        return true;
    }
    else {
        return false;
    }
}


// Helper function for clear_all_nodes() (recursive approach for O(N) time)
void delete_children(Node *node) {
    for (int i=0; i < node->children.size(); i++) {   // loop through children of the current node
        delete_children(node->children[i]);   // Delete all the children recursively ('node->children[i]' is the input parameter to the function)
        delete node->children[i];   // Meemory freed
    }
    node->children.clear();   // pointer to the node's children vector; use .clear() to clear all contents of this vector (children)
}

// Remove (CLEAR) all nodes from trie
void Trie::clear_all_nodes() {
    delete_children(root);   // Start deleting at the root (recursively delete all nodes in the helper function until only root is left)
    delete root;  // Delete root node
    size = 0;   // Set the size of the trie to 0 since it is cleared
    root = new Node();  // initialize a new root node
    cout << "success" << endl;
}


// Return SIZE of trie
int Trie::return_trie_size() {
    return size;
}