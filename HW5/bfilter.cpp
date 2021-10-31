#include <vector>
#include "bfilter.h"
#include <iostream>
#include "math.h"

// (a)

class SillyHashFun : public HashFun {
    unsigned int operator()(const std::string& key) {
        // Here's my silly hash function that always returns 0.
        // You should make some good hash functions and not use this one.
        // This is just an example of how to inherit the HashFun class.
        return 0;
    }
};

class MultiplicationHashFun : public HashFun {
    unsigned int operator()(const std::string& key) {
        int length = key.length();
        unsigned int value = 0;
        
        //A constant c such that 0<c<1 that is recommended by Knuth as close to ideal 
        double c = ((sqrt(5)-1)/2);

        //if less than 7 characters (i.e. 'http://')
        if (length < 7)
            {
                for (int i = 0; i < length; i++)
                    {
                        value += key[i];
                    }
            }
        
        //else sum up the values of the ascii characters in the string after 'http://'
        else
            {
                for (int i = 6; i<length; i++)
                {
                    value += key[i];
                }
            }
        
        //takes the fractional component of the sum of charcters * c and multiplies it by 330 the size of bitset.
        double fraction = (value*c) - floor(value*c);
        int hash = fraction*330;
        return hash;
    }
};

//sums up all the values of the ascii characters after first seven characters 'http://'
class SimpleSumHashFun : public HashFun {
    unsigned int operator()(const std::string& key) {
        //initialize a variable to hold the integer value
        int value = 0;

        int length = key.length();
        
        //if less than 7 characters (i.e. 'http://')
        if (length < 7)
            {
                for (int i = 0; i < length; i++)
                    {
                        value += key[i];
                    }
            }
        //else sum up the values of the ascii characters in the string after 'http://'
        else
            {
                for (int i = 6; i<length; i++)
                {
                    value += key[i];
                }
            }

        return value;
    }
};

// ...
// You can make as many hash functions as you want!
// ...

void BloomFilter::add_hash_funs() {
    // You will need to implement this function, it is responsible
    // for adding your custom hash functions to your bloom filter.

    MultiplicationHashFun *h1 = new MultiplicationHashFun();
    SimpleSumHashFun *h2 = new SimpleSumHashFun();
    this->hash_funs.push_back(h1);
    this->hash_funs.push_back(h2);
}

void BloomFilter::insert(const std::string& key) {
    // You will need to implement this function, it is responsible
    // for inserting key into the bloom filter.
    
    int functions = this->hash_funs.size();

    for (int i = 0; i < functions; i++)
        {
            unsigned int hash_result = this->call_hash(i, key);
            (this->filter)[hash_result % 330] = 1;
        }

}

bool BloomFilter::member(const std::string& key) {
    // This function should report true if key is potentially in the bloom filter.
    // It should only return false if you know for sure that key is not in the bloom filter.

    bool present = true;
    int functions = this->hash_funs.size();

    for (int i = 0; i < functions; i++)
        {
            unsigned int hash_result = this->call_hash(i, key);
            int check = (this->filter)[hash_result % 330];

            //if not already false, and this one is also true, present is true, othewise false.
            if ((present) && (check == 1))
                present = true;
            else
                present = false;
        }
   
    return present; // returns true if all checks for each hash function are true
}
