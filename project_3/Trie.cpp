#include "Trie.h"
#include "ece250_socket.h"
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


// Helper function for INSERT, CLASSIFY, ERASE to check for capital letters
void check_capital_letter_exception(string classification_string) {
    string alphabet_capital = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i=0; i < (classification_string.size()); i++) {
        for (int j=0; j < (alphabet_capital.size()); j++) {
            if ((classification_string[i]) == (alphabet_capital[j])) {  // Check for capital letters
                throw illegal_exception();  // Throw exception if capital letter detected (try-catch block)
            }
        }
    }
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

        // Parse through classification string by using commas as the delimiter and traverse trie
        while (getline(stream, classification_string, ',')) {
            check_capital_letter_exception(classification_string);  // Throw exception if captial letter found in helper function

            // Traverse children to see if classification has already been added to the trie
            bool classification_exists = false;
            for (int i=0; i < (current->children.size()); i++) {
                // If classification already exists (current node's child has value of classification_string), move into that child node
                if (current->children[i]->node_value() == classification_string) {
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
void Trie::classify_input(string input) {
    try {
        Node* current = root;  // Start at trie's root node
        istringstream stream(input); // input string
        string classification_string;   // Used to store parts of the input
        string output = "";  // Final classification result

        // Parse through string by using commas as the delimiter and traverse trie
        while (getline(stream, classification_string, ',')) {
            check_capital_letter_exception(classification_string);  // Throw exception if captial letter found in helper function

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

            //Append classification string to outpt
            if (output != "") {
                output += ",";
            }
            output += classification_string;
        }

        // Get classifications of current node's children
        string classifications = "";
        for (int i = 0; i < current->children.size(); i++) {
            if (i>0) {
                classifications += ",";  // comma between classifications
            }
            classifications += current->children[i]->node_value();
        }

        // Get classified output from the classifiern and add it to the output
        if (classifications != ""){
            string classifier_classification = labelText(input, classifications);
            output += "," + classifier_classification;
        }

        cout << output << endl;
    } 
    
    catch (illegal_exception) {
        cout << "illegal argument" << endl;  // if capital letters aredetected in classification
    }
}


// ERASE (remove) classification and its children
void Trie::erase_classification(string classification) {
    try {
        if (is_trie_empty()) {  // Failure if empty trie
            cout << "failure" << endl;
            return;
        }

        Node* current = root;  // Start at trie's root node
        istringstream stream(classification); // Classification string
        string classification_string;   // store extracted parts of the classification input
        vector<Node*> visited_path;    // Store visited nodes
        vector<int> child_indexes; // Store the index of each node in the children vector

        // Parse through classification string by using commas as the delimiter and traverse trie
        while (getline(stream,classification_string,',')) {
            check_capital_letter_exception(classification_string);  // Throw exception if captial letter found in helper function

            bool classification_exists = false;
            for (int i=0; i < (current->children.size()); i++) {
                // If classification already exists
                if (current->children[i]->node_value() == classification_string) {
                    visited_path.push_back(current); // Store current node
                    child_indexes.push_back(i);      // store current child's index
                    current = current->children[i];  // Move to chil node
                    classification_exists = true;    // Classifiation exists
                    break;
                }
            }

            if (!classification_exists) {   // classification does not exist in the trie so failure
                cout << "failure" << endl;
                return;
            }
        }

        // if the current node is not a terminal node, then it is not a complete path, so failure
        if (!current->is_terminal_node()) {
            cout << "failure" << endl;
            return;
        }

        // Remove terminal node if it is the terminal node
        current->set_terminal_node(false);
        //delete current;

        // Backtrack and remove nodes that are not needed
        for (int i = (visited_path.size() -1); i>=0; i--) {   // LOop backwards through visited nodes
            Node* parent = visited_path[i];   // Parent of the current node
            int child_index = child_indexes[i];   // Index of current node in the children vector of its parent

            if (current->children.empty() && !current->is_terminal_node()) {   // Children vecotr empty and node is not a terminal node
                delete parent->children[child_index]; // Delete current child node
                parent->children.erase(parent->children.begin() + child_index);  // Remove from the children's vector
                current = parent; // Go to its parent
            } else {
                break; // break if node has children or is a terminal node
            }
        }

        size--;
        cout << "success" << endl;
    }

    catch (illegal_exception) {
        cout << "illegal argument" << endl;   // If capital letters detected in classification
    }
}


// Helper function for print_classifications()
void Trie::find_classification_path(Node* node, string current_path, vector<string> all_paths) {
    if (node->is_terminal_node()) {
        all_paths.push_back(current_path);  // Add the terminal node's (current node) classification path to the all_paths vector
    }

    // Loop through all the children of the current node
    for (int i = 0; i < node->children.size(); i++) {
        string path_child;  // store the current child's classification path

        if (current_path == "") {   // the root
            path_child = node->children[i]->node_value();  // Initialize path with the root's child
        } else {
            path_child = current_path + "," + node->children[i]->node_value();   // add child's value to the current path if not at root
        }

        find_classification_path(node->children[i], path_child, all_paths);   // get all classification paths for the child recursively 
                                                                              // start at child node and current path is updated to the child's path
    }

}

// PRINT all classifications in trie
void Trie::print_classifications() {
    if (is_trie_empty()) {
        cout << "trie is empty" << endl;
    }

    else {
        vector<string> all_paths;
        find_classification_path(root,"", all_paths);  // Get all classification paths starting from root node

        string output_str = "";  // tore all formatted classifications to print
        for (int i = 0; i < all_paths.size(); i++) {
            if (i>=1) {
                output_str += "_";  // Adds an underscore after each classification
            }
            output_str += all_paths[i];  // Add current path to the final output string
        }

        cout << output_str << endl;
    }
}


// Check if trie is EMPTY
bool Trie::is_trie_empty() {
    if (root->children.empty()) {   // Empty when root has no children
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