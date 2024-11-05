// Manages data in each individual file block (stores ID, data, and computes checksum)

#ifndef FILEBLOCK_H
#define FILEBLOCK_H

// Class declaration
class Fileblock {
public:
    Fileblock(int id, char* payload);  // Constructor to initialize ID and payload data
    ~Fileblock();  // Destructor

    void set_payload(char* new_payload, bool updateChecksum = true);  // Set new data in payload (nullptr = zeros the array) and option to recompute checksum
    int get_id();  // Returns ID of the file block
    bool compare_new_checksum();  // Generate new checksum and check for corruption by comparing it with the existing checksum

private:
    int id;  // Unique ID for file block
    char payload[501];  // Payload array that can store max 500 characters (501th char is '/0')
    int compute_checksum();  // Helper function to calculate checksum
    int checksum;  // Checksum to check if data is corrupted or not
};

#endif
