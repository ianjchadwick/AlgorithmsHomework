#include <iostream>
#include <vector>
#include "bfilter.h"
#include "string.h"

int main() {
    
    std::string input = "start";

    while (input != "q")
    {
    std:: cout << "Enter a string or q to quit: ";
    std::cin >> input;

    }


    BloomFilter bf = BloomFilter();
    bf.insert("Hello, World!");
    bf.insert("Lorem ipsum");

    std::cout << (bf.member("foo bar") ?
            "'foo bar' is in our bloom filter" :
            "'foo bar' is not in our bloom filter")
        << std::endl;


    return 0;
}
