// Manages data in each file block (stores data and computes checksum)

#include "Fileblock.h"
#include <iostream>
#include <vector>
using namespace std;

// Constructor Definition
Fileblock::FileBlock(int id_input, char* data_input) {
    id = id_input;  // Initialize id with input parameter

    for (int i=0; i<500; i++) {           // Initialize data array with input parameter by copying each character
        if (data_input[i] == '\0') {
            data[i] = '\0';  
            break;
        }
        data[i] = data_input[i];        
    }
    checksum = compute_checksum();
}


// Destructor Definition: nothing to free since no dynamically allocated memory
Fileblock::~FileBlock() {
}


int Fileblock::compute_checksum() const {
    return 0;
}


void Fileblock::set_data(char* data, bool updateChecksum = true) {
    
}


int Fileblock::get_id() const {
    return id;
}


bool Fileblock::validate_checksum() const {
    return true;
}