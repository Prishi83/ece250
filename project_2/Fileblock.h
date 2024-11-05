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

    void set_payload(char* payload, bool updateChecksum = true);  // Set new data, optionally update checksum
    int get_id() const;  // Returns ID of the file block
    bool compute_new_checksum() const;  // Generate new checksum to check for corruption by comparing with existing checksum

private:
    int id;  // Unique ID for file block
    char payload[501];  // Fixed array that can store max 500 characters
    int compute_checksum() const;  // Helper function to calculate checksum
    int checksum;  // Checksum for verifying data integrity
};

#endif
