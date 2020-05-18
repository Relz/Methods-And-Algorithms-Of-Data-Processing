#ifndef MULTIPLESAMPLETEXTSEARCH_BOHRNODE_H
#define MULTIPLESAMPLETEXTSEARCH_BOHRNODE_H

#include <string>
#include <unordered_map>

class BohrNode
{
public:
	explicit BohrNode(char value = '#', BohrNode * parentNode = nullptr)
		: value(value)
		, parentNode(parentNode)
	{}

	std::unordered_map<char, BohrNode *> childrenMap;
	std::unordered_map<char, BohrNode *> autoMove;
	BohrNode * parentNode;
	BohrNode * suffixLink = nullptr;
	BohrNode * suffixFineLink = nullptr;
	std::string sample;
	char value;
};

#endif //MULTIPLESAMPLETEXTSEARCH_BOHRNODE_H
