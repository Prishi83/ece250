// Manages data storage (finds index for each file block and handles collision)

#include "Hashtable.h"
#include <iostream>
#include <vector>
using namespace std;

// Constructor Definition
Hashtable::Hashtable() {
    hashtable_size = 0;
    hash_func_type = 0;
}


// Destructor definition
Hashtable::~Hashtable() {
    for (int i = 0; i < hashtable_size; i++) {
        delete hash_table[i];     // Memory for each FileBlock freed and pointers set to nullptr
        hash_table[i] = nullptr;
    }
}


int Hashtable::hash_func_1(int key) const {
    return key % hashtable_size;
}


int Hashtable::hash_func_2(int key) const {
    int result = (key/hashtable_size) % hashtable_size;
    if (result % 2 == 0) {  // Add 1 if result is an even number (only want odd numbers)
        result++;
    }
    return result;
}


void Hashtable::new_hashtable(int N, int T) {
    hash_func_type = T;   // Type of hashing (0 = open addressing; 1 = separate chaining)
    hashtable_size = N;   // Size of hash table
    hash_table.clear();   // Remove any existing elements in the vector
    hash_table.resize(N, nullptr);   // N is the size of the vector (hash_table) and each element (slot) is set to nullptr
    cout << "success" << endl;
}


// access id of the FileBlock at the index
void Hashtable::store_file_block(int ID, char* payload) {
    int func1_index = hash_func_1(ID);  // File block's primary index from hash function 1
    int func2_index = hash_func_2(ID);  // Offset from hash function 2 to find next available spot
    
    // Open addressing - Double hashing:
    if (hash_func_type == 0) {
        int i = 0;    // Number of double hashing attempts
        new_index = func1_index;

        // Probe hash table until an empty spot is found where a new file block can be inserted
        // != nullptr means the slot is occupied
        // != ID means there is a collision, so probe to find next slot; the same ID means it's a duplicate so stop probing
        while (hash_table[new_index] != nullptr && (*hash_table[new_index]).get_id() != ID) {
            i++;
            new_index = (func1_index + (i * func2_index)) % hashtable_size; // Double hashing to find new index for probing next slot

            // Check if the table is full (full if you loop back to the start)
            if (new_index == func1_index) {
                cout << "failure" << endl;
                return;
            }
        }
        if (hash_table[new_index] == nullptr) {    // Insert new file block when an empty slot is found
            hash_table[new_index] = new Fileblock(ID, payload);
            cout << "success" << endl;
        }
        else {    // if ID already exists in hashtable (don't want to add duplicates)
            cout << "failure" << endl;
        }
    }

    // Separate chaining:
    else if (hash_func_type == 1) {
        bool ID_found = false;

        // Check if ID is already in the slot
        for (j = 0; j < hash_table[func1_index].size; j++) {  // Loop through chain in the slot to compare each ID in the chain with the key
            if ((*hash_table[func1_index][j]).get_id() == ID) {   // ID exists in the chain
                ID_found = true;
                break;
            }
        }

        if (ID_found) {
            cout << "failure" << endl;  // ID already exists, so failure since we don't want duplicates
        } 
        else {
            hash_table[func1_index].push_back(new FileBlock(ID, payload)); // New file block added to back of the chain since ID does not already exist
            cout << "success" << endl;
        }
    }
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