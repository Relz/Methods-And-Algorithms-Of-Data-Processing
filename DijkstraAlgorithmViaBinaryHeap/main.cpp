#include <iostream>
#include <string>
#include "Input-Library/Input.h"

using namespace std;

int main()
{
	Input input("INPUT.TXT");

	unsigned cityCount;
	if (!input.ReadArguments(false, cityCount))
	{
		cerr << "Unable to read city count from input." << endl;
		return EXIT_FAILURE;
	}

	unsigned roadCount;
	if (!input.ReadArguments(false, roadCount))
	{
		cerr << "Unable to read road count from input." << endl;
		return EXIT_FAILURE;
	}

	unsigned firstCityId;
	if (!input.ReadArguments(false, firstCityId))
	{
		cerr << "Unable to read first city id from input." << endl;
		return EXIT_FAILURE;
	}

	unsigned lastCityId;
	if (!input.ReadArguments(false, lastCityId))
	{
		cerr << "Unable to read last city id from input." << endl;
		return EXIT_FAILURE;
	}
	
	cout << cityCount  << endl
		<< roadCount << endl
		<< firstCityId << endl
		<< lastCityId << endl;

	for (unsigned i = 0; i < roadCount; ++i)
	{
		unsigned sourceCityId;
		if (!input.ReadArguments(false, sourceCityId))
		{
			cerr << "Unable to read source city id, line: " << (i + 1) << endl;
			return EXIT_FAILURE;
		}

		unsigned destinationCityId;
		if (!input.ReadArguments(false, destinationCityId))
		{
			cerr << "Unable to read destination city id, line: " << (i + 1) << endl;
			return EXIT_FAILURE;
		}

		unsigned distance;
		if (!input.ReadArguments(false, distance))
		{
			cerr << "Unable to read distance, line: " << (i + 1) << endl;
			return EXIT_FAILURE;
		}
	}

	return EXIT_SUCCESS;
}
