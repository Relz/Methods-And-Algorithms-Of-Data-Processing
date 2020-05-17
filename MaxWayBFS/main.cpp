/*
 Имеется взвешенный ориентированный ациклический граф. Найти максимальный путь, используя поиск в ширину.
 Алексей Старовойтов, Илья Романов.
 Протестировано на Windows 10 (Build 1909), ArchLinux (Linux 5.5.8-arch1-1).
 Проект является CMake-проектом (Поддерживается в Visual Studio 2017+).
 Чтобы собрать программу на Windows, нужно запустить Visual Studio, открыть директорию проекта и собрать проект,
 используя возможности IDE. Собранная программа будет находиться в директории "out/build/(Debug|Release)".
 Пример использования:
 1. С выводом в консоль:
 ./MaxWayBFS input.txt
 2. С выводом в файл:
 ./MaxWayBFS input.txt >> output.txt
*/

#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

struct Result
{
	int maxLength;
	int previousVertex;
};

struct Relation
{
public:
	Relation(int targetVertex, int length)
		: targetVertex(targetVertex)
		, length(length)
	{}

	int targetVertex;
	int length;
};

void InitializeResults(std::vector<Result> results)
{
	for (auto & result : results)
	{
		result = Result();
	}
}

std::vector<int> GetWay(std::vector<Result> results, int endVertex, int startVertex)
{
	std::vector<int> way;

	int currentVertex = endVertex;
	while (currentVertex != startVertex)
	{
		way.insert(way.begin(), currentVertex);
		currentVertex = results[currentVertex].previousVertex;
	}
	way.insert(way.begin(), startVertex);

	return way;
}

int main()
{
	std::ifstream input("input.txt");
	int vertexCount;
	int arcCount;
	int startVertex;
	int endVertex;

	input >> vertexCount;
	input >> arcCount;
	input >> startVertex;
	input >> endVertex;

	std::map<int, std::vector<Relation>> vertexRelations;

	int a;
	int b;
	int c;
	while (input >> a && input >> b && input >> c)
	{
		std::vector<Relation> value({ Relation(b, c) });
		auto const & iter = vertexRelations.find(a);
		if (iter != vertexRelations.end())
		{
			value.insert(value.end(), iter->second.begin(), iter->second.end());
		}
		vertexRelations.insert_or_assign(a, value);
	}

	std::vector<bool> visited(vertexCount + 1);
	visited[startVertex] = true;

	std::vector<Result> results(vertexCount + 1);
	InitializeResults(results);

	std::queue<int> queue;
	queue.push(startVertex);
	while (!queue.empty())
	{
		int currentVertex = queue.front();
		queue.pop();

		std::vector<Relation> relations = (vertexRelations.find(currentVertex) != vertexRelations.end())
			? vertexRelations[currentVertex]
			: std::vector<Relation>();

		for (auto & relation : relations)
		{
			Result currentResult = results[currentVertex];
			Result targetResult = results[relation.targetVertex];
			int possibleNewMaxLength = currentResult.maxLength + relation.length;
			if (possibleNewMaxLength > targetResult.maxLength)
			{
				results[relation.targetVertex].maxLength = possibleNewMaxLength;
				results[relation.targetVertex].previousVertex = currentVertex;
				visited[relation.targetVertex] = false;
			}

			if (!visited[relation.targetVertex])
			{
				queue.push(relation.targetVertex);
				visited[relation.targetVertex] = true;
			}
		}
	}

	if (results[endVertex].maxLength != 0)			if ()

		{
		std::cout << results[endVertex].maxLength << std::endl;
		std::vector<int> way = GetWay(results, endVertex, startVertex);
		for (int i = 0; i < way.size(); ++i)
		{
			std::cout << way[i];
			if (i == way.size() - 1)
			{
				std::cout << std::endl;
			}
			else
			{
				std::cout << " ";
			}
		}
	}
	else
	{
		std::cout << "No." << std::endl;
	}
}