#ifndef HASHING_H
#define HASHING_H

// The required hash functions are described as this class.
class HashFunction {
private:
    long a, b, maximum, prime = 47055833369llu; // 47,055,833,369
    long random();

public:
    HashFunction(long w);
    ~HashFunction();
    long hash(long number);
};

#endif