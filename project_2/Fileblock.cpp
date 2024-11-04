// Manages data in each individual file block (stores ID, data, and computes checksum)

#include "Fileblock.h"
#include <iostream>
#include <vector>
using namespace std;

// Constructor Definition
Fileblock::FileBlock(int id_input, char* payload_input) {
    id = id_input;  // Initialize id with input parameter

    for (int i=0; i<500; i++) {           // Initialize payload array with input parameter by copying each character
        if (payload_input[i] == '\0') {
            payload[i] = payload_input[i];
            break;
        }
        payload[i] = payload_input[i];        
    }
    checksum = compute_checksum();
}


// Destructor definition: nothing to free since no dynamically allocated memory
Fileblock::~FileBlock() {
}


int Fileblock::compute_checksum() const {
    return 0;
}


void Fileblock::set_payload(char* payload, bool updateChecksum = true) {
    
}


int Fileblock::get_id() const {  // id = private member of Fileblock class, so method needed in order to use id in Hashtable class
    return id;
}


bool Fileblock::validate_checksum() const {
    return true;
}