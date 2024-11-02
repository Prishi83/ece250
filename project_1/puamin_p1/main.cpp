#include <iostream>
#include "Cpu.h"
using namespace std;

int main() {
    Cpu cpu;
    string command;   // Store input command

    while (cin >> command) {
        if (command == "ON") {
            int N;
            cin >> N;

            cpu.new_cpu_instance(N);
        }

        else if (command == "SPAWN") {
            int P_ID;
            cin >> P_ID;

            cpu.spawn_new_task(P_ID);
        }

        else if (command == "RUN") {
            int C_ID;
            cin >> C_ID;

            cpu.run_next_task(C_ID);
        }

        else if (command == "SLEEP") {
            int C_ID;
            cin >> C_ID;

            cpu.sleep(C_ID);
        }

        else if (command == "SHUTDOWN") {
            cpu.shutdown();
        }

        else if (command == "SIZE") {
            int C_ID;
            cin >> C_ID;

            cpu.size_of_tasks(C_ID);
        }

        else if (command == "CAPACITY") {
            int C_ID;
            cin >> C_ID;

            cpu.deque_capacity(C_ID);
        }

        else if (command == "EXIT") {
            break;
        }
    }

    return 0;
}