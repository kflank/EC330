#include <vector>
#include "bfilter.h"
#include <cmath>
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>

using namespace std;

// (a)

class SillyHashFun : public HashFun
{
    unsigned int operator()(const std::string &key)
    {

        unsigned int hash = 3;
        unsigned int p = 7;
        for (int i = 0; i < key.size(); i++)
        {
            hash += hash * 7 + key[0] * pow(p, i);
            hash = hash % 330;
        }
        return hash;
    }
};

class GoodHashFun_0 : public HashFun
{
    unsigned int operator()(const std::string &key)
    {

        unsigned int hash = 0;
        for (int i = 0; i < key.size(); i++)
        {
            hash = (hash + ((int)key[i]));
            hash = hash % 330;
        }
        return hash;
    }
};

// ...
// You can make as many hash functions as you want!
// ...

void BloomFilter::add_hash_funs()
{
    // You will need to implement this function, it is responsible
    // for adding your custom hash functions to your bloom filter.

    // Here's an example where I add two hash functions.
    // You will need to add at least one hash function.
    SillyHashFun *h1 = new SillyHashFun();
    GoodHashFun_0 *h2 = new GoodHashFun_0();
    this->hash_funs.push_back(h1);
    this->hash_funs.push_back(h2);
}

void BloomFilter::insert(const std::string &key)
{
    // You will need to implement this function, it is responsible
    // for inserting key into the bloom filter.

    // Here's how you can call your hash functions that you added in add_hash_funs()
    for (int i = 0; i < this->hash_funs.size(); i++)
    {
        unsigned int result = this->call_hash(i, key);
        //std::cout << "Hash of '" << key << "' is '" << first_hash_result << "' using the first hash function." << std::endl;
        //unsigned int second_hash_result = this->call_hash(1, key);
        //std::cout << "Hash of '" << key << "' is '" << second_hash_result << "' using the second hash function." << std::endl;

        // You'll need to use the results of the hash function to update this->filter
        // Here's an example

        (this->filter)[result % 330 ] = 1;
        //(this->filter)[second_hash_result] = 1;
    }
}

bool BloomFilter::member(const std::string &key)
{
    // This function should report true if key is potentially in the bloom filter.
    // It should only return false if you know for sure that key is not in the bloom filter.

    //
    // your code here ...
    //
    for (int i = 0; i < this->hash_funs.size(); i++)
    {
        unsigned int result = this -> call_hash(i,key);
        if (this->filter[result % 330] != 1)
        {
            return false;
        }
        // you will need to change this.
    }
    return true;
}

// int main(){

// BloomFilter B;
// B.add_hash_funs();

// string filename("phishing-links-ACTIVE.txt");
//     vector<string> lines;
//     string line;

//     ifstream input_file(filename);
//     if (!input_file.is_open()) {
//         cout << "Could not open the file - '"
//              << filename << "'" << endl;
//         return EXIT_FAILURE;
//     }

//     while (getline(input_file, line)){
//         lines.push_back(line);
//     }
//     int count =0;
//     for (const auto &i : lines)
//     {
//         B.insert(i);
//         //cout<< B.filter<<endl;
//         //cout<<count<<endl;
//         count++;

//         //cout<< i << endl;

//     }
//     cout<< B.filter<<endl;

//     input_file.close();
//     return EXIT_SUCCESS;

// }
