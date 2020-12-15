#include "Advent_of_code.h"
#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <queue>
#include <sstream>

bool FindInPreamble(std::vector<unsigned int>& list)
{
	for (size_t i = list.size()-26; i < list.size() - 2; i++)
	{
		for (size_t j = i + 1; j < list.size() - 1; j++)
		{
			if (list[i] + list[j] == list.back())
			{
				return true;
			}
		}
	}
	return false;
}

std::pair<unsigned int, unsigned int> MinMax(std::vector<unsigned int> &list)
{
	std::pair<unsigned int, unsigned int> result{ UINT_MAX,0 };
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i] < result.first)
			result.first = list[i];
		if (list[i] > result.second)
			result.second = list[i];
	}
	return result;
}
std::pair<unsigned int, unsigned int> FindWeakness(std::vector<unsigned int>& list, unsigned int weakness)
{
	unsigned int total = 0;
	std::pair<int, int> ret{ 0,0 };
	for (int i = 0; i < list.size(); i++)
	{
		for (int j = i ; j < list.size(); j++)
		{
			total += list[j];
			if (total > list.back())
			{
				total = 0;
				break;
			}
			if (total == weakness)
			{
				std::vector<unsigned int> range;
				range.insert(range.begin(), list.begin() + i, list.begin() + j + 1);
				return MinMax(range);
			}
		}
	}
	return  { 0,0 };
}

void Dec09::Puzzle()
{
	std::string line = "";
	std::ifstream file("Dec09_PuzzleInput.txt");
	std::vector<unsigned int> list;

	list.reserve(512);
	unsigned int weakness = 0;
	unsigned int encryptionWeakness = 0;
	if (file.is_open())
	{
		
		while (std::getline(file, line))
		{
			auto value = std::stoull(line);
			list.push_back(static_cast<unsigned int>(value));
			if (!weakness)
				if (list.size() > 26)
					if (!FindInPreamble(list))
						weakness = list.back();
		}
		auto pair = FindWeakness(list, weakness);
		encryptionWeakness = pair.first + pair.second;
	}
}