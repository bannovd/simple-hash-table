#ifndef HASHUTILS_H
#define HASHUTILS_H

#include <cstdlib>


template <typename K, std::size_t tableSize>
struct KeyHash {
    unsigned long operator()(const K& key) const {
        return reinterpret_cast<unsigned long>(key) % tableSize;
    }
};

#endif // HASHUTILS_H
