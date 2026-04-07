#ifndef AVL_TREE_MAP_H
#define AVL_TREE_MAP_H

#include "bstmap.h"
#include <algorithm> // For std::max

template <typename K, typename V>
class AVLTreeMap : public BSTMap<K, V> {
private:
    
    int getHeight(typename BSTMap<K, V>::Node* n) {
        return n ? n->height : 0;
    }

    // Helper to calculate balance factor
    int getBalance(typename BSTMap<K, V>::Node* n) {
        return n ? getHeight(n->left) - getHeight(n->right) : 0;
    }

    // Right Rotation
    typename BSTMap<K, V>::Node* rotateRight(typename BSTMap<K, V>::Node* y) {
        typename BSTMap<K, V>::Node* x = y->left;
        typename BSTMap<K, V>::Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    // Left Rotation
    typename BSTMap<K, V>::Node* rotateLeft(typename BSTMap<K, V>::Node* x) {
        typename BSTMap<K, V>::Node* y = x->right;
        typename BSTMap<K, V>::Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    // Overriding the recursive insertion to add balancing
    typename BSTMap<K, V>::Node* insertRec(typename BSTMap<K, V>::Node* node, const K& key, int docID) override {
        
        if (!node) {
            V newList;
            newList.insertBack(docID);
            return new typename BSTMap<K, V>::Node(key, newList);
        }

        if (key < node->key) {
            node->left = insertRec(node->left, key, docID);
        } else if (key > node->key) {
            node->right = insertRec(node->right, key, docID);
        } else {
            node->value.insertBack(docID);
            return node;
        }

        // Update height of this ancestor node
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

        // Get balance factor to check if it became unbalanced
        int balance = getBalance(node);

        // Left Left Case
        if (balance > 1 && key < node->left->key)
            return rotateRight(node);

        // Right Right Case
        if (balance < -1 && key > node->right->key)
            return rotateLeft(node);

        // Left Right Case
        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Left Case
        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

public:
    AVLTreeMap() : BSTMap<K, V>() {}
    
    
};

#endif