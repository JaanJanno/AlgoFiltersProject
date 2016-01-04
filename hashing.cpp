#include "hashing.h"
#include <random>

uint64_t HashFunction::random() {
	return (uint64_t)rand() << 32 | rand();
}

HashFunction::HashFunction(uint64_t w) {
	maximum = w;
	a = 1 + random() % (prime - 1);
	b = random() % prime;
}

HashFunction::~HashFunction() {

}

uint64_t HashFunction::hash(uint64_t number) {
	return (number * a + b) % prime % maximum;
}

// 2nd hash function for Cuckoo filter
uint64_t HashFunction::hash2(uint64_t number) {
	return number % hash2_const;
}
