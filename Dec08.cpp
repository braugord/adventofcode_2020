#include "Advent_of_code.h"
#include <string>
#include <fstream>
#include <vector>
#include <iostream>

struct Instruction
{
	std::string command;
	signed int value;
};

int Puzzle1(std::vector<Instruction>& instructions)
{
	int index = 0;
	int accumulator = 0;
	bool* hasRun = new bool[instructions.size()]{ false };
	while (!hasRun[index])
	{
		hasRun[index] = true;
		if (instructions[index].command == "nop")
		{
			index++;
		}
		else if (instructions[index].command == "acc")
		{
			accumulator += instructions[index].value;
			index++;
		}
		else if (instructions[index].command == "jmp")
		{
			index += instructions[index].value;
		}
	}
	return accumulator;
}
int Puzzle2(std::vector<Instruction>& instructions)
{
	int* lastRun = new int[instructions.size()]{ -1 };
	for (int i = 0; i < instructions.size(); i++)
	{
		int index = 0;
		int accumulator = 0;

		if (instructions[i].command == "acc")
			continue;

		(instructions[i].command == "nop" ? instructions[i].command = "jmp" : instructions[i].command = "nop");

		while (lastRun[index] != i)
		{
			if (index == instructions.size() - 1)
				return accumulator;

			lastRun[index] = i;
			if (instructions[index].command == "nop")
			{
				index++;
			}
			else if (instructions[index].command == "acc")
			{
				accumulator += instructions[index].value;
				index++;
			}
			else if (instructions[index].command == "jmp")
			{
				index += instructions[index].value;
			}
		}

		(instructions[i].command == "nop" ? instructions[i].command = "jmp" : instructions[i].command = "nop");
	}
	return -1;
}


void Dec08::Puzzle()
{
	std::string line = "";
	std::ifstream file("Dec08_PuzzleInput.txt");

	std::vector<Instruction> instructions;
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			instructions.push_back( { line.substr(0, line.find(' ')),
									  std::stoi(line.substr(line.find(' '), line.back())),
								    });
		}
	}

	std::cout << "Puzzle 1: " << Puzzle1(instructions) << std::endl;
	std::cout << "Puzzle 2: " << Puzzle2(instructions) << std::endl;
	return;
}