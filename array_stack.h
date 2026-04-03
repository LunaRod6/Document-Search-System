#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H

#include <vector>
#include <stdexcept>

template<typename T>
class ArrayStack {
private:
    std::vector<T> data;

public:
    void push(const T& val) {
        data.push_back(val);
    }

    void pop() {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }

        data.pop_back();
    }

    T peek() const {
        if(isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }

        return data.back();
    }

    bool isEmpty() const {
        return data.empty();
    }

    int size() const {
        return data.size();
    }
};

#endif 
