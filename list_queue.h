#ifndef LIST_QUEUE_H
#define LIST_QUEUE_H

#include "linked_list.h"
#include <stdexcept>

template<typename T>
class ListQueue {
private:
    LinkedList<T> storage;

public:
    void enqueue(T val) {
        storage.insertBack(val);
    }

    void dequeue() {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty");
        }
        storage.popFront();
    }

    T peek() const {
        if (isEmpty()) {
            throw std::out_of_range("Queue is empty");
        }
        return storage.getFront();
    }

    bool isEmpty() const { return storage.size() == 0; }
    int size() const { return storage.size(); }
};

#endif