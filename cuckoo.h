#ifndef CUCKOO_H
#define CUCKOO_H

#include "filter.h"
#include "hashing.h"

class Cuckoo : public Filter
{
private:

	char* table;

	HashFunction* hashFun;
	HashFunction* fingerFun;

	char finger(uint64_t elem);

	uint64_t hash1(uint64_t elem);

	uint64_t hash2(uint64_t hash1, char finger);

	uint64_t bucketCount;

	bool elemInBucket(char finger, uint64_t bucket);

	bool elemToBucket(char finger, uint64_t bucket);

public:

	Cuckoo(uint64_t tableSize, uint64_t bucketCount);

	~Cuckoo();

	bool lookUp(Hash hash);

	void insert(Hash hash);

};

#endif