#include "Advent_of_code.h"
#include <fstream>
#include <string>
#include <iostream>

void FindSeat(std::string data, unsigned int min, unsigned int max, unsigned int &row)
{
	if (!data.empty())
	{
		if (data.size() == 1)
			row = (data[0] == 'F' || data[0] == 'L' ? min : max);
		else
			data[0] == 'F' || data[0] == 'L' ? FindSeat(data.substr(1, data.size()), min, max-(max - min+1) / 2, row) : FindSeat(data.substr(1, data.size()), min+(max-min+1)/2, max, row);
	}

}
void Dec05::Puzzle()
{
	std::string line = "";
	std::ifstream file("Dec05_PuzzleInput.txt");

	unsigned int seats[128*8]{ 0 };
	if (file.is_open())
	{
		unsigned int max = 0;
		while (std::getline(file, line))
		{
			unsigned int row = 0;
			unsigned int column = 0;
			FindSeat(line.substr(0, 7), 0, 127, row);
			FindSeat(line.substr(7, 10), 0, 7, column);
			unsigned id = row * 8 + column;
			seats[row*8+column] = id;
			max = id > max ? id : max;
		}
		std::cout << max << std::endl;
		for (int i = 1; i < sizeof(seats) / sizeof(seats[0]) - 1; i++)
			if (seats[i] == 0 && seats[i - 1] != 0 && seats[i + 1] != 0)
				std::cout << seats[i+1]-1 << std::endl;
	}
	return;
}