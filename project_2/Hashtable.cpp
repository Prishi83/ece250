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
        for (int j = 0; j < hash_table[i].size(); j++) {  // Free memory for each Fileblock in the chains
            delete hash_table[i][j];
            hash_table[i][j] = nullptr;
        }
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
    hash_table.resize(N);   // N is the size of the vector (hash_table)
    cout << "success" << endl;
}


void Hashtable::store_file_block(int ID, char* payload) {
    int func1_index = hash_func_1(ID);  // File block's primary index from hash function 1
    int func2_index = hash_func_2(ID);  // Offset from hash function 2 to find next available spot
    
    // Open addressing - Double hashing:
    if (hash_func_type == 0) {
        int i = 0;    // Number of double hashing attempts
        int new_index = func1_index;

        // Probe hash table until an empty spot is found where a new file block can be inserted
        // != nullptr means the slot is occupied
        // != ID means there is a collision, so probe to find next slot; the same ID means it's a duplicate so stop probing
        while ((hash_table[new_index] != nullptr) && ((*hash_table[new_index]).get_id() != ID)) {
            i++;
            new_index = (func1_index + (i * func2_index)) % hashtable_size; // Double hashing to find new index for probing next slot

            if (new_index == func1_index) {  // Check if the table is full (full if you loop back to the start)
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
        for (int j = 0; j < hash_table[func1_index].size; j++) {  // Loop through chain in the slot to compare each ID in the chain with the key
            if ((*hash_table[func1_index][j]).get_id() == ID) {   // ID exists in the chain
                ID_found = true;
                break;
            }
        }

        if (ID_found) {
            cout << "failure" << endl;  // ID already exists, so failure since we don't want duplicates
        } 
        else {
            hash_table[func1_index].push_back(new Fileblock(ID, payload)); // New file block added to back of the chain since ID does not already exist
            cout << "success" << endl;
        }
    }
}


void Hashtable::search_file_block(int ID) {
    int func1_index = hash_func_1(ID);  // File block's primary index from hash function 1
    int func2_index = hash_func_2(ID);  // Offset from hash function 2 to find next available spot

    // Open addressing - Double hashing:
    if (hash_func_type == 0) {  
        int i = 0;
        int new_index = func1_index;
        
        while ((hash_table[new_index] != nullptr) && ((*hash_table[new_index]).get_id() != ID)) {
            i++;
            new_index = (func1_index + (i * func2_index)) % hashtable_size; // Double hashing to find new index for probing next slot

            if (new_index == func1_index) {
                break;
            }
        }

        if ((hash_table[new_index] != nullptr) && ((*hash_table[new_index]).get_id() == ID)) {
            cout << "found " << ID << " in " << new_index << endl;
        } else {
            cout << "not found" << endl;
        }
    }

    // Separate chaining:
    else {
        for (int j = 0; j < hash_table[func1_index].size(); j++) {
            if ((*hash_table[func1_index][j]).get_id() == ID) {
                cout << "found " << ID << " in " << func1_index << endl;
                return;
            }
        }
        cout << "not found" << endl;
    }
}


void Hashtable::delete_file_block(int ID) {
    int func1_index = hash_func_1(ID);  // File block's primary index from hash function 1
    int func2_index = hash_func_2(ID);  // Offset from hash function 2 to find next available spot
    
    // Open addressing - Double hashing:
    if (hash_func_type == 0) {
        int i = 0;    // Number of double hashing attempts
        int new_index = func1_index;

        // Probe hash table until an empty spot is found
        // != nullptr means the slot is occupied
        // != ID means there is a collision, so probe to find next slot; the same ID means it's a duplicate so stop probing
        while ((hash_table[new_index] != nullptr) && ((*hash_table[new_index]).get_id() != ID)) {
            i++;
            new_index = (func1_index + (i * func2_index)) % hashtable_size; // Double hashing to find new index for probing next slot

            if (new_index == func1_index) {  // Check if the table is full (full if you loop back to the start)
                break;
            }
        }
        if ((hash_table[new_index] != nullptr) && ((*hash_table[new_index]).get_id() == ID)) {
            delete hash_table[new_index];
            hash_table[new_index] = nullptr;
            cout << "success" << endl;
        }
        else {    // if ID does not exist in hashtable
            cout << "failure" << endl;
        }
    }

    // Separate chaining:
    else if (hash_func_type == 1) {
        // Check if ID is already in the slot
        for (int j = 0; j < hash_table[func1_index].size; j++) {  // Loop through chain in the slot to compare each ID in the chain with the key
            if ((*hash_table[func1_index][j]).get_id() == ID) {   // ID exists in the chain
                delete hash_table[func1_index][j];
                hash_table[func1_index].erase(hash_table[func1_index].begin() + j);
                hash_table[func1_index] = nullptr;
                cout << "success" << endl;
                return;
            }
        }
        cout << "failure" << endl;
    }
}


void Hashtable::corrupt_file_block(int ID, char* payload) {
    int func1_index = hash_func_1(ID);  // File block's primary index from hash function 1
    int func2_index = hash_func_2(ID);  // Offset from hash function 2 to find next available spot

    // Open addressing - Double hashing:
    if (hash_func_type == 0) {
        int i = 0;    // Number of double hashing attempts
        int new_index = func1_index;

        // Probe hash table until an empty spot is found
        // != nullptr means the slot is occupied
        // != ID means there is a collision, so probe to find next slot; the same ID means it's a duplicate so stop probing
        while ((hash_table[new_index] != nullptr) && ((*hash_table[new_index]).get_id() != ID)) {
            i++;
            new_index = (func1_index + (i * func2_index)) % hashtable_size;

            if (new_index == func1_index) {  // Check if the table is full (full if you loop back to the start)
                cout << "failure" << endl;
                return;
            }
        }

        if ((hash_table[new_index] != nullptr) && ((*hash_table[new_index]).get_id() == ID)) {
            (*hash_table[new_index]).set_payload(nullptr, false);  // Set all chars in payload to nullptr ('\0' or 0)
            (*hash_table[new_index]).set_payload(payload, false);  // Set new payload without calculating checksum
            cout << "success" << endl;
        } 
        else {
            cout << "failure" << endl;
        }
    }

    // Separate chaining:
    else if (hash_func_type == 1) {
        for (int j = 0; j < hash_table[func1_index].size(); j++) {  // Loop through chain in the slot to compare each ID in the chain with the key
            if ((*hash_table[func1_index][j]).get_id() == ID) {   // ID exists in the chain
                (*hash_table[func1_index][j]).set_payload(nullptr, false);  // Set all chars in payload to zero ('\0')
                (*hash_table[func1_index][j]).set_payload(payload, false);  // Set new payload without calculating checksum
                cout << "success" << endl;
                return;
            }
        }
        cout << "failure" << endl;
    }
}


void Hashtable::validate_file_block(int ID) {
    int func1_index = hash_func_1(ID);  // File block's primary index from hash function 1
    int func2_index = hash_func_2(ID);  // Offset from hash function 2 to find next available spot

    // Open addressing - Double hashing:
    if (hash_func_type == 0) {
        int i = 0;
        int new_index = func1_index;

        // Probe hash table until the ID is found
        while ((hash_table[new_index] != nullptr) && ((*hash_table[new_index]).get_id() != ID)) {
            i++;
            new_index = (func1_index + (i * func2_index)) % hashtable_size;

            if (new_index == func1_index) {  // Check if the table is full (full if you loop back to the start)
                cout << "failure" << endl;
                return;
            }
        }

        // Check if the ID is at new_index
        if ((hash_table[new_index] != nullptr) && ((*hash_table[new_index]).get_id() == ID)) {
            if ((*hash_table[new_index]).compare_new_checksum()) {    // Check the checksum for the file block
                cout << "valid" << endl;    // File block with given ID exists, and its checksum matches  the new computed checksum
            } 
            else {
                cout << "invalid" << endl;  // File block with given ID exists, but its checksum does not match the new computed checksum 
            }
        } else {
            cout << "failure" << endl;
        }
    }

    // Separate chaining:
    else if (hash_func_type == 1) {
        // Loop through the chain to find the ID
        for (int j = 0; j < hash_table[func1_index].size(); j++) {
            if ((*hash_table[func1_index][j]).get_id() == ID) {
                if ((*hash_table[func1_index][j]).compare_new_checksum()) {    // Check the checksum for the file block
                    cout << "valid" << endl;    // File block with given ID exists, and its checksum matches  the new computed checksum
                } else {
                    cout << "invalid" << endl;  // File block with given ID exists, but its checksum does not match the new computed checksum 
                }
                return;
            }
        }
        cout << "failure" << endl;  // no file block exists with given ID
    }
}


void Hashtable::print(int i) {
    if (hash_table[i].empty()) {    // Chain at index i is empty
        cout << "chain is empty" << endl;
    }
    else if (i >= 0 && i < hashtable_size) {    // Chain at index i is within the bounds, print out the IDs
        for (int id = 0; id < hash_table[i].size(); id++) {
            cout << (*hash_table[i][id]).get_id() << " ";
        }
        cout << endl;
    }
    else {    // Chain at index i is out of bounds
        cout << "failure" << endl;
    }
}