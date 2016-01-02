#ifndef NOFILTER_H
#define NOFILTER_H

#include "filter.h"

class NoFilter : public Filter
{
public:

	NoFilter();
	~NoFilter();

	bool lookUp(Hash hash);

	void insert(Hash hash);
};

#endif