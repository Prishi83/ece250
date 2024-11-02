// Enqueuing, dequeuing, and resizing deque

#ifndef DEQUE_H
#define DEQUE_H

// Class declaration
class Deque {
public:
    Deque();   // Constructor
    ~Deque();  // Destructor (frees up dynamically allocated memory)

    int size();
    int capacity();
    int front_pop();
    int rear_pop();
    bool isEmpty();
    void resize_deque();
    void enqueue_front(int id);
    void enqueue_rear(int id);
    void dequeue_front();
    void dequeue_rear();

private:
    int deque_size;     // Number of tasks in core's deque
    int deque_capacity; // Total number of tasks that can be stored in the core's duque
    int front_index;
    int rear_index;
    int* core_tasks;    // Dynamically allocated array of task IDs in the core
};

#endif