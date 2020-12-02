#include "Advent_of_code.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void Dec01::Puzzle1()
{
	std::vector<int> numbers;
	std::string line = "";
	std::ifstream file("Dec01_PuzzleInput.txt");
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			numbers.push_back(std::stoi(line));
		}
	}
	for (int i = 0; i < numbers.size()-1; i++)
	{
		for (int j = i + 1; j < numbers.size(); j++)
		{
			if (numbers[i] + numbers[j] == 2020)
			{
				std::cout << numbers[i] * numbers[j] << std::endl;
			}
		}
	}
}

void Dec01::Puzzle2()
{
	std::vector<int> numbers;
	std::string line = "";
	std::ifstream file("Dec01_PuzzleInput.txt");
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			numbers.push_back(std::stoi(line));
		}
	}
	for (int i = 0; i < numbers.size() - 2; i++)
	{
		for (int j = i + 1; j < numbers.size() - 1; j++)
		{
			for (int k = j + 1; k < numbers.size(); k++)
			{
				if (numbers[i] + numbers[j] + numbers[k] == 2020)
				{
					std::cout << numbers[i] * numbers[j] * numbers[k] << std::endl;
				}
			}
		}
	}
}