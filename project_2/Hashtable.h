// Manages data storage (finds index for each file block and handles collision)

#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "Fileblock.h"
#include <vector>
using namespace std;

// Class declaration
class Hashtable {
public:
    Hashtable();   // Constructor
    ~Hashtable();  // Destructor

    void new_hashtable(int N, int T);  // Initialize new hash table with size N and type T
    void store_file_block(int ID, char* payload);  // Store a file block with given ID and payload
    void search_file_block(int ID);  // Search for a file block in the hash table using its ID
    void delete_file_block(int ID);  // Deletes a file block from the hash table using its ID
    void corrupt_file_block(int ID, char* payload);  // Corrupt a file block by replacing it w/ new data w/o updating checksum
    void validate_file_block(int ID);  // Validate the checksum of a file block, given its ID
    void print(int i);  // Only for separate chaining: Print chain of IDs that start at specified index (i)

private:
    int hashtable_size;  // Size of hash table
    int hash_type;   // Type of hashing (0 = open addressing; 1 = chaining)
    vector<FileBlock*> hash_table; // Vector ("hash_table") of pointers (dynamic array used to rep. hash table)
                                   // Each entry is a slot in the hash_table
                                   // Each element is a pointer to a Fileblock instance (dynamically allocate FileBlock objects)
                                   // Empty slots rep. by nullptr
    int hash_func_1(int key) const;  // Primary hash function
    int hash_func_2(int key) const;  // Secondary hash function for double hashing
};

#endif