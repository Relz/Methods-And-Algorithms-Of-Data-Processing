#include "Input-Library/Input.h"
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct Relation
{
	Relation(unsigned cityId, unsigned distance)
		: cityId(cityId)
		, distance(distance)
	{}

	unsigned cityId;
	unsigned distance;

	bool operator<(Relation const & rhs) const
	{
		return distance < rhs.distance;
	}
};

vector<unsigned> InitializeMinDistances(unsigned vertexCount, unsigned firstVertexIndex);
vector<unsigned> InitializePreviousCities(unsigned vertexCount, unsigned firstVertexIndex);
vector<unsigned> GetMinWay(
	unsigned firstCityId,
	unsigned lastCityId,
	vector<unsigned> const & minDistances,
	vector<unsigned> const & previousCities);
template<typename T>
void PrintVector(vector<T> const & vector, string const & separator);

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

	vector<unsigned> minDistances = InitializeMinDistances(cityCount, firstCityId);
	vector<unsigned> previousCities = InitializePreviousCities(cityCount, firstCityId);

	set<Relation> relations = { Relation(firstCityId, 0) };
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

		set<Relation> const & cityRelations = cityIdsRelations[relation.cityId];
		for (Relation const & cityRelation : cityRelations)
		{
			unsigned newDistance = relation.distance + cityRelation.distance;
			if (newDistance < minDistances[cityRelation.cityId])
			{
				minDistances[cityRelation.cityId] = newDistance;
				previousCities[cityRelation.cityId] = relation.cityId;
				relations.emplace(Relation(cityRelation.cityId, newDistance));
			}
		}
		visitedCities.emplace(relation.cityId);

		relations.erase(relation);
	}

	vector<unsigned> minWay = GetMinWay(firstCityId, lastCityId, minDistances, previousCities);
	cout << minDistances[lastCityId] << endl;
	PrintVector(minWay, " ");
	cout << endl;

	return EXIT_SUCCESS;
}

vector<unsigned> InitializeMinDistances(unsigned vertexCount, unsigned firstVertexIndex)
{
	vector<unsigned> result(vertexCount + 1, UINT_MAX);
	result[firstVertexIndex] = 0;
	return result;
}

vector<unsigned> InitializePreviousCities(unsigned vertexCount, unsigned firstVertexIndex)
{
	vector<unsigned> result(vertexCount + 1, UINT_MAX);
	result[firstVertexIndex] = 0;
	return result;
}

vector<unsigned> GetMinWay(
	unsigned firstCityId,
	unsigned lastCityId,
	vector<unsigned> const & minDistances,
	vector<unsigned> const & previousCities)
{
	vector<unsigned> result;

	unsigned cityId = lastCityId;
	while (cityId != firstCityId)
	{
		result.insert(result.begin(), cityId);
		cityId = previousCities[cityId];
	}

	result.insert(result.begin(), firstCityId);

	return result;
}

template<typename T>
void PrintVector(vector<T> const & vector, string const & separator)
{
	for (size_t i = 0; i < vector.size(); ++i)
	{
		cout << vector[i];
		if (i != vector.size() - 1)
		{
			cout << separator;
		}
	}
}