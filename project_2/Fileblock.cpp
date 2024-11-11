// Manages data in each individual file block (stores ID, data and computes checksum)

#include "Fileblock.h"
#include <iostream>
#include <vector>
using namespace std;

// Constructor Definition
Fileblock::Fileblock(int id_input, char* payload_input) {
    id = id_input;  // Initialize id with input parameter
    checksum = 0;

    for (int i=0; i < 500; i++) {           // Initialize payload array with the payload input parameter by copying each character
        payload[i] = payload_input[i];
        if (payload_input[i] == '\0') {
            break;
        }
    }
    checksum = compute_checksum();  // Initial checksum for the file block
}


// Destructor definition: nothing to free since no dynamically allocated memory
Fileblock::~Fileblock() {
}


// Compute the checksum by sum of the ASCII values of the payload characters modulo 256
int Fileblock::compute_checksum() {
    int payload_chars_sum = 0;   // Add up the ASCII values of the characters in the payload
    for (int i=0; (i < 500) && (payload[i] != '\0'); i++) {
        payload_chars_sum += payload[i];    // Directly add the chars since += will automatically add the ASCII value of each char
    }
    return payload_chars_sum % 256;
}


// Used to corrupt the file block (used in Hashtable.cpp)
// Sets new data for the payload and gives the option to update the checksum
void Fileblock::set_payload(char* new_payload, bool updateChecksum) {
    // Zero the array of chars (payload) if new_payload = nullptr
    if (new_payload == nullptr) {
        for (int i=0; i<500; i++) {
            payload[i] = '\0';
        }
    }
    else {
        for (int i = 0; i < 500; i++) {     // Populate payload array with the new payload data by copying each character
            payload[i] = new_payload[i];
            if (new_payload[i] == '\0') {
                break;
            }
        }
    }

    if (updateChecksum) {
        checksum = compute_checksum();  // Recalculate checksum if input parameter is true
    }
}


int Fileblock::get_id() {  // id = private member of Fileblock class, so this method needed to use id in Hashtable class
    return id;
}


// Generate new checksum and check for corruption by comparing it with the existing checksum
bool Fileblock::compare_new_checksum() {
    if (compute_checksum() == checksum) {
        return true;
    }
    else {
        return false;
    }
}