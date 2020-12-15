#include "Advent_of_code.h"
#include <string>
#include <fstream>
#include <vector>



char FindSeat(std::vector<std::string>& in, int x, int y, int x_dir, int y_dir)
{
	while (in[y][x] == '.')
	{
		x += x_dir;
		y += y_dir;
		if (y < 0 || y >= in.size() || x<0 || x>in[y].size())
		{
			return '.';
		}
	}
	return in[y][x];
}
char EvolveSeat(std::vector<std::string>& in, int x_in, int y_in, bool vision, int limit)
{
	if (in[y_in][x_in] == '.')
		return '.';

	int count = 0;
	for (int y = y_in-1; y <= y_in+1; y++)
	{
		for (int x = x_in-1; x <= x_in+1; x++)
		{
			if (y < 0 || y >= in.size() || x<0 || x>in[y].size() || (x == x_in && y == y_in))
				continue;

			if (vision)
			{
				if (FindSeat(in, x, y, x-x_in, y-y_in) == '#')
				{
					count++;
				}
			}
			else
			{
				if (in[y][x] == '#')
					count++;
			}
		}
	}
	if (in[y_in][x_in] == '#')
		return (count >= limit ? 'L' : '#');
	if(in[y_in][x_in] == 'L')
		return (count == 0 ? '#' : 'L');

	return false;
}
bool EvolveLayout(std::vector<std::string>& in, std::vector<std::string>& out, bool vision, int limit)
{
	bool changed = false;
	for (int y = 0; y<in.size();y++)
	{
		for (int x = 0; x < in[y].size(); x++)
		{
			out[y][x] = EvolveSeat(in, x, y, vision, limit);
			if (in[y][x] != out[y][x])
				changed = true;
		}
	}
	return changed;
}

int CountLayout(std::vector<std::string>& in, char comparison)
{
	int count = 0;
	for (int y = 0; y < in.size(); y++)
	{
		for (int x = 0; x < in[y].size(); x++)
		{
			if (in[y][x] == comparison)
				count++;
		}
	}
	return count;
}

void DrawLayout(std::vector<std::string>& in)
{
	printf("\n Draw \n");
	for (std::string str : in)
	{
		printf("%s \n", str.c_str());
	}
}

void Dec11::Puzzle()
{
	std::string line = "";
	std::ifstream file("Dec11_PuzzleInput.txt");
	
	std::vector<std::string> in;
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			in.push_back(line);
		}
	}
	std::vector<std::string> out(in);

	//DrawLayout(in); // Debug
	while (EvolveLayout(in, out, true, 5))
	{
		in = out;
		//DrawLayout(in); // Debug
	}
	//DrawLayout(out); // Debug
	int tally = CountLayout(out,'#');
	return;
}
