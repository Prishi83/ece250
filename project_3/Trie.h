#ifndef TRIE_H
#define TRIE_H

#include "Node.h"
#include <string>
#include <vector>
using namespace std;

class Trie {
private:
    Node* root;      // Root node of the trie
    int size;        // Number of classifications in the trie

    Node* findNode(string classification); // Helper to find a node for a classification

    // Helper function to check for invalid characters (uppercase letters in this case)
    bool hasInvalidCharacter(string input);

public:
    Trie();                       // Constructor
    ~Trie();                      // Destructor

    bool insert(string classification); // Inserts a classification into the trie
    bool erase(string classification);  // Removes a classification and its descendants
    string classify(string input); // Classifies an input using the trie
    string print();          // Returns all classifications in the trie
    bool isEmpty();               // Checks if the trie is empty
    void clear();                 // Clears all nodes from the trie
    int getSize();                // Returns the size of the trie
    void loadFromFile(string filename); // Loads classifications from a file
};

#endif
