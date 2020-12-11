#include "Advent_of_code.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

void Dec03::Puzzle1()
{
	std::vector<char> grid;
	std::string line = "";
	std::ifstream file("Dec03_PuzzleInput.txt");
	size_t width = 0;
	size_t height = 0;
	if (file.is_open())
	{
		std::getline(file, line);
		width = line.size();
		do
		{
			for (int i = 0; i < line.size(); i++)
			{
				grid.push_back(line[i]);
			}
		} while (std::getline(file, line));
		height = grid.size() / width;

		int x = 0;
		int y = 0;
		int trees = 0;
		while (y < height-1)
		{
			x += 3;
			y++;
			
			size_t index = (x % width) + y * width;
			if (grid[index] == '#')
			{
				trees++;
			}
		}
		std::cout << trees << std::endl;
	}
}

void Dec03::Puzzle2()
{
	std::vector<char> grid;
	std::string line = "";
	std::ifstream file("Dec03_PuzzleInput.txt");
	size_t width = 0;
	size_t height = 0;
	if (file.is_open())
	{
		std::getline(file, line);
		width = line.size();
		do
		{
			for (int i = 0; i < line.size(); i++)
			{
				grid.push_back(line[i]);
			}
		} while (std::getline(file, line));
		height = grid.size() / width;

		
		unsigned int totaltrees = 1;
		std::vector<std::pair<int, int>> traversal{ {1,1}, 
													{3,1}, 
													{5,1}, 
													{7,1}, 
													{1,2} };
		for (std::pair<int, int> pair : traversal)
		{
			int x = 0;
			int y = 0;
			int trees = 0;
			while (y < height - 1)
			{
				x += pair.first;
				y += pair.second;

				size_t index = (x % width) + y * width;
				if (grid[index] == '#')
				{
					trees++;
				}
			}
			totaltrees *= trees;
			std::cout << trees << std::endl;
		}
		std::cout << totaltrees << std::endl;
	}
}