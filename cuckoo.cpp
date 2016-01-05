#include "cuckoo.h"

#define CUCKOO_KICK_COUNT 100

Cuckoo::Cuckoo(uint64_t tableSize, uint64_t bucketCount){
	table = (char*)calloc(tableSize * bucketCount, 1);

	hashFun = new HashFunction(tableSize);
	fingerFun = new HashFunction(255);

	this->bucketCount = bucketCount;
}

Cuckoo::~Cuckoo(){
	free(table);
	delete hashFun;
}

char Cuckoo::finger(uint64_t elem) {
	return (char)fingerFun->hash(elem) + 1;
}

uint64_t Cuckoo::hash1(uint64_t elem) {
	return hashFun->hash(elem);
}

uint64_t Cuckoo::hash2(uint64_t hash1, char finger) {
	return hash1 xor hashFun->hash(finger);
}

bool Cuckoo::elemToBucket(char finger, uint64_t bucket) {
	for(int i = 0; i < bucketCount; i++) {
		if(table[bucket * bucketCount + i] == 0) {
			table[bucket * bucketCount + i] = finger;
			return true;
		}
	}
	return false;
}

bool Cuckoo::elemInBucket(char finger, uint64_t bucket) {
	for(int i = 0; i < bucketCount; i++) {
		if(table[bucket * bucketCount + i] == finger) {
			return true;
		}
	}	
	return false;
}

bool Cuckoo::lookUp(Hash hash){
	char f = finger(hash);
	uint64_t h1 = hash1(hash);
	uint64_t h2 = hash2(h1, f);

	if(elemInBucket(f, h1)) {

		if(std::find(array.begin(), array.end(), hash) != array.end()) {
			return true;
		}
		return false;	
	}
	else if(elemInBucket(f, h2)) {

		if(std::find(array.begin(), array.end(), hash) != array.end()) {
			return true;
		}
		return false;	
	}
	else
		return false;
}

void Cuckoo::insert(Hash hash){
	char f = finger(hash);
	uint64_t h1 = hash1(hash);
	uint64_t h2 = hash2(h1, f);

	if(elemInBucket(f, h1))
		return;
	if(elemInBucket(f, h2))
		return;

	if(elemToBucket(f, h1)) {
		array.push_back(hash);
		return;
	}
	if(elemToBucket(f, h2)) {
		array.push_back(hash);
		return;
	}

	uint64_t h = rand()&1 ? h1 : h2;

	for(int i = 0; i < CUCKOO_KICK_COUNT; i++) {
		char e = table[(h * bucketCount + rand() % bucketCount)];

		uint64_t swap = f;
		f = e;

		h = h xor hash1(f);

		if(elemToBucket(f, h)) {
			array.push_back(hash);
			return;
		}
	}
}