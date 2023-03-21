#include <iostream>
#include <string>
#include <assert.h>
#include "hashtable.h"


using namespace std;
using namespace string_literals;

struct TestKeyHash {
    unsigned long operator()(const int& i) const {
        return i % 10;
    }
};

int main()
{
    HashTable<int, std::string, 10, TestKeyHash> hashTable;
    hashTable.Insert(1, "1"s);
    hashTable.Insert(2, "2"s);
    hashTable.Insert(3, "3"s);

    string value;
    auto result = hashTable.Get(2);
    assert(result.has_value());
    assert(result.value() == "2"s);

    auto result2 = hashTable.Get(2);
    assert(result2.has_value());
    assert(result2.value() == "2"s);

    hashTable.Remove(3);
    auto result3 = hashTable.Get(3);
    assert(!result3.has_value());

    return 0;
}
