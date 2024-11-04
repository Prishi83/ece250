// Manages data storage (finds index for each file block and handles collision)

#include "Hashtable.h"
#include <iostream>
#include <vector>
using namespace std;

// Constructor Definition
Hashtable::Hashtable() {
    hashtable_size = 0;
    hash_type = 0;
}


// Destructor definition
Hashtable::~Hashtable() {
    for (int i = 0; i < hashtable_size; i++) {
        delete hash_table[i];     // Free memory for each FileBlock
        hash_table[i] = nullptr;  // Set pointer to nullptr
    }
}


void Hashtable::new_hashtable(int N, int T) {
    
}


void Hashtable::store_file_block(int ID, char* payload) {
    
}


void Hashtable::search_file_block(int ID) {
    
}


void Hashtable::delete_file_block(int ID) {
    
}


void Hashtable::corrupt_file_block(int ID, char* payload) {
    
}


void Hashtable::validate_file_block(int ID) {
    
}


void Hashtable::print(int i) {
    
}


int Hashtable::hash_func_1(int key) const {
    return 0;
}


int Hashtable::hash_func_2(int key) const {
    return 0;
}