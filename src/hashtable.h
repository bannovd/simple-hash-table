#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <optional>
#include "hashnode.h"
#include "hashutils.h"


template <typename K, typename V, std::size_t tableSize, typename HashFunc = KeyHash<K, tableSize>>
class HashTable {
public:
    HashTable(const HashTable& other) = delete;
    const HashTable& operator=(const HashTable& other) = delete;
    HashTable()
        : table_(), hashFunc_() {}

    ~HashTable() {
        for (size_t i = 0; i < tableSize; ++i) {
            HashNode<K, V> *entry = table_[i];
            while (entry != nullptr) {
                HashNode<K, V> *prev = entry;
                entry = entry->getNext();
                delete prev;
            }
            table_[i] = NULL;
        }
    }

    std::optional<HashNode<K, V>> Get(const K& key) {
        unsigned long hashValue = hashFunc_(key);
        HashNode<K, V> *entry = table_[hashValue];
        while (entry != nullptr) {
            if (entry->Key() == key) {
                return *entry;
            }
            entry = entry->Next();
        }
        return std::nullopt;
    }

    void Insert(const K &key, const V &value) {
        unsigned long hashValue = hashFunc_(key);
        HashNode<K, V> *prev = NULL;
        HashNode<K, V> *entry = table_[hashValue];

        while (entry != nullptr && entry->Key() != key) {
            prev = entry;
            entry = entry->Next();
        }

        if (entry == NULL) {
            entry = new HashNode<K, V>(key, value);
            if (prev == NULL) {
                table_[hashValue] = entry;
            } else {
                prev->SetNext(entry);
            }
        } else {
            entry->SetValue(value);
        }
    }
private:    
    HashNode<K, V>* table_[tableSize];
    HashFunc hashFunc_;
};

#endif // HASHTABLE_H
