#include "Advent_of_code.h"
#include <iostream>
#include <fstream>
#include <string>

void Dec06::Puzzle1()
{
    std::string line = "";
    std::ifstream file("Dec06_PuzzleInput.txt");

    int total = 0;
    int combined = 0;

    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            for (char c : line)
                combined |= (1 << (c % 97));

            if (line.empty() || file.eof())
            {
                while (combined > 0)
                {
                    if (combined & 0b1)
                        total++;
                    combined >>= 1;
                }
            }
        }
    }
    std::cout << total << std::endl;
}

void Dec06::Puzzle2()
{
    std::string line = "";
    std::ifstream file("Dec06_PuzzleInput.txt");

    int total = 0;
    int combined = 0;
    int base = 0;
    bool newGroup = true;
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            if (newGroup)
            {
                for (char c : line)
                    base |= (1 << (c % 97));
                newGroup = false;
            }
            else
            {
                for (char c : line)
                    combined |= (1 << (c % 97));

                if (combined != 0)
                {
                    base &= combined;
                    combined = 0;
                }
            }

            if (line.empty() || file.eof())
            {
                while (base > 0)
                {
                    if (base & 0b1)
                        total++;
                    base >>= 1;
                }
                base = 0;
                newGroup = true;
            }
        }
    }
    //std::cout << total << std::endl;
}