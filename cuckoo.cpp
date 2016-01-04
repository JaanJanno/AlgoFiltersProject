#include "cuckoo.h"

Cuckoo::Cuckoo(uint64_t tableSize, uint64_t hashCount, uint64_t maxNumKicks){
	this->tableSize = tableSize*2; //the table consists of two separate tables
	this->hashCount = hashCount;
	this->maxNumKicks = maxNumKicks;

    table = (uint64_t*)calloc(this->tableSize, 8);
	hashes1 = (HashFunction**)malloc(hashCount * sizeof(HashFunction*));
	hashes2 = (HashFunction2**)malloc(hashCount * sizeof(HashFunction2*));

}
Cuckoo::~Cuckoo(){
	free(table);
	for(int i = 0; i < hashCount; i++) {
		delete hashes[i];
		delete hashes2[i];
    }
	free(hashes);
	free(hashes2);

}

// we rehash the value if there is a collision on both position1 and position2
void Cuckoo::rehash(Hash hash){
    uint64_t position3 = hash3(hash);
    if(hashes[position3] == nullptr) {
        hashes[position3] = hash;
        return true;
    }
    return false;
}

bool Cuckoo::lookUp(Hash hash){
    uint64_t position1 = hash(hash);
    uint64_t position2 = hash2(hash);
    uint64_t position3 = hash3(hash);
    if(hashes[position1] == hash || hashes[position2] == hash || hashes[position3] == hash)
        return true;
    return false;
}

bool Cuckoo::insert(Hash hash){
    uint64_t position1 = hash(hash);
    uint64_t position2 = hash2(hash);
    if(hashes[position1] == hash || hashes[position2] == hash)
        return true;
    position = position1;
    for(int i = 0; i < maxNumKicks; i++) {
        if(hashes[position] == nullptr) {
            hashes[position] = hash;
            return true;
        }
        position = position2;
        if(hashes[position] == nullptr) {
            hashes[position] = hash;
            return true;
        }
        // steals the place and the one kicked out will be reinserted
        Hash temp = hashes[position];
        hashes[position] = hash;
        insert(temp);
    }
    // return rehash(hash); // alternatively rehash and return the result of rehashing?
    return false;

}
