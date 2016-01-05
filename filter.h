#ifndef HASH_H
#define HASH_H

#include <vector>
#include <algorithm>

#include "bst.h"

typedef uint64_t Hash;

class Filter {
public:
	// Look up the hash from the array
	// return true if element in array
	virtual bool lookUp(Hash hash) = 0;

	// Insert hash into the array
	// return true if successful
	virtual void insert(Hash hash) = 0;

	std::vector<Hash> array;
	BST bst {0};

};

#endif