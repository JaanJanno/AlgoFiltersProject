#include "filter.h"
#include "cuckoo.h"
#include "noFilter.h"
#include "bloom.h"

#include <inttypes.h>
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <random>
#include <time.h>

#define TEST_NUM 10000

#define BLOOM_TABLE_SIZE 1024
#define BLOOM_HASH_COUNT 16

Hash generateHash(){
	return (uint64_t)rand() << 32 | rand();
}

void generateHashes(Hash *array) {
	for(int i = 0; i < TEST_NUM; ++i) {
		array[i] = generateHash();
	}
}

long getTime() {
	std::chrono::milliseconds t = std::chrono::duration_cast< std::chrono::milliseconds >(
    	std::chrono::system_clock::now().time_since_epoch()
		);
	return t.count();
}

long test(Filter *f) {
	std::cout << "Generating hash array" << std::endl;

	// Generate hash array
	Hash hashes[TEST_NUM];
	generateHashes(hashes);

	std::cout << "Running algorithm" << std::endl;

	// Start clock
	long start = getTime();

	// Run algorithm
	for (int i = 0; i < TEST_NUM; ++i) {
		Hash value = hashes[i];
		if(!f->lookUp(value)){
			f->insert(value);
		}
	}

	// Stop clock and calculate time
	long end = getTime();
	return (end - start);
}

int main() {
	srand(time(0));
	
	// Create 3 filters
	Filter *f1 = new NoFilter();
	Filter *f2 = new Bloom(BLOOM_TABLE_SIZE, BLOOM_HASH_COUNT);
	Filter *f3 = new Cuckoo();

	// Test no filter
	long time1 = test(f1);
	std::cout << "No filter test with " << TEST_NUM << " values: " << time1 << " ms" << std::endl;

	// Test bloom filter
	long time2 = test(f2);
	std::cout << "Bloom filter test with " << TEST_NUM << " values: " << time2 << " ms" << std::endl;

	// Test cuckoo filter
	long time3 = test(f3);
	std::cout << "Cuckoo filter test with " << TEST_NUM << " values: " << time3 << " ms" << std::endl;
}