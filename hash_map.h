#ifndef HASH_MAP_H
#define HASH_MAP_H

#include "linked_list.h"
#include <string>
#include <vector>

template <typename K, typename V>
class HashMap {
private:
    struct Entry {
        K key;
        V value;

        bool operator==(const Entry& other) const {
            return key == other.key;
        }
    };

    std::vector<LinkedList<Entry>> table;
    int numBuckets;
    int numElements;

    int hashFunction(const K& key) const {
        std::hash<K> hasher;
        return hasher(key) % numBuckets;
    }

    void rehash();

public:
    HashMap(int size = 101) : numBuckets(size), numElements(0) {
        table.resize(numBuckets);
    }

    void insertElement(const K& key, int docID);
    V* findElement(const K& key);
};

template <typename K, typename V>
void HashMap<K, V>::insertElement(const K& key, int docID) {
    if ((float)numElements / numBuckets > 0.75) {
        rehash();
    }

    int index = hashFunction(key);

    LinkedList<Entry>& bucket = table[index];

    auto* curr = bucket.getHead();

    while (curr) {
        if (curr->data.key == key) {
            curr->data.value.insertBack(docID);
            return;
        }
        curr = curr->next;
    }

    V newIDList;
    newIDList.insertBack(docID);

    Entry newEntry;
    newEntry.key = key;
    newEntry.value = newIDList;

    bucket.insertBack(newEntry);
    numElements++;

}

template <typename K, typename V>
V* HashMap<K, V>::findElement(const K& key) {
    int index = hashFunction(key);
    auto*curr = table[index].getHead();

    while (curr) {
        if (curr->data.key == key) {
            return &(curr->data.value);
        }
        curr = curr->next;
    }

    return nullptr;
}

template <typename K, typename V>
void HashMap<K, V>::rehash() {
    int oldBuckets = numBuckets;
    numBuckets *= 2;

    std::vector<LinkedList<Entry>> newTable(numBuckets);

    for (int i = 0; i < oldBuckets; i++) {
        auto* curr = table[i].getHead();
        while (curr) {
            int newIndex = std::hash<K>{}(curr->data.key) % numBuckets;
            newTable[newIndex].insertBack(curr->data);
            curr = curr->next;
        }
    }
    table = std::move(newTable);
}

#endif