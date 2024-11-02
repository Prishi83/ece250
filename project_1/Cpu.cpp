#include "Cpu.h"
#include <iostream>
using namespace std;

// Constructor definition
Cpu::Cpu() {
    total_cores = 0;        // Number of total cores
    cores_array = 0;  // Dynamically allocated array of Deques (one for each core)
}


// Destructor definition
Cpu::~Cpu() {
    delete[] cores_array;
    cores_array = nullptr;
}


void Cpu::new_cpu_instance(int N) {   // Create a new CPU instance with N cores
    if (total_cores == 0) {      // A CPU does not exists
        total_cores = N;
        cores_array = new Deque[total_cores];   // Cpu array that holds all of the cores (deques)
        cout << "success" << endl;
    }
    else {
        cout << "failure" << endl;
    }
}


void Cpu::spawn_new_task(int P_ID) {  // Spawn a new task to run
    if ((P_ID > 0) && (total_cores > 0)) {
        // Find core with the least number of tasks
        int min_num_of_tasks = cores_array[0].size();
        int index = 0;

        for (int i=1; i < total_cores; i++) {
            if (cores_array[i].size() < min_num_of_tasks) {
                min_num_of_tasks = cores_array[i].size();
                index = i;
            }
        }

        // Add new task to end of the core with the least number of tasks
        cores_array[index].enqueue_rear(P_ID);

        cout << "core " << index << " assigned task " << P_ID << endl;
    }

    else {   // Fail if non-positive ID or no cores initialized (CPU doesn't exist)
        cout << "failure" << endl;
    }
}


void Cpu::run_next_task(int C_ID) {   // Run the next task on the core
    // C_ID is in the bounds of [0, N-1]
    if ((C_ID >= 0) && (C_ID <= total_cores-1)) {
        // Deque is empty (core has no tasks)
        if (cores_array[C_ID].isEmpty()) {
            cout << "core " << C_ID << " has no tasks to run" << endl;
        }
        // Pop the next task from the front of the core's deque
        else {
            cout << "core " << C_ID << " is running task " << cores_array[C_ID].front_pop() << endl;
        }
    }
    // C_ID is out of the bounds of [0, N-1]
    else {
        cout << "failure" << endl;        
    }
}


void Cpu::sleep(int C_ID) {       // Put core to sleep by distributing its tasks to the other cores
    if ((C_ID < 0) || (C_ID >= total_cores)) {
        cout << "failure" << endl;   // C_ID is out of the bounds of [0, N-1]
        return;
    }

    if (cores_array[C_ID].size()==0) {     // Deque is empty (core has no remaining tasks)
        cout << "core " << C_ID << " has no tasks to assign" << endl;
        return;
    }
    
    //if ((C_ID >= 0) && (C_ID <= total_cores-1)) {     // C_ID is in the bounds of [0, N-1]
    while (cores_array[C_ID].size() > 0) {            // Reassign current core's tasks to other cores until it's empty
        int removed_task = cores_array[C_ID].rear_pop();

        // Find core with the least number of tasks
        int min_num_of_tasks = 10000000;
        int index = -1;

        for (int i=1; i < total_cores; i++) {
            if ((i != C_ID) && (cores_array[i].size() < min_num_of_tasks)) {
                min_num_of_tasks = cores_array[i].size();
                index = i;
            }
        }
                
        // Add new task to end of the core with the least number of tasks
        cores_array[index].enqueue_rear(removed_task);

        cout << "task " << removed_task << " assigned to core " << index << " ";
    }
    cout << endl;
}


void Cpu::shutdown() {                // Remove all remaining tasks from cores to shut down the CPU
    if (total_cores == 0) {
        cout << "no tasks to remove" << endl;
    }
    else {
        for (int i=0; i <= total_cores-1; i++) {
            while (!(cores_array[i].isEmpty())) {            // Remove tasks from each core until all cores are empty
                cout << "deleting task " << cores_array[i].rear_pop() << " from core " << i << " ";
            }
        }
    }
}


void Cpu::size_of_tasks(int C_ID) {   // Print number of tasks in the core's deque (number of current tasks)
    if ((C_ID >= 0) && (C_ID <= total_cores-1)) {   // C_ID is in the bounds of [0, N-1]
        cout << "size is " << cores_array[C_ID].size() << endl;
    }
    else {
        cout << "failure" << endl;
    }
}


void Cpu::deque_capacity(int C_ID) {  // Print total capacity of the core duque (number of tasks that can be stored)
    if ((C_ID >= 0) && (C_ID <= total_cores-1)) {   // C_ID is in the bounds of [0, N-1]
        cout << "capacity is " << cores_array[C_ID].capacity() << endl;
    }
    else {
        cout << "failure" << endl;
    }
}