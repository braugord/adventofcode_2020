#include "Advent_of_code.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

struct Bag
{
    std::vector<std::pair<int, Bag*>> bags;
};

bool Contains(Bag* bag, Bag* target)
{
    for (auto b : bag->bags)
    {
        if (b.second == target)
            return true;

        if (Contains(b.second, target))
            return true;
    }
    return false;
}

int BagCount(Bag* bag)
{
    int count = 0;
    for (auto b : bag->bags)
    {
        count += b.first;
        count += b.first * BagCount(b.second);
    }
    return count;
}

void Dec07::Puzzle()
{
    std::string line = "";
    std::ifstream file("Dec07_PuzzleInput.txt");
    std::unordered_map<std::string, Bag> bags;

    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            std::string key = line.substr(0, line.find("bags")-1);
            line.erase(0, line.find("bags") + 13);
            line.replace(line.find('.'), 1, ",");
            while (!line.empty())
            {
                std::string number = line.substr(0, line.find(' '));
                if (number == "no")
                    line.clear();
                else
                {
                    std::string bag = line.substr(line.find(' ')+1, line.find("bag")-3);
                    bags[key].bags.push_back({std::stoi(number), &bags[bag]});
                    line.erase(0, line.find(',') + 2);
                }
            }
        }
        int count = 0;
        for (auto pair : bags)
        {
            if (Contains(&pair.second, &bags["shiny gold"]))
            {
                count++;
            }
        }
        
        std::cout << count << std::endl;
        std::cout << BagCount(&bags["shiny gold"]) << std::endl;
    }

}