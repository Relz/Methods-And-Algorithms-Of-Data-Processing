#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include "Input-Library/Input.h"

using namespace std;

struct Relation
{
	Relation(unsigned cityId, unsigned distance)
		: cityId(cityId)
		, distance(distance)
	{

	}

	unsigned cityId;
	unsigned distance;

	bool operator <(Relation const & rhs) const
	{
		return distance < rhs.distance;
	}
};

vector<unsigned> InitializeMinDistances(unsigned vertexCount, unsigned firstVertexIndex);

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

	input.SkipLine();
	
	cout << cityCount  << endl
		<< roadCount << endl
		<< firstCityId << endl
		<< lastCityId << endl;

	vector<unsigned> minDistances = InitializeMinDistances(cityCount, firstCityId);

	set<Relation> relations;
	relations.emplace(Relation(firstCityId, 0));

	unordered_set<unsigned> visitedCities;

	unordered_map<unsigned, set<Relation>> cityIdsRelations;

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

		input.SkipLine();

		cityIdsRelations[sourceCityId].emplace(Relation(destinationCityId, distance));
		cityIdsRelations[destinationCityId].emplace(Relation(sourceCityId, distance));
	}

	while (!relations.empty())
	{
		Relation const & relation = *relations.begin();

		if (visitedCities.find(relation.cityId) != visitedCities.end())
		{
			relations.erase(relation);
			continue;
		}

		set<Relation> const& cityRelations = cityIdsRelations[relation.cityId];
		for (Relation const& cityRelation : cityRelations)
		{
			unsigned newDistance = relation.distance + cityRelation.distance;
			if (newDistance < minDistances[cityRelation.cityId])
			{
				minDistances[cityRelation.cityId] = newDistance;
				relations.emplace(Relation(cityRelation.cityId, newDistance));
			}
		}
		visitedCities.emplace(relation.cityId);

		relations.erase(relation);
	}

	return EXIT_SUCCESS;
}

vector<unsigned> InitializeMinDistances(unsigned vertexCount, unsigned firstVertexIndex)
{
	vector<unsigned> result(vertexCount + 1, UINT_MAX);
	result[firstVertexIndex] = 0;
	return result;
}
