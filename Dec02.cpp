#include "Advent_of_code.h"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

struct Data
{
	int min;
	int max;
	char key;
	std::string password;
};

bool Puzzle1_Verify(Data& data)
{
	int count = 0;
	for (int i = 0; i < data.password.size(); i++)
	{
		if (data.password[i] == data.key)
			count++;
	}
	if (count >= data.min && count <= data.max)
		return true;
	else
		return false;
}

void Dec02::Puzzle1()
{
	std::vector<int> numbers;
	std::string line = "";
	std::ifstream file("Dec02_PuzzleInput.txt");
	if (file.is_open())
	{
		int count = 0;
		while (std::getline(file, line))
		{
			std::string range = line.substr(0, line.find(' '));
			line.erase(0, range.size() + 1);
			std::string chars = line.substr(0, line.find(' '));
			line.erase(0, chars.size()+1);
			std::string password = line.substr(0, line.find(' '));

			std::string min = range.substr(0, range.find('-'));
			range.erase(0, min.size() + 1);
			chars.erase(chars.begin()+1, chars.end());
			Data entry{ std::stoi(min), std::stoi(range), chars[0], password };
			if (Puzzle1_Verify(entry))
			{
				count++;
			}
		}
		std::cout << count << std::endl;
	}
}

bool Puzzle2_Verify(Data& data)
{
	int count = 0;
	for (int i = 0; i < data.password.size(); i++)
	{
		if (i + 1 == data.min || i + 1 == data.max)
		{
			if (data.password[i] == data.key)
				count++;
		}
	}
	if (count == 1)
		return true;
	else
		return false;
}

void Dec02::Puzzle2()
{
	std::vector<int> numbers;
	std::string line = "";
	std::ifstream file("Dec02_PuzzleInput.txt");
	if (file.is_open())
	{
		int count = 0;
		while (std::getline(file, line))
		{
			std::string range = line.substr(0, line.find(' '));
			line.erase(0, range.size() + 1);
			std::string chars = line.substr(0, line.find(' '));
			line.erase(0, chars.size() + 1);
			std::string password = line.substr(0, line.find(' '));

			std::string min = range.substr(0, range.find('-'));
			range.erase(0, min.size() + 1);
			chars.erase(chars.begin() + 1, chars.end());
			Data entry{ std::stoi(min), std::stoi(range), chars[0], password };
			if (Puzzle2_Verify(entry))
			{
				count++;
			}
		}
		std::cout << count << std::endl;
	}
}