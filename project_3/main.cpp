#include <iostream>
#include "trie.h"
using namespace std;

int main() {
    Trie trie;   // Create an object of the Trie class
    string command;   // Store input command

    while (cin >> command) {
        if (command == "LOAD") {
            string filename;
            cin >> filename;

            trie.loadFromFile(filename);
            cout << "success" << endl;
        }

        else if (command == "INSERT") {
            string classification;
            cin >> classification;

            if (classification.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos) {
                cout << "illegal argument" << endl;
            } else if (trie.insert(classification)) {
                cout << "success" << endl;
            } else {
                cout << "failure" << endl;
            }
        }

        else if (command == "CLASSIFY") {
            string input;
            cin >> input;

            if (input.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos) {
                cout << "illegal argument" << endl;
            } else {
                cout << trie.classify(input) << endl;
            }
        }

        else if (command == "ERASE") {
            string classification;
            cin >> classification;

            if (classification.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos) {
                cout << "illegal argument" << endl;
            } else if (trie.erase(classification)) {
                cout << "success" << endl;
            } else {
                cout << "failure" << endl;
            }
        }

        else if (command == "PRINT") {
            cout << trie.print() << endl;
        }

        else if (command == "EMPTY") {
            cout << (trie.isEmpty() ? "empty 1" : "empty 0") << endl;
        }

        else if (command == "CLEAR") {
            trie.clear();
            cout << "success" << endl;
        }

        else if (command == "SIZE") {
            cout << "number of classifications is " << trie.getSize() << endl;
        }

        else if (command == "EXIT") {
            break;
        }
    }

    return 0;
}
