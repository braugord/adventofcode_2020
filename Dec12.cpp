#include "Advent_of_code.h"
#include <string>
#include <fstream>
#include <vector>

int PartOne(std::vector<std::pair<char, int>>& input)
{
	int x = 0;
	int y = 0;
	int dir = 0;
	for (auto pair : input)
	{
		switch (pair.first)
		{
		case 'E': x += pair.second; break;
		case 'S': y -= pair.second; break;
		case 'W': x -= pair.second; break;
		case 'N': y += pair.second; break;
		case 'L': dir -= pair.second; break;
		case 'R': dir += pair.second; break;
		case 'F':
			switch (dir % 360)
			{
			case -270: y -= pair.second; break;
			case -180: x -= pair.second; break;
			case -90: y += pair.second; break;
			case 0: x += pair.second; break;
			case 90: y -= pair.second; break;
			case 180: x -= pair.second; break;
			case 270: y += pair.second; break;
			default: break;
			} break;
		default: break;
		}
	}
	int manhattan = abs(x) + abs(y);
	return manhattan;
}

int PartTwo(std::vector<std::pair<char, int>>& input)
{
	int x = 0;
	int y = 0;
	int waypoint_x = 10;
	int waypoint_y = 1;
	int dir = 0;
	for (auto pair : input)
	{
		switch (pair.first)
		{
		case 'E': waypoint_x += pair.second; break;
		case 'S': waypoint_y -= pair.second; break;
		case 'W': waypoint_x -= pair.second; break;
		case 'N': waypoint_y += pair.second; break;
		case 'L': 
		{
			for (int i = 0; i != pair.second; i += 90)
			{
				int tmp = waypoint_x;
				waypoint_x = waypoint_y * -1;
				waypoint_y = tmp;
			} break;
		}
		case 'R': 
		{
			for (int i = 0; i != pair.second; i += 90)
			{
				int tmp = waypoint_x;
				waypoint_x = waypoint_y;
				waypoint_y = tmp * -1;
			} break;
		}
		case 'F': x += waypoint_x * pair.second; y += waypoint_y * pair.second; break;
		default: break;
		}
	}
	int manhattan = abs(x) + abs(y);
	return manhattan;
}

void Dec12::Puzzle()
{
	std::string line = "";
	std::ifstream file("Dec12_PuzzleInput.txt");

	std::vector<std::pair<char,int>> input;
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			input.push_back({ line[0],std::stoi(line.substr(1, line.size()))});
		}
	}
	
	int partone = PartOne(input);
	int parttwo = PartTwo(input);

	return;
}