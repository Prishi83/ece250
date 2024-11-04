// Manages data in each individual file block (stores ID, data, and computes checksum)

#ifndef FILEBLOCK_H
#define FILEBLOCK_H

#include <vector>
using namespace std;

// Class declaration
class Fileblock {
public:
    FileBlock(int id, char* data);  // Constructor to initialize ID and data
    ~FileBlock();  // Destructor

    void set_data(char* data, bool updateChecksum = true);  // Set new data, optionally update checksum
    int get_id() const;  // Returns ID of the file block
    bool validate_checksum() const;  // Validate checksum to check for corruption

private:
    int id;  // Unique ID for file block
    char data[501];  // Fixed array that can store max 500 characters
    int compute_checksum() const;  // Helper function to calculate checksum
    int checksum;  // Checksum for verifying data integrity
};

#endif
