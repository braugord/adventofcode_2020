#include "Advent_of_code.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

void Dec15::Puzzle()
{
	std::string line = "";
	std::ifstream file("Dec15_PuzzleInput.txt");
	std::vector<int> input;
	std::unordered_map<int, std::vector<int>> output;
	
	if (file.is_open())
	{
		std::getline(file,line);
		std::stringstream ss(line);
		std::string s;
		while (std::getline(ss, s, ','))
		{
			input.push_back(std::stoi(s));
			int value = std::stoi(s);
		}
	}
	
	int turn = 1;
	int lastSpoken = 0;
	for (int i = 0; i < input.size(); i++, turn++)
	{
		output[input[i]].push_back(turn);
		lastSpoken = input[i];
	}
	
	for (int i = 0; turn <= 30000000; i++, turn++) // Part1: turn <= 2020
	{
		int inputindex = i % input.size();
		if (output[lastSpoken].size() == 1)
		{
			output[0].push_back(turn);
			lastSpoken = 0;
		}
		else
		{
			size_t lastindex = output[lastSpoken].size() - 1;
			int value = output[lastSpoken][lastindex] - output[lastSpoken][lastindex - 1];
			output[value].push_back(turn);
			lastSpoken = value;
		}
	}
	std::cout << "Part2: " << lastSpoken << "\n";
	return;
}