#ifndef LINKED_LIST_H
#define LINKED_LIST_H

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
    Node* tail;
    int currentSize;

public:
    LinkedList() : head(nullptr), tail(nullptr), currentSize(0) {}

    // Add a node to the front
    void insertFront(T val);

    void insertBack(T val);

    // Removes the first occurrence of a value
    bool remove(T val);

    // Print all elements
    void display() const;

    T getFront() const;

    // Returns the current size
    int size() const { return currentSize; }

    //Copy Constructor
    LinkedList(const LinkedList<T>& other);

    //Copy Assignment Operator
    LinkedList<T>& operator=(const LinkedList<T>& other);

    // Destructor
    ~LinkedList();
};

template <typename T>
void LinkedList<T>::insertFront(T val) {
    
    Node* newNode = new Node(val);

    newNode->next = head;

    head = newNode;

    if (currentSize == 0) {
        tail = newNode;
    }
    currentSize++;
}

template <typename T>
void LinkedList<T>::insertBack(T val) {
    
    Node* newNode = new Node(val);

    if (head == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
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

            //If the node is a tail
            if (curr == tail) {
                tail = prev;
            }

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
LinkedList<T>::LinkedList(const LinkedList<T>& other) : head(nullptr), tail(nullptr), currentSize(0) {
    Node* curr = other.head;
    while (curr) {
        //Reusing the insertBack function
        this->insertBack(curr->data);
        curr = curr->next;
    }
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other) {
    if (this == &other) {
        return *this;
    }

    //Clears the target list
    Node* curr = head;
    while (curr) {
        Node* nextNode = curr->next;
        delete curr;
        curr = nextNode;
    }

    head = tail = nullptr;
    currentSize = 0;

    //Copies other's node by node to the empty list
    Node* otherCurr = other.head;
    while (otherCurr) {
        this->insertBack(otherCurr->data);
        otherCurr = otherCurr->next;
    }

    return *this;

}

template<typename T>
LinkedList<T>::~LinkedList() {
    
    Node* curr = head;

    while (curr) {
        Node* nextNode = curr->next;

        delete curr;

        curr = nextNode;
    }

    head = nullptr;
    currentSize = 0;

}

#endif