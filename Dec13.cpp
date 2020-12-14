#include "Advent_of_code.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include "BigInt.h"

int Part1(int timestamp, std::vector<int>& ids)
{
	int closest = INT_MAX;
	int closestIndex = 0;
	for (int i = 0; i < ids.size(); i++)
	{
		int departure = (timestamp / ids[i] + 1) * ids[i] - timestamp;
		if (departure < closest)
		{
			closest = departure;
			closestIndex = i;
		}
	}
	int result = closest * ids[closestIndex];
	return result;
}

BigInt Part2(std::vector<int>& ids)
{
	std::vector<BigInt> steps(ids.size());
	BigInt step = ids[0];
	int latestindex = 0;

	for (BigInt timestamp = 0; ; timestamp += step)
	{
		if (timestamp % ids[0] == 0)
		{
			int offset = 1;
			for (int j = 1; j <= ids.size(); j++)
			{
				if (j == ids.size())
				{
					return timestamp ;
				}
				if (ids[j] <= 0)
				{
					offset -= ids[j];
					continue;
				}
				if ((timestamp + offset) % ids[j] == 0)
				{
					if (j > latestindex)
					{
						if (steps[latestindex] == 0)
						{
							steps[latestindex] = timestamp;
						}
						else
						{
							if (timestamp != steps[latestindex])
							{
								steps[latestindex] = timestamp - steps[latestindex];
								step = steps[latestindex];
							}
							latestindex = j;
						}
					}
					offset++;
					continue;
				}
				break;
			}
		}
		else
		{
		}
	}
	return -1;
}

void Dec13::Puzzle()
{

	std::string line = "";
	std::ifstream file("Dec13_PuzzleInput.txt");

	int timestamp = 0;
	std::vector<int> part1;
	std::vector<int> part2;

	if (file.is_open())
	{
		std::getline(file, line);
		timestamp = std::stoi(line);
		while (std::getline(file, line))
		{
			std::stringstream ss(line);

			std::string s;
			while (std::getline(ss, s, ',')) {

				if (s[0] == 'x')
				{
					if (part2[part2.size() - 1] < 0)
						part2[part2.size() - 1]--;
					else
						part2.push_back(-1);
				}
				else
				{
					part1.push_back(std::stoi(s));
					part2.push_back(std::stoi(s));
				}
			}
		}
	}

	/*int result1 = Part1(timestamp, part1);
	std::cout << "Part1 " << result1 << std::endl;*/
	BigInt result2 = Part2(part2);
	std::cout << "Part2 = " << result2 << std::endl;

	return;
}