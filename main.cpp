#include "filter.h"
#include "cuckoo.h"
#include "noFilter.h"
#include "bloom.h"

#include <ctime>
#include <iostream>
#include <cstdlib>

#define TEST_NUM 10000

Hash generateHash(){
	if (sizeof(int) < sizeof(long)) {
		return (static_cast<long>(std::rand()) << (sizeof(int) * 8)) | std::rand();
	}
	return std::rand();
}

void generateHashes(Hash *array) {
	for(int i = 0; i < TEST_NUM; ++i) {
		array[i] = generateHash();
	}
}

double test(Filter *f) {
	std::cout << "Generating hash array" << std::endl;

	// Generate hash array
	Hash hashes[TEST_NUM];
	generateHashes(hashes);

	std::cout << "Running algorithm" << std::endl;

	// Start clock
	std::clock_t start;
	start = std::clock();

	// Run algorithm
	for (int i = 0; i < TEST_NUM; ++i) {
		Hash value = hashes[i];
		if(!f->lookUp(value)){
			f->insert(value);
		}
	}

	// Stop clock and calculate time
	return (double)(std::clock() - start);
}

int main() {
	// Create 3 filters
	Filter *f1 = new NoFilter();
	Filter *f2 = new Bloom();
	Filter *f3 = new Cuckoo();

	// Test no filter
	double time1 = test(f1);
	std::cout << "No filter test with " << TEST_NUM << " values: " << time1 << " ms" << std::endl;

	// Test bloom filter
	double time2 = test(f2);
	std::cout << "Bloom filter test with " << TEST_NUM << " values: " << time2 << " ms" << std::endl;

	// Test cuckoo filter
	double time3 = test(f3);
	std::cout << "Cuckoo filter test with " << TEST_NUM << " values: " << time3 << " ms" << std::endl;
}