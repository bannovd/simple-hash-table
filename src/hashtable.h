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
            HashNode<K, V>* entry = table_[i];
            while (entry != nullptr) {
                HashNode<K, V>* prev = entry;
                entry = entry->Next();
                delete prev;
            }
            table_[i] = nullptr;
        }
    }

    std::optional<V> Get(const K& key) {
        unsigned long hashValue = hashFunc_(key);
        HashNode<K, V>* entry = table_[hashValue];
        while (entry != nullptr) {
            if (entry->Key() == key) {
                return std::make_optional<V>(entry->Value());
            }
            entry = entry->Next();
        }
        return std::nullopt;
    }

    void Insert(const K& key, const V& value) {
        unsigned long hashValue = hashFunc_(key);
        HashNode<K, V>* prev = nullptr;
        HashNode<K, V>* entry = table_[hashValue];

        while (entry != nullptr && entry->Key() != key) {
            prev = entry;
            entry = entry->Next();
        }

        if (entry == nullptr) {
            entry = new HashNode<K, V>(key, value);
            if (prev == nullptr) {
                table_[hashValue] = entry;
            } else {
                prev->SetNext(entry);
            }
        } else {
            entry->SetValue(value);
        }
    }

    void Remove(const K& key) {
        unsigned long hashValue = hashFunc_(key);
        HashNode<K, V>* prev = nullptr;
        HashNode<K, V>* entry = table_[hashValue];

        while (entry != nullptr && entry->Key() != key) {
            prev = entry;
            entry = entry->Next();
        }

        if (entry == nullptr) {
            return;
        } else {
            if (prev == nullptr) {
                table_[hashValue] = entry->Next();
            } else {
                prev->SetNext(entry->Next());
            }
            delete entry;
        }
    }
private:
    HashNode<K, V>* table_[tableSize];
    HashFunc hashFunc_;
};

#endif // HASHTABLE_H
