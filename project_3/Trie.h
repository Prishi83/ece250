#ifndef TRIE_H
#define TRIE_H

#include "Node.h"
#include "illegal_exception.h"
#include <string>
#include <vector>
using namespace std;

class Trie {
private:
    Node* root;   // Root node of trie
    int size;   // # of classifications in trie

    // Node* findNode(string classification); // Helper to find a node for a classification

    // // Helper function to check for invalid characters (uppercase letters in this case)
    // bool hasInvalidCharacter(string input);

public:
    Trie();   // Constructor
    ~Trie();  // Destructor

    void load_input(string filename);  // LOAD classifications from an input file
    void insert_classification(string classification);  // INSERT classification into trie
    void classify_input(string input);  // CLASSIFY input string using trie
    void erase_classification(string classification);   // ERASE (remove) classification and its children
    void find_classification_path(Node* node, string current_path, vector<string> all_paths);   // Helper function for PRINT
    void print_classifications();   // PRINT all classifications in trie
    bool is_trie_empty();  // Check if trie is EMPTY
    void clear_all_nodes();   // Remove (CLEAR) all nodes from trie
    int return_trie_size();   // Return SIZE of trie
};

#endif
