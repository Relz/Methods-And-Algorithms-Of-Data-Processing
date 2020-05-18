/*
 Требуется найти все вхождения любого из образцов в текст.
 Результаты поиска не должны зависеть от регистра букв,
 то есть каждая буква в образце и тексте может быть как строчной, так и прописной.
 Алексей Старовойтов, Илья Романов.
 Протестировано на Windows 10 (Build 1909), ArchLinux (Linux 5.5.8-arch1-1).
 Проект является CMake-проектом (Поддерживается в Visual Studio 2017+).
 Чтобы собрать программу на Windows, нужно запустить Visual Studio, открыть директорию проекта и собрать проект,
 используя возможности IDE. Собранная программа будет находиться в директории "out/build/(Debug|Release)".
 Пример использования:
 1. С выводом в консоль:
 ./MultipleSampleTextSearch input.txt
 2. С выводом в файл:
 ./MultipleSampleTextSearch input.txt >> output.txt
*/

#include "Bohr/Bohr.h"

#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <algorithm>

bool compareBohrResult(BohrResult const & a, BohrResult const & b)
{
	return a.position.absolutePosition < b.position.absolutePosition;
}

int main(int /*argc*/, char * argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	std::string inputFileName = argv[1];
	std::ifstream input(inputFileName);

	Bohr bohr;

	unsigned long sampleCount;
	input >> sampleCount;
	std::string tmp;
	std::getline(input, tmp);
	for (unsigned long sampleIndex = 0; sampleIndex < sampleCount; ++sampleIndex)
	{
		std::string sample;
		std::getline(input, sample);
		bohr.AddSample(sample);
	}
	std::string textFileName;
	std::getline(input, textFileName);

	std::ifstream textFile(textFileName);

	std::vector<BohrResult> positions = bohr.GetPositions(textFile);
	std::sort(positions.begin(), positions.end(), compareBohrResult);
	for (BohrResult const & bohrResult : positions)
	{
		std::cout << bohrResult.position.ToString() << ": " << bohrResult.sample << std::endl;
	}
	std::cout << std::endl;
}
