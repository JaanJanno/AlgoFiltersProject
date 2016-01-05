#ifndef BST_H
#define BST_H

#include <inttypes.h>

class BST {

private:

	BST* left;
	BST* right;

	uint64_t value;


public:

	BST(uint64_t first);
	~BST();

	virtual bool lookUp(uint64_t hash);

	virtual void insert(uint64_t hash);

};

#endif