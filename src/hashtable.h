#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <optional>
#include "hashnode.h"
#include "hashutils.h"


template <typename K, typename V, std::size_t tableSize, typename HashFunc = KeyHash<K, tableSize>>
class HashTable {
public:
    HashTable()
        : table(), hashFunc() {}

    ~HashTable() {
        for (size_t i = 0; i < tableSize; ++i) {
            HashNode<K, V> *entry = table[i];
            while (entry != nullptr) {
                HashNode<K, V> *prev = entry;
                entry = entry->getNext();
                delete prev;
            }
            table[i] = NULL;
        }
    }

    std::optional<HashNode<K, V>> Get(const K& key) {
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *entry = table[hashValue];
        while (entry != nullptr) {
            if (entry->Key() == key) {
                return *entry;
            }
            entry = entry->Next();
        }
        return std::nullopt;
    }


private:
    HashTable(const HashTable& other);
    const HashTable& operator=(const HashTable& other);
    HashNode<K, V> *table[tableSize];
    HashFunc hashFunc;
};

#endif // HASHTABLE_H
