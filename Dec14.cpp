#include "Advent_of_code.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <bitset>
#include <unordered_map>

struct Command
{
	int maskindex = 0;
	int memindex = 0;
	int value = 0;
};

void RecursivePermutation(std::vector<std::bitset<36>>& permutations, std::bitset<36> mask, int index, bool value)
{
	mask[index] = value;
	for (int i = index+1; i < mask.size(); i++)
	{
		if (mask[i] == true)
		{
			RecursivePermutation(permutations, mask, i, true);
			RecursivePermutation(permutations, mask, i, false);
			return;
		}
	}
	permutations.push_back(mask);
}

// Recursivly fill vector with permutations of supplied mask
void Permutations(std::vector<std::bitset<36>>& permutations, std::bitset<36> mask)
{
	for (int i = 0; i < mask.size(); i++)
	{
		if (mask[i] == true)
		{
			RecursivePermutation(permutations, mask, i, true);
			RecursivePermutation(permutations, mask, i, false);
			break;
		}
	}
}

void Dec14::Puzzle()
{
	std::vector<std::bitset<36>> bitsets;
	std::vector<std::bitset<36>> positivemasks;
	std::vector<std::bitset<36>> negativemasks;
	std::vector<std::bitset<36>> floatingmasks;
	std::vector<Command> commands;
	int maxmem = 1;
	int maskindex = -1;
	std::string line = "";
	std::ifstream file("Dec14_PuzzleInput.txt");

	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			std::stringstream ss(line);
			std::string s;
			while (ss >> s)
			{
				if (s == "mask")
				{
					ss >> s; 
					ss >> s;
					std::bitset<36> posmask = 0;
					std::bitset<36> negmask = 0;
					std::bitset<36> floatingmask = 0;

					for (int i = 0; i < s.size(); i++)
					{
						posmask <<= 1;
						negmask <<= 1;
						floatingmask <<= 1;

						if (s[i] == '1')
							posmask |= 0b1;
						else if (s[i] == '0')
							negmask |= 0b1;
						else if (s[i] == 'X')
							floatingmask |= 0b1;
					}
					positivemasks.push_back(posmask);
					negativemasks.push_back(negmask);
					floatingmasks.push_back(floatingmask);
					maskindex++;
				}
				else
				{
					Command i;
					i.maskindex = maskindex;
					s.erase(s.size() - 1, s.size());
					i.memindex = std::stoi(s.substr(4, s.size()));
					if (i.memindex > maxmem)
						maxmem = i.memindex;
					ss >> s;
					ss >> i.value; 
					commands.push_back(i);
				}
			}
		}
	}

	// Part 1
	std::bitset<36>* part1 = new std::bitset<36>[maxmem+1] {0};
	for (auto command : commands)
	{
		long value = command.value;
		std::bitset<36> posmask = positivemasks[command.maskindex];
		std::bitset<36> negmask = negativemasks[command.maskindex];
		std::bitset<36> result = std::bitset<36>(value) | posmask;
		std::bitset<36> result2 = std::bitset<36>(result) & ~negmask;
		part1[command.memindex] = result2;
	}
	unsigned long long total = 0;
	for (int i = 0; i <= maxmem; i++)
	{
		if (part1[i] != 0)
		{
			total += part1[i].to_ullong();
		}
	}
	delete[] part1;
	std::cout << "Part1: " << total << "\n";

	// Part 2
	std::unordered_map<std::bitset<36>, long> part2;
	for (auto command : commands)
	{
		long value = command.value;
		std::bitset<36> posmask = positivemasks[command.maskindex];
		std::bitset<36> floatmask = floatingmasks[command.maskindex];
		std::bitset<36> result = std::bitset<36>(command.memindex) | posmask;
		std::bitset<36> result2 = std::bitset<36>(result) & ~floatmask;
		
		std::vector<std::bitset<36>> permutations;
		Permutations(permutations, floatmask);
		for (auto p : permutations)
		{
			unsigned long long index = (p | result2).to_ullong();
			part2[index] = value;
		}
	}
	total = 0;
	for (auto pair : part2)
	{
		total += pair.second;
	}
	std::cout << "Part2: " << total << "\n";
	return;
}