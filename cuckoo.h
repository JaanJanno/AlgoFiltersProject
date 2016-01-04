#ifndef CUCKOO_H
#define CUCKOO_H

#include "filter.h"
#include "hashing.h"

class Cuckoo : public Filter
{
private:
	uint64_t hashCount, tableSize;
	uint64_t* table;
	HashFunction** hashes;
public:

	Cuckoo(uint64_t tableSize, uint64_t hashCount, uint64_t maxNumKicks);
	~Cuckoo();

    uint64_t chooseRandomly(Hash hash1, Hash Hash2);

    uint64_t fingerprint(Hash hash);

	bool lookUp(Hash hash);

	bool insert(Hash hash);
};

#endif
