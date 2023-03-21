#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <optional>
#include <stdexcept>
#include "hashnode.h"
#include "hashutils.h"


template <typename K, typename V, std::size_t tableSize, typename HashFunc = KeyHash<K, tableSize>>
class HashTable {
public:
    HashTable(const HashTable& other) = delete;
    const HashTable& operator=(const HashTable& other) = delete;
    HashTable()
        : table_(), hashFunc_(), size_(0) {}

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

    std::optional<V> get(const K& key) {
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

    void insert(const K& key, const V& value) {
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
                ++size_;
            } else {
                prev->SetNext(entry);
            }
        } else {
            entry->SetValue(value);
            ++size_;
        }
    }

    void remove(const K& key) {
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
                --size_;
            } else {
                prev->SetNext(entry->Next());
            }
            delete entry;
        }
    }

    //auto begin() const;
    //auto end() const;
    size_t size() const {
        return size_;
    }

    V& operator[](const K& key) {
        unsigned long hashValue = hashFunc_(key);
        HashNode<K, V>* entry = table_[hashValue];
        while (entry != nullptr) {
            if (entry->Key() == key) {
                return entry->Value();
            }
            entry = entry->Next();
        }
        throw std::out_of_range("Wrong key");
    }

    const V& operator[](const K& key) const {
        unsigned long hashValue = hashFunc_(key);
        HashNode<K, V>* entry = table_[hashValue];
        while (entry != nullptr) {
            if (entry->Key() == key) {
                return entry->Value();
            }
            entry = entry->Next();
        }
        throw std::out_of_range("Wrong key");
    }
private:
    HashNode<K, V>* table_[tableSize];
    HashFunc hashFunc_;
    size_t size_;
};

#endif // HASHTABLE_H
