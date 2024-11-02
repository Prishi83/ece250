#include "FieldMap.h"
#include <iostream>
using namespace std;


int main() {
    FieldMap map;
    string command; // Store input command
    
    while (cin >> command) {  // Loop through input file commands until "EXIT" command
        if (command == "CREATE") {  // Create a new grid of size N rows x M columns (ints)
            int N;  // Rows
            int M;  // Columns
            cin >> N;
            cin >> M;

            map.create_field(N, M);
            cout << "success" << endl;
        }

        else if (command == "POINT") {
            char T;  // 'G' for goal or 'O' for obstacle
            int X;   // x coordinate for goal/obstacle position
            int Y;   // y coordinate for goal/obstacle position
            cin >> T >> X >> Y;

            bool result = map.insert_point(T, X, Y);
            if (result) {
                cout << "success" << endl;
            }
            else {
                cout << "failure" << endl;
            }
        }

        else if (command == "MOVE") {
            int X;   // x coordinate for current robot position
            int Y;   // y coordinate for current robot position
            cin >> X >> Y;
            
            map.move_robot(X, Y);
        }

        else if (command == "CLEAR") {
            if (map.clear()) {
                cout << "success" << endl;
            }
            else {
                cout << "failure" << endl;
            }
        }

        else if (command == "UPDATE") {
            double new_K;
            cin >> new_K;   // Constant in potential value formula

            bool result = map.update(new_K);
            if (result) {
                cout << "success" << endl;
            }
            else {
                cout << "failure" << endl;
            }
        }
        
        else if (command == "EXIT") {
            break;
        }
    }

    return 0;
}