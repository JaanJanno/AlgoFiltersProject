#ifndef CUCKOO_H
#define CUCKOO_H

#include "filter.h"

class Cuckoo : public Filter
{
public:

	Cuckoo();
	~Cuckoo();

    void rehash(Hash hash);

	bool lookUp(Hash hash);

	bool insert(Hash hash);
};

#endif
