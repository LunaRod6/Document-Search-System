#ifndef BSTMAP_H
#define BSTMAP_H

#include "linked_list.h"

template <typename K, typename V>
class BSTMap {
private:
    struct Node {
        K key;
        V value;
        Node *left, *right;

        Node(K k, V v) : key(k), value(v), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* insertRec(Node* node, const K& key, int docID);

public:
    BSTMap() : root(nullptr) {}

    void insertNode(const K& key, const int& docID);
    V* findNode(const K& key);
};

template <typename K, typename V>
void BSTMap<K, V>::insertNode(const K& key, const int& docID) {
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