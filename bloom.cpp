#include "bloom.h"

void setBit(uint64_t* array, uint64_t index) {
    array[index / 64] |= (1LLU << (63 - (index % 64)));
}

int getBit(uint64_t* array, uint64_t index) {
    return (array[index / 64] >> (63 - (index % 64))) & 1;
}

Bloom::Bloom(uint64_t tableSize, uint64_t hashCount){
	this->tableSize = tableSize;
	this->hashCount = hashCount;

	table = (uint64_t*)calloc(tableSize, 8);
	hashes = (HashFunction**)malloc(hashCount * sizeof(HashFunction*));

	for(int i = 0; i < hashCount; i++)
		hashes[i] = new HashFunction(tableSize * 8);
}
Bloom::~Bloom(){
	free(table);
	for(int i = 0; i < hashCount; i++)
		delete hashes[i];
	free(hashes);
}

bool Bloom::lookUp(Hash hash){
	for(int i = 0; i < hashCount; i++) {
		uint64_t position = hashes[i]->hash(hash);
		if(!getBit(table, position))
			return false;
	}

	if(std::find(array.begin(), array.end(), hash) != array.end()) {
		return true;
	}
	return false;	
}

void Bloom::insert(Hash hash){
	for(int i = 0; i < hashCount; i++) {
		uint64_t position = hashes[i]->hash(hash);
		setBit(table, position);
	}
	array.push_back(hash);
}