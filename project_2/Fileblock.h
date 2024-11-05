// Manages data in each individual file block (stores ID, data, and computes checksum)

#ifndef FILEBLOCK_H
#define FILEBLOCK_H

#include <vector>
using namespace std;

// Class declaration
class Fileblock {
public:
    FileBlock(int id, char* payload);  // Constructor to initialize ID and payload data
    ~FileBlock();  // Destructor

    void set_payload(char* new_payload, bool updateChecksum = true);  // Set new data in payload (nullptr = zeros the array) and option to recompute checksum
    int get_id() const;  // Returns ID of the file block
    bool compare_new_checksum() const;  // Generate new checksum and check for corruption by comparing it with the existing checksum

private:
    int id;  // Unique ID for file block
    char payload[501] = {};  // Fixed array that can store max 500 characters (501th char is '/0') and is initialized to 0
    int compute_checksum() const;  // Helper function to calculate checksum
    int checksum;  // Checksum to check if data is corrupted or not
};

#endif
