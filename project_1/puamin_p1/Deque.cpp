#include "Deque.h"
#include <iostream>
using namespace std;

// Constructor definition
Deque::Deque() {
    deque_size = 0;     // Number of tasks currently in core's deque
    deque_capacity = 4; // Total number of tasks that can be stored in the core's duque
    front_index = 0;    // First index of deque is 0
    rear_index = -1;    // Deque is initially empty
    core_tasks = new int[4];  // Dynamically allocated array of task IDs in the core
}


// Destructor definition
Deque::~Deque() {
    delete[] core_tasks;
    core_tasks = nullptr;   // Dynamic array memory freed
}


int Deque::size() {
    return deque_size;
}


int Deque::capacity() {
    return deque_capacity;
}


bool Deque::isEmpty() {
    if (deque_size == 0) {
        return true;
    }
    else {
        return false;
    }
}


void Deque::resize_deque() {
    // When deque is full, double the capacity
    if (deque_size == deque_capacity) {
        int new_deque_capacity;

        if (deque_capacity == 0) {
            new_deque_capacity = 2;    // Set capacity to minimum value if no capacity has been assigned
        }
        else {
            new_deque_capacity = deque_capacity * 2;    // Double the capacity
        }

        int* new_core_tasks = new int[new_deque_capacity];  // New array with double capacity
        for (int i=0; i <= deque_size-1; i++) {    // Add all elements to new deque array
            new_core_tasks[i] = core_tasks[i];
        }

        // Free old memory and update to new array with more capacity
        delete[] core_tasks;
        core_tasks = nullptr;
        core_tasks = new_core_tasks;

        // Update size, capacity, and indexes of deque
        deque_capacity = new_deque_capacity;
        front_index = 0;
        rear_index = deque_size - 1;
    }

    // When deque size is 1/4 of the capacity, divide the capacity by 2
    else if ((deque_size <= (deque_capacity/4)) && (deque_capacity >= 2)) {
        int new_deque_capacity;

        if ((deque_capacity / 2) > 2) {
            new_deque_capacity = deque_capacity / 2;
        }
        else {
            new_deque_capacity = 2;    // Minimum capacity
        }

        int* new_core_tasks = new int[new_deque_capacity];   // New deque array with updated capacity
        for (int i=0; i <= deque_size-1; i++) {    // Add all elements to new deque array
            new_core_tasks[i] = core_tasks[i];
        }

        // Free old memory and update to new array with more capacity
        delete[] core_tasks;
        core_tasks = nullptr;
        core_tasks = new_core_tasks;

        // Update size, capacity, and indexes of deque
        deque_capacity = new_deque_capacity;
        front_index = 0;
        rear_index = deque_size - 1;
    }
}


void Deque::enqueue_front(int id) {
    if (deque_size == deque_capacity) {
        resize_deque();
    }

    // Shift all indexes one to the right to create space for new first element
    for (int i = deque_size-1; i>=0; i--) {
        core_tasks[i+1] = core_tasks[i];
    }
    core_tasks[front_index] = id;   // Add id to the front
    rear_index++;
    deque_size++;
}


void Deque::enqueue_rear(int id) {
    if (deque_size == deque_capacity) {
        resize_deque();
    }
    
    // Increase size of deque and rear index by 1, then add id at that new position
    deque_size++;
    rear_index++;
    core_tasks[rear_index] = id;
}


void Deque::dequeue_front() {
    if (!isEmpty()) {
        // Shift all indexes one to the left to remove the first element
        for (int i=0; i < deque_size-1; i++) {
            core_tasks[i] = core_tasks[i+1];
        }
        // Decrement the size and update rear index
        deque_size--;
        rear_index = deque_size-1;

        resize_deque();
    }
    // else {
    //     return -1;
    // }
}


void Deque::dequeue_rear() {
    if (!isEmpty()) {
        rear_index--;   // Decrement by one to remove the last element
        deque_size--;   // Decrement the size by one

        resize_deque();
    }
    // else {
    //     return -1;
    // }
}


int Deque::front_pop() {
    if (!isEmpty()) {   // Remove first element (task) from deque and return its value (ID)
        int id;
        id = core_tasks[front_index];
        dequeue_front();
        return id;
    }
    else {
        return -1;  // Deque is empty
    }
}


int Deque::rear_pop() {
    if (!isEmpty()) {   // Remove last element (task) from deque and return its value (ID)
        int id;
        id = core_tasks[rear_index];
        dequeue_rear();
        return id;
    }
    else {
        return -1;  // Deque is empty
    }
}