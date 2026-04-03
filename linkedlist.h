#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        //Constructor
        Node(T val) : data(val), next(nullptr) {}
    };

    Node* head;
    int currentSize;

public:
    LinkedList() : head(nullptr), currentSize(0) {}

    // Add a node to the front
    void insertFront(T val);

    // Removes the first occurrence of a value
    bool remove(T val);

    // Print all elements
    void display() const;

    T getFront() const;

    // Returns the current size
    int size() const { return currentSize; }

    // Destructor
    ~LinkedList();
};

template <typename T>
void LinkedList<T>::insertFront(T val) {
    
    Node* newNode = new Node(val);

    newNode->next = head;

    head = newNode;

    currentSize++;
}

template<typename T>
bool LinkedList<T>::remove(T val) {

    if (head == nullptr) return false;

    if (head->data == val) {
        Node* temp = head;
        head = head->next;
        delete temp;
        currentSize--;
        return true;
    }

    Node* prev = head;
    Node* curr = head->next;

    while(curr) {
        if (curr->data == val) {
            prev->next = curr->next;
            delete curr;
            currentSize--;
            return true;
        }

        prev = curr;
        curr = curr->next;
    }

    return false;
}

template<typename T>
void LinkedList<T>::display() const {

    Node* curr = head;

    while(curr) {
        std::cout << curr->data << ", ";
        curr = curr->next;
    }
    std::cout << "nullptr" << std::endl;
}

template<typename T>
T LinkedList<T>::getFront() const {

    if (head == nullptr) {
        return T();
    }
    return head->data;

}

template<typename T>
LinkedList<T>::~LinkedList() {
    
    Node* curr = head;

    while(curr) {
        Node* nextNode = curr->next;

        delete curr;

        curr = nextNode;
    }

    head = nullptr;
    currentSize = 0;

}

#endif