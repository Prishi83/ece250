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

};

// INSERT classification into trie
bool Trie::insert(string classification) {

}


// CLASSIFY input string using trie
string Trie::classify(string input) {

}


// ERASE (remove) classification and its children
bool Trie::erase(string classification) {

}


// PRINT all classifications in trie
string Trie::print() {

}


// Check if trie is EMPTY
bool Trie::is_Empty() {

}


// Remove (CLEAR) all nodes from trie
void Trie::clear() {

}


// Return SIZE of trie
int Trie::return_size() {

}