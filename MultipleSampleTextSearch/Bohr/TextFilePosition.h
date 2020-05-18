#ifndef MULTIPLESAMPLETEXTSEARCH_TEXTFILEPOSITION_H
#define MULTIPLESAMPLETEXTSEARCH_TEXTFILEPOSITION_H

struct TextFilePosition
{
	TextFilePosition(unsigned long long line, unsigned long long column, unsigned long long absolutePosition)
		: line(line)
		, column(column)
		, absolutePosition(absolutePosition)
	{}

	unsigned long long line;
	unsigned long long column;
	unsigned long long absolutePosition;

	std::string ToString() const
	{
		if (IsNone())
		{
			return "No";
		}
		return "Line " + std::to_string(line) + ", position " + std::to_string(column);
	}

private:
	bool IsNone() const
	{
		unsigned long long constexpr maxUnsignedLongLong = std::numeric_limits<unsigned long long>::max();
		return line == maxUnsignedLongLong && column == maxUnsignedLongLong && absolutePosition == maxUnsignedLongLong;
	}
};

#endif //MULTIPLESAMPLETEXTSEARCH_TEXTFILEPOSITION_H
