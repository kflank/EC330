#include <iostream>
#include <vector>
#include "bfilter.h"

int main() {
    
    BloomFilter bf = BloomFilter();
    bf.insert("Hello, World!");
    bf.insert("Lorem ipsum");

    std::cout << (bf.member("foo bar") ?
            "'foo bar' is in our bloom filter" :
            "'foo bar' is not in our bloom filter")
        << std::endl;

    return 0;
}
