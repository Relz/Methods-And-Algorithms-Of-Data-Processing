#include "Bohr.h"
#include <unordered_set>

Bohr::Bohr()
{
	m_rootNode = new BohrNode();
}

void Bohr::AddSample(std::string_view sample)
{
	BohrNode * node = m_rootNode;
	for (char ch : sample)
	{
		char lowerCasedChar = ToLowerCase(ch);
		if (node->childrenMap.find(lowerCasedChar) == node->childrenMap.end())
		{
			node->childrenMap.emplace(lowerCasedChar, new BohrNode(lowerCasedChar, node));
		}
		node = node->childrenMap.at(lowerCasedChar);
	}
	node->sample = sample;
	m_samples.emplace_back(sample);
}

std::vector<BohrResult> Bohr::GetPositions(std::ifstream & input)
{
	std::vector<BohrResult> result;
	std::unordered_set<std::string> foundSamples;

	BohrNode * node = m_rootNode;
	std::vector<unsigned long long> linesColumnCount;
	bool processEndOfLine = false;
	char ch;
	unsigned long long line = 1;
	unsigned long long column = 1;
	unsigned long long absolutePosition = 1;
	while (input.get(ch))
	{
		if (ch == '\n')
		{
			processEndOfLine = true;
			ch = ' ';
		}
		node = GetAutoMove(node, ch);
		std::vector<std::string_view> samples = FindSamples(node);
		for (std::string_view sample : samples)
		{
			TextFilePosition samplePosition
				= GetSamplePosition(linesColumnCount, TextFilePosition(line, column, absolutePosition), sample.length());
			result.emplace_back(BohrResult(samplePosition, sample));
			foundSamples.emplace(sample);
		}
		if (processEndOfLine)
		{
			processEndOfLine = false;
			++line;
			linesColumnCount.emplace_back(column);
			column = 1;
		}
		else
		{
			++column;
		}
		++absolutePosition;
	}

	unsigned long long constexpr maxUnsignedLongLong = std::numeric_limits<unsigned long long>::max();
	TextFilePosition NonePosition = TextFilePosition(maxUnsignedLongLong, maxUnsignedLongLong, maxUnsignedLongLong);
	for (std::string const & sample : m_samples)
	{
		if (!foundSamples.contains(sample))
		{
			result.emplace_back(BohrResult(NonePosition, sample));
		}
	}
	return result;
}

BohrNode * Bohr::GetAutoMove(BohrNode * node, char ch)
{
	char lowerCasedChar = ToLowerCase(ch);
	if (!node->autoMove.contains(lowerCasedChar))
	{
		node->autoMove.emplace(
			lowerCasedChar,
			node->childrenMap.contains(lowerCasedChar)
				? node->childrenMap.at(lowerCasedChar)
				: node == m_rootNode ? m_rootNode : GetAutoMove(GetSuffixLink(node), lowerCasedChar));
	}
	return node->autoMove[lowerCasedChar];
}

BohrNode * Bohr::GetSuffixLink(BohrNode * node)
{
	if (node->suffixLink == nullptr)
	{
		node->suffixLink = node == m_rootNode || node->parentNode == m_rootNode
			? m_rootNode
			: GetAutoMove(GetSuffixLink(node->parentNode), node->value);
	}
	return node->suffixLink;
}

std::vector<std::string_view> Bohr::FindSamples(BohrNode * node)
{
	std::vector<std::string_view> result;

	BohrNode * currentNode = node;
	while (currentNode != m_rootNode)
	{
		if (!currentNode->sample.empty())
		{
			result.emplace_back(currentNode->sample);
		}
		currentNode = GetSuffixFineLink(currentNode);
	}
	return result;
}

BohrNode * Bohr::GetSuffixFineLink(BohrNode * node)
{
	if (node->suffixFineLink == nullptr)
	{
		BohrNode * newNode = GetSuffixLink(node);
		node->suffixFineLink
			= newNode == m_rootNode ? m_rootNode : newNode->sample.empty() ? GetSuffixFineLink(newNode) : newNode;
	}
	return node->suffixFineLink;
}

char Bohr::ToLowerCase(char ch)
{
	return m_lowerCaseMap.contains(ch) ? m_lowerCaseMap.at(ch) : ch;
}

TextFilePosition Bohr::GetSamplePosition(
	std::vector<unsigned long long> const & linesColumnCount,
	TextFilePosition sampleEndPosition,
	unsigned int sampleLength)
{
	TextFilePosition resultPosition = sampleEndPosition;
	size_t restSampleLength = sampleLength - 1;
	while (restSampleLength != 0)
	{
		--resultPosition.column;
		if (resultPosition.column == 0)
		{
			--resultPosition.line;
			resultPosition.column = linesColumnCount[resultPosition.line - 1];
		}
		--restSampleLength;
	}
	resultPosition.absolutePosition -= sampleLength - 1;

	return resultPosition;
}
