#ifndef BLOOM_H
#define BLOOM_H

#include "filter.h"

class Bloom : public Filter
{
public:

	Bloom();
	~Bloom();

	bool lookUp(Hash hash);

	void insert(Hash hash);
};

#endif