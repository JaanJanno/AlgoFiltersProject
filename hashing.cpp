#include "hashing.h"
#include <random>

long HashFunction::random() {
	return (long)rand() << 32 | rand();
}

HashFunction::HashFunction(long w) {
	maximum = w;
	a = 1 + random() % (prime - 1);
	b = random() % prime;
}

HashFunction::~HashFunction() {

}

long HashFunction::hash(long number) {
	return (number * a + b) % prime % maximum;
}