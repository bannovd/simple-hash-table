#include <iostream>
#include <string>
#include <assert.h>
#include "hashtable.h"


using namespace std::string_literals;

struct TestKeyHash {
    unsigned long operator()(const int& i) const {
        return i % 10;
    }
};

int main()
{
    HashTable<int, std::string, 10, TestKeyHash> hashTable;
    hashTable.insert(1, "1"s);
    hashTable.insert(2, "2"s);
    hashTable.insert(3, "3"s);

    std::string value;
    auto result = hashTable.get(2);
    assert(result.has_value());
    assert(result.value() == "2"s);

    auto result2 = hashTable.get(2);
    assert(result2.has_value());
    assert(result2.value() == "2"s);

    hashTable.remove(3);
    auto result3 = hashTable.get(3);
    assert(!result3.has_value());

    assert(hashTable.size() == 2);

    hashTable[3] = "4"s;
    auto result2_2 = hashTable.get(3);
    assert(result2_2 == "4"s);

    assert(hashTable.size() == 3);

    return 0;
}
