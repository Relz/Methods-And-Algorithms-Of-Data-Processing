/*
 Алгоритм Дейкстры на бинарной куче.
 Алексей Старовойтов, Илья Романов.
 Протестировано на Windows 10 (Build 1909), ArchLinux (Linux 5.5.8-arch1-1).
 Проект является CMake-проектом (Поддерживается в Visual Studio 2017+).
 Чтобы собрать программу на Windows, нужно запустить Visual Studio, открыть директорию проекта и собрать проект,
 используя возможности IDE. Собранная программа будет находиться в директории "out/build/(Debug|Release)".
 Пример использования:
 1. С выводом в консоль:
 ./DijkstraAlgorithmViaBinaryHeap input.txt
 2. С выводом в файл:
 ./DijkstraAlgorithmViaBinaryHeap input.txt >> output.txt
*/

#include "Input-Library/Input.h"
#include "Relation/Relation.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

std::vector<unsigned> InitializeMinDistances(unsigned vertexCount, unsigned firstVertexIndex);
std::vector<unsigned> InitializePreviousCities(unsigned vertexCount, unsigned firstVertexIndex);
std::vector<unsigned> GetMinWay(unsigned firstCityId, unsigned lastCityId, std::vector<unsigned> const & previousCities);
template<typename T>
void PrintVector(std::vector<T> const & vector, std::string const & separator);

int main(int argc, char * argv[])
{
	try
	{
		if (argc != 2)
		{
			std::cerr << "Usage: DijkstraAlgorithmViaBinaryHeap <input file>" << std::endl;
			return EXIT_FAILURE;
		}
		std::string inputFileName
			= argv[1]; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic): Use span when C++20 become available
		Input input(inputFileName);

		unsigned cityCount;
		if (!input.ReadArguments(false, cityCount))
		{
			std::cerr << "Unable to read city count from input." << std::endl;
			return EXIT_FAILURE;
		}

		unsigned roadCount;
		if (!input.ReadArguments(false, roadCount))
		{
			std::cerr << "Unable to read road count from input." << std::endl;
			return EXIT_FAILURE;
		}

		unsigned firstCityId;
		if (!input.ReadArguments(false, firstCityId))
		{
			std::cerr << "Unable to read first city id from input." << std::endl;
			return EXIT_FAILURE;
		}

		unsigned lastCityId;
		if (!input.ReadArguments(false, lastCityId))
		{
			std::cerr << "Unable to read last city id from input." << std::endl;
			return EXIT_FAILURE;
		}

		input.SkipLine();

		std::vector<unsigned> minDistances = InitializeMinDistances(cityCount, firstCityId);
		std::vector<unsigned> previousCities = InitializePreviousCities(cityCount, firstCityId);

		std::unordered_map<unsigned, std::vector<Relation>> cityIdsRelations;

		for (unsigned i = 0; i < roadCount; ++i)
		{
			unsigned sourceCityId;
			if (!input.ReadArguments(false, sourceCityId))
			{
				std::cerr << "Unable to read source city id, line: " << (i + 1) << std::endl;
				return EXIT_FAILURE;
			}

			unsigned destinationCityId;
			if (!input.ReadArguments(false, destinationCityId))
			{
				std::cerr << "Unable to read destination city id, line: " << (i + 1) << std::endl;
				return EXIT_FAILURE;
			}

			unsigned distance;
			if (!input.ReadArguments(false, distance))
			{
				std::cerr << "Unable to read distance, line: " << (i + 1) << std::endl;
				return EXIT_FAILURE;
			}

			input.SkipLine();

			cityIdsRelations[sourceCityId].emplace_back(Relation(destinationCityId, distance));
			cityIdsRelations[destinationCityId].emplace_back(Relation(sourceCityId, distance));
		}

		std::vector<Relation> relations{ Relation(firstCityId, 0) };
		std::make_heap(relations.begin(), relations.end(), std::greater<>{});

		std::unordered_set<unsigned> visitedCities;

		while (!relations.empty())
		{
			pop_heap(relations.begin(), relations.end(), std::greater<>{});
			Relation relation = relations.back();
			relations.pop_back();

			if (visitedCities.find(relation.GetCityId()) != visitedCities.end())
			{
				continue;
			}

			std::vector<Relation> const & cityRelations = cityIdsRelations[relation.GetCityId()];
			for (Relation const & cityRelation : cityRelations)
			{
				unsigned newDistance = relation.GetDistance() + cityRelation.GetDistance();
				if (newDistance < minDistances[cityRelation.GetCityId()])
				{
					minDistances[cityRelation.GetCityId()] = newDistance;
					previousCities[cityRelation.GetCityId()] = relation.GetCityId();
					relations.emplace_back(Relation(cityRelation.GetCityId(), newDistance));
					push_heap(relations.begin(), relations.end(), std::greater<>{});
				}
			}
			visitedCities.emplace(relation.GetCityId());
		}

		std::vector<unsigned> minWay = GetMinWay(firstCityId, lastCityId, previousCities);
		std::cout << minDistances[lastCityId] << std::endl;
		PrintVector(minWay, " ");
		std::cout << std::endl;

		return EXIT_SUCCESS;
	}
	catch (std::exception & exception)
	{
		std::cerr << exception.what() << std::endl;
		return EXIT_FAILURE;
	}
}

std::vector<unsigned> InitializeMinDistances(unsigned vertexCount, unsigned firstVertexIndex)
{
	std::vector<unsigned> result(vertexCount + 1, std::numeric_limits<unsigned>::max());
	result[firstVertexIndex] = 0;
	return result;
}

std::vector<unsigned> InitializePreviousCities(unsigned vertexCount, unsigned firstVertexIndex)
{
	std::vector<unsigned> result(vertexCount + 1, std::numeric_limits<unsigned>::max());
	result[firstVertexIndex] = 0;
	return result;
}

std::vector<unsigned> GetMinWay(unsigned firstCityId, unsigned lastCityId, std::vector<unsigned> const & previousCities)
{
	std::vector<unsigned> result;

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
void PrintVector(std::vector<T> const & vector, std::string const & separator)
{
	for (size_t i = 0; i < vector.size(); ++i)
	{
		std::cout << vector[i];
		if (i != vector.size() - 1)
		{
			std::cout << separator;
		}
	}
}
