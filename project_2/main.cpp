#include <iostream>
#include "Hashtable.h"
using namespace std;

int main() {
    Hashtable hashtable;   // Create an object of the Hashtable class
    string command;   // Store input command
    
    while (cin >> command) {
        if (command == "NEW") {
            int N;
            int T;
            cin >> N >> T;

            hashtable.new_hashtable(N, T);
        }

        else if (command == "STORE") {
            int ID;
            char charstring[501];   // max 500 chars in array + '\0' (null terminator)
            
            char char_in;
            int i = 0;

            cin >> ID;
            // read character and add it to charstring array based on conditions
            while ((cin >> char_in) && (char_in!='!') && (i<500)) {
                charstring[i++] = char_in;
            }
            charstring[i] = '\0';

            hashtable.store_file_block(ID, charstring);
        }

        else if (command == "SEARCH") {
            int ID;
            cin >> ID;

            hashtable.search_file_block(ID);
        }

        else if (command == "DELETE") {
            int ID;
            cin >> ID;

            hashtable.delete_file_block(ID);
        }

        else if (command == "CORRUPT") {
            int ID;
            char charstring[501];   // max 500 chars in array + '\0' (null terminator)
            
            char char_in;
            int i = 0;

            cin >> ID;
            // read character and add it to charstring array based on conditions
            while ((cin >> char_in) && (char_in!='!') && (i<500)) {
                charstring[i++] = char_in;
            }
            charstring[i] = '\0';
            
            hashtable.corrupt_file_block(ID, charstring);
        }

        else if (command == "VALIDATE") {
            int ID;
            cin >> ID;

            hashtable.validate_file_block(ID);
        }

        else if (command == "PRINT") {
            int i;
            cin >> i;

            hashtable.print(i);
        }

        else if (command == "EXIT") {
            break;
        }
    }

    return 0;
}



    // vector<int> numbers;

    // // Adding elements
    // numbers.push_back(1);
    // numbers.push_back(2);
    // numbers.push_back(3);

    // // Accessing elements
    // cout << "First element: " << numbers[0] << endl;
    // cout << "Second element (using at()): " << numbers.at(1) << endl;

    // // Iterating over elements
    // cout << "Elements: ";
    // for (int num : numbers) {
    //     cout << num << " ";
    // }
    // cout << endl;

    // // Removing an element
    // numbers.pop_back();
    // cout << "After pop_back, size is: " << numbers.size() << endl;
    