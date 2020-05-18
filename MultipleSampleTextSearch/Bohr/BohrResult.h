#ifndef MULTIPLESAMPLETEXTSEARCH_BOHRRESULT_H
#define MULTIPLESAMPLETEXTSEARCH_BOHRRESULT_H

#include "TextFilePosition.h"
#include <string>

struct BohrResult
{
	BohrResult(TextFilePosition position, std::string_view sample)
		: position(position)
		, sample(sample)
	{}

	TextFilePosition position;
	std::string_view sample;
};

#endif //MULTIPLESAMPLETEXTSEARCH_BOHRRESULT_H
