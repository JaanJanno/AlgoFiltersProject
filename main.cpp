#include "filter.h"
#include "cuckoo.h"
#include "noFilter.h"
#include "bloom.h"
#include "bst.h"

#include <inttypes.h>
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <random>
#include <time.h>
#include <stdint.h>

#define BLOOM_TABLE_SIZE 1024000
#define BLOOM_HASH_COUNT 8

#define CUCKOO_TABLE_SIZE 1024000
#define CUCKOO_BUCKET_COUNT 8

static int TEST_NUM=1000000;

Hash generateHash(){
	return rand() % TEST_NUM;
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

long test(Filter *f, Hash *hashes) {
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

	// Generate hash array
	Hash* hashes = (Hash*)malloc(TEST_NUM*8);
	generateHashes(hashes);
	
	// Create 3 filters
	Filter *f1 = new NoFilter();

	Filter *f2 = new Bloom(BLOOM_TABLE_SIZE, BLOOM_HASH_COUNT);
	Filter *f3 = new Bloom(BLOOM_TABLE_SIZE, 1);

	Filter *f4 = new Cuckoo(CUCKOO_TABLE_SIZE, CUCKOO_BUCKET_COUNT);

	std::cout << "size,noFilter,Bloom,Bloom1Hash,Cuckoo" << std::endl;
	while(TEST_NUM > 50000) {
		std::cout << TEST_NUM << ',' << test(f1, hashes) << ',' << test(f2, hashes) << ',' << test(f3, hashes) << ',' << test(f4, hashes) << std::endl;
		TEST_NUM /= 2;
	}
	/*
	// Test no filter
	long time1 = test(f1);
	std::cout << "No filter test with " << TEST_NUM << " values: " << time1 << " ms" << std::endl;

	// Test bloom filter
	long time2 = test(f2);
	std::cout << "Bloom filter test with " << TEST_NUM << " values: " << time2 << " ms" << std::endl;

	// Test cuckoo filter
	long time3 = test(f3);
	std::cout << "Cuckoo filter test with " << TEST_NUM << " values: " << time3 << " ms" << std::endl;
	*/
}