#ifndef HASHING_H
#define HASHING_H

#include <stdint.h>

// The required hash functions are described as this class.
class HashFunction {
private:
    uint64_t a, b, maximum, prime = 47055833369llu; // 47,055,833,369
    uint64_t random();

public:
    HashFunction(uint64_t w);
    ~HashFunction();
    uint64_t hash(uint64_t number);
};

#endif