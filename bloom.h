#ifndef BLOOM_H
#define BLOOM_H

#include "filter.h"
#include "hashing.h"

class Bloom : public Filter
{
private:
	uint64_t hashCount, tableSize;
	uint64_t* table;
	HashFunction** hashes;

public:

	Bloom(uint64_t tableSize, uint64_t hashCount);
	~Bloom();

	bool lookUp(Hash hash);

	void insert(Hash hash);
};

#endif