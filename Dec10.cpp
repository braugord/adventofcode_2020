#include "Advent_of_code.h"
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

void Traverse(std::vector<int>& data, int index, int &total)
{
	if (index == data.size() - 1)
		total++;

	for (int i = index+1; i < data.size() && i < index+4; i++)
	{
		if (data[i] - data[index] <= 3)
			Traverse(data, i, total);
	}
}

int Traverse2(std::vector<int>& data, int index, int &nextblock)
{
	if (index == data.size() - 1 || data[index+1] - data[index] == 3)
	{
		if(index+1 > nextblock)
			nextblock = index+1;
		return 1;
	}
	int count = 0;
	for (int i = index + 1; i < data.size() && i < index + 4; i++)
	{
		if (data[i] - data[index] <= 3)
		{
			count += Traverse2(data, i, nextblock);
		}
	}
	return count;
}

void Dec10::Puzzle()
{
	std::string line = "";
	std::ifstream file("Dec10_PuzzleInput.txt");
	std::vector<int> data;
	data.push_back(0);
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			int value = std::stoi(line);
			data.push_back(value);
		}
		std::sort(data.begin(), data.end());
	}
	data.push_back(data.back() + 3);
	int accumulated[3]{ 0 };
	for (int i = 0; i < data.size() - 1; i++)
	{
		int diff = data[i + 1] - data[i];
		accumulated[diff-1]++;
	}
	int total = (accumulated[0]) * (accumulated[2]);
	total = 0; // puzzle 1
	//Traverse(data, 0, total); // Only worked for small data set
	
	long long final = 1;
	int nextblock = 0;
	while (nextblock != data.size())
	{
		final *= Traverse2(data, nextblock, nextblock);
	}
	return;
}