#ifndef CUCKOO_H
#define CUCKOO_H

#include "filter.h"

class Cuckoo : public Filter
{
public:

	Cuckoo();
	~Cuckoo();

	bool lookUp(Hash hash);

	void insert(Hash hash);
};

#endif