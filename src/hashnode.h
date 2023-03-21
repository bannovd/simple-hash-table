#ifndef HASHNODE_H
#define HASHNODE_H

#include <utility>

template <typename K, typename V>
class HashNode {
public:
    HashNode(const HashNode &) = delete;
    HashNode & operator=(const HashNode &) = delete;

    HashNode(const K& key, const V& value)
        : key_(key), value_(value), next_(nullptr) {}

    const K& Key() const {
        return key_;
    }

    V& Value() {
        return value_;
    }
    const V& Value() const{
        return value_;
    }

    void SetValue(const V& value) {
        value_ = value;
    }

    HashNode* Next() {
        return next_;
    }

    void SetNext(HashNode* next) {
        next_ = next;
    }
private:
    K key_;
    V value_;
    HashNode* next_;
};

#endif // HASHNODE_H
