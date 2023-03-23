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
    const HashNode<int, std::string>& result1 = hashTable.Insert(1, "1"s);
    assert(result1.Value() == "1"s);

    hashTable.Insert(2, "2"s);
    hashTable.Insert(3, "3"s);

    auto result2 = hashTable.Get(2);
    assert(result2.has_value());
    assert(result2.value() == "2"s);

    hashTable.Remove(3);
    auto result3 = hashTable.Get(3);
    assert(!result3.has_value());

    assert(hashTable.Size() == 2);

    hashTable[3] = "4"s;
    auto result2_2 = hashTable.Get(3);
    assert(result2_2 == "4"s);

    assert(hashTable.Size() == 3);

    return 0;
}
