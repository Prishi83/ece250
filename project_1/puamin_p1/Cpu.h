// Handles the cores (each core is a deque)
// Controls how tasks are assigned and for stealing tasks

#ifndef CPU_H
#define CPU_H

#include "Deque.h"

// Class declaration
class Cpu {
public:
    Cpu();   // Constructor
    ~Cpu();  // Destructor (frees up dynamically allocated memory)

    void new_cpu_instance(int N);   // Create a new CPU instance with N cores
    void spawn_new_task(int P_ID);  // Spawn a new task to run
    void run_next_task(int C_ID);   // Run the next task on the core
    void sleep(int C_ID);           // Put core to sleep by distributing its tasks to the other cores
    void shutdown();                // Remove all remaining tasks from cores to shut down the CPU
    void size_of_tasks(int C_ID);   // Print number of tasks in the core's deque (number of current tasks)
    void deque_capacity(int C_ID);  // Print total capacity of the core duque (number of tasks that can be stored)

private:
    Deque* cores_array;    // Dynamically allocated array of Deques (one for each core)
    int total_cores;       // Number of total cores
};

#endif