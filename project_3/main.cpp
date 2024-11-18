#include <iostream>
#include "Trie.h" // Include the Trie header file
using namespace std;

int main() {
    Trie trie;   // Create an object of the Trie class
    string command;   // Store input command

    while (cin >> command) {
        if (command == "LOAD") {
            string filename;
            cin >> filename;

            trie.load_input(filename);
            cout << "success" << endl;
        }

        else if (command == "INSERT") {
            string classification;
            cin >> classification;
            trie.insert_classification(classification);
        }

        else if (command == "CLASSIFY") {
            string input;
            cin >> input;
            trie.classify_input(input);
        }

        else if (command == "ERASE") {
            string classification;
            cin >> classification;
            trie.erase_classification(classification);
        }

        else if (command == "PRINT") {
            cout << trie.print_classifications() << endl;
        }

        else if (command == "EMPTY") {
            if (trie.is_trie_empty()) {
                cout << "empty 1" << endl;
            }
            else {
                cout << "empty 0" << endl;
            }
        }

        else if (command == "CLEAR") {
            trie.clear_all_nodes();
        }

        else if (command == "SIZE") {
            cout << "number of classifications is " << trie.return_trie_size() << endl;
        }

        else if (command == "EXIT") {
            break;
        }
    }

    return 0;
}