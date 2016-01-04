#include "cuckoo.h"
#include <cstdlib>

Cuckoo::Cuckoo(uint64_t tableSize, uint64_t hashCount, uint64_t maxNumKicks){
	this->tableSize = tableSize;
	this->hashCount = hashCount;
	this->maxNumKicks = maxNumKicks;

    table = (uint64_t*)calloc(this->tableSize, 8);
	hashes = (HashFunction**)malloc(hashCount * sizeof(HashFunction*));

}
Cuckoo::~Cuckoo(){
	free(table);
	for(int i = 0; i < hashCount; i++) {
		delete hashes[i];
    }
	free(hashes);

}
// Returns randomly either one of the input arguments
uint64_t chooseRandomly(Hash hash1, Hash Hash2){
    int randInt = rand() % 100;
    if(randInt >= 50)
        return hash1;
    return hash2;
}

uint64_t Cuckoo::fingerprint(Hash hash){
    f = hash2(hash);
    return f;
}

bool Cuckoo::lookUp(Hash hash){
    uint64_t f = fingerprint(hash);
    uint64_t position1 = hash(hash);
    uint64_t position2 = position1 xor hash(f);
    if(hashes[position1] == f || hashes[position2] == f)
        return true;
    return false;
}

void Cuckoo::insert(Hash hash){
    uint64_t f = fingerprint(hash);
    uint64_t position1 = hash(hash);
    uint64_t position2 = position1 xor hash(f);

    if(hashes[position1] == nullptr) {
        hashes[position1] = f;
        return;
    }

    if(hashes[position2] == nullptr) {
        hashes[position2] = f;
        return;
    }

    uint64_t position = chooseRandomly(position1, position2);
    for(int i = 0; i < maxNumKicks; i++) {
        uint64_t entry = hashes[position];
        hashes[position] = f;
        position = position xor hash(f);

        if(hashes[position] == nullptr) {
            hashes[position] = f;
            return;
        }
    }
    // too full
    return;

}

