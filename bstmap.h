#ifndef BSTMAP_H
#define BSTMAP_H

#include "linked_list.h"

template <typename K, typename V>
class BSTMap {
protected:
    struct Node {
        K key;
        V value;
        Node *left, *right;
        int height;

        Node(K k, V v) : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    // Helper to the destructor
    void destroyTree(Node* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    // Helper to the Copy Map
    Node* copyTree(Node* otherNode) {
        if (!otherNode) return nullptr;

        Node* newNode = new Node(otherNode->key, otherNode->value);

        newNode->left = copyTree(otherNode->left);
        newNode->right = copyTree(otherNode->right);

        return newNode;
    }

    virtual Node* insertRec(Node* node, const K& key, int docID);

public:
    BSTMap() : root(nullptr) {}

    virtual ~BSTMap() {
        destroyTree(root);
    }

    BSTMap(const BSTMap& other) {
        root = copyTree(other.root);
    }

    BSTMap& operator=(const BSTMap& other) {
        if (this != &other) {
            destroyTree(root);
            root = copyTree(other.root);
        }
        return *this;
    }

    void insertNode(const K& key, int docID);
    V* findNode(const K& key);
};

template <typename K, typename V>
void BSTMap<K, V>::insertNode(const K& key, int docID) {
    root = insertRec(root, key, docID);
}

template <typename K, typename V>
typename BSTMap<K, V>::Node* BSTMap<K, V>::insertRec(Node* node, const K& key, int docID) {
    if (node == nullptr) {
        V newList;
        newList.insertBack(docID);
        return new Node(key, newList);
    }

    if (key < node->key) {
        node->left = insertRec(node->left, key, docID);
    } else if (key > node->key) {
        node->right = insertRec(node->right, key, docID);
    } else {
        node->value.insertBack(docID);
    }
    return node;

}

template <typename K, typename V>
V* BSTMap<K, V>::findNode(const K& key) {
    Node* curr = root;
    while (curr) {
        if (key == curr->key) return &(curr->value);
        if (key < curr->key) curr = curr->left;
        else curr = curr->right;
    }
    return nullptr;
}

#endif