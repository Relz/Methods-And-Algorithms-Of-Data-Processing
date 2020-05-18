#ifndef MULTIPLESAMPLETEXTSEARCH_BOHR_H
#define MULTIPLESAMPLETEXTSEARCH_BOHR_H

#include "BohrNode.h"
#include "BohrResult.h"
#include "TextFilePosition.h"
#include <string>
#include <vector>
#include <fstream>

class Bohr
{
public:
	Bohr();
	void AddSample(std::string_view str);
	std::vector<BohrResult> GetPositions(std::ifstream & input);

private:
	BohrNode * m_rootNode;
	std::vector<std::string> m_samples;

	std::vector<std::string_view> FindSamples(BohrNode * node);
	BohrNode * GetSuffixLink(BohrNode * node);
	BohrNode * GetAutoMove(BohrNode * node, char ch);
	BohrNode * GetSuffixFineLink(BohrNode * node);
	char ToLowerCase(char ch);
	static TextFilePosition GetSamplePosition(
		std::vector<unsigned long long> const & linesColumnCount,
		TextFilePosition sampleEndPosition,
		unsigned int sampleLength
	);

	
	std::unordered_map<char, char> m_lowerCaseMap = {
		{-64, -32},
		{-63, -31},
		{-62, -30},
		{-61, -29},
		{-60, -28},
		{-59, -27},
		{-88, -72},
		{-58, -26},
		{-57, -25},
		{-56, -24},
		{-55, -23},
		{-54, -22},
		{-53, -21},
		{-52, -20},
		{-51, -19},
		{-50, -18},
		{-49, -17},
		{-48, -16},
		{-47, -15},
		{-46, -14},
		{-45, -13},
		{-44, -12},
		{-43, -11},
		{-42, -10},
		{-41, -9},
		{-40, -8},
		{-39, -7},
		{-38, -6},
		{-37, -5},
		{-36, -4},
		{-35, -3},
		{-34, -2},
		{-33, -1},
	};
};

#endif //MULTIPLESAMPLETEXTSEARCH_BOHR_H
