#include "Advent_of_code.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>


typedef	std::vector<int> Ticket;

struct Property
{
	int index = -1;
	std::string name;
	std::vector<std::pair<int, int>> ranges;
};

bool ValidateValue(int value, Property& property)
{
	for (auto pair : property.ranges)
	{
		if (value >= pair.first && value <= pair.second)
		{
			//printf("Value: %d IS in range of %d - %d \n", value, pair.first, pair.second);
			return true;

		}
	}
	//printf("Value: %d IS NOT in range of %s \n", value, name.c_str());
	return false;
}

bool ValidateProperty(Ticket& ticket, Property& property)
{
	for (auto value : ticket)
	{
		bool good = false;
		for (auto pair : property.ranges)
		{
			if (value >= pair.first && value <= pair.second)
			{
				good = true;
				break;
			}
		}
		if (good == false)
			return false;
	}
	return true;
}

void Dec16::Puzzle()
{
	std::ifstream file("Dec16_PuzzleInput.txt");

	// Key(ID) : Value(N x (min,max))
	std::unordered_map<std::string, Property> properties;
	std::vector<Ticket> tickets;

	if (file.is_open())
	{
		std::string line = "";
		while (std::getline(file, line))
		{
			if (line.empty())
				break;

			std::stringstream ss(line);
			std::string key;
			std::getline(ss, key, ':');
			std::string range;
			while (std::getline(ss, range, ' '))
			{
				size_t delim = range.find("-");
				if (delim != std::string::npos)
				{
					std::string r1 = range.substr(0, delim);
					std::string r2 = range.substr(delim+1, range.size());
					std::pair<int, int> pair { std::stoi(r1), std::stoi(r2) };
					properties[key].ranges.push_back(pair);
					properties[key].name = key;
				}
			}
		}
		while (std::getline(file, line))
		{
			if (line.find("ticket") != std::string::npos || line.empty())
				continue;

			std::stringstream ss(line);
			std::string value;
			Ticket ticket;
			while (std::getline(ss, value, ','))
			{
				ticket.push_back(std::stoi(value));
			}
			tickets.push_back(ticket);
		}
	}

	std::vector<int> invalid_values; // Part 1
	std::vector<Ticket> valid_tickets; // Part 2
	for (auto ticket : tickets)
	{
		bool validTicket = true;
		for (auto value : ticket)
		{
			bool validProperty = false;
			for (auto property : properties)
			{
				if (ValidateValue(value, property.second))
				{
					validProperty = true;
					break;
				}
			}

			if (!validProperty)
			{
				invalid_values.push_back(value); // Part 1
				validTicket = false;
			}
			
		}
		if(validTicket)
			valid_tickets.push_back(ticket); // Part 2
	}
	
	// Part 1 Result
	unsigned long long sum = 0;
	for (auto value : invalid_values)
	{
		sum += value;
	}
	std::cout << "Part1: " << sum << "\n";

	// While available index we go trough to find key index on tickets that 
	// only fits a single properties ranges, set said index to taken then keep
	// going reducing the different options for each property each cycle
	std::vector<bool> available_index(valid_tickets[0].size(), true);
	while (std::count(available_index.begin(), available_index.end(), true) > 0)
	{
		for (auto &property : properties)
		{
			//printf("\n PROPERTY %s \n", property.second.name.c_str());
			std::vector<bool> valid_index(available_index);
			for (int i = 0; i < valid_index.size(); i++)
			{
				if (!valid_index[i])
					continue;

				for (auto ticket : valid_tickets)
				{
					if (!ValidateValue(ticket[i], property.second))
					{
						valid_index[i] = false;
						break;
					}
				}
			}

			int count = std::count(valid_index.begin(), valid_index.end(), true);
			for (int i = 0; i < valid_index.size(); i++)
			{
				if (valid_index[i])
				{
					if (count == 1)
					{
						//std::cout << " ### Index " << i << " IS property " << property.second.name << " ### \n";
						property.second.index = i;
						available_index[i] = false;
					}
					else
					{
						//std::cout << "Index " << i << " is valid for property " << property.second.name << "\n";
					}
				}
			}
		}
	}

	// Part 2 Result
	sum = 1;
	Ticket myticket = tickets[0];
	for (auto property : properties)
	{
		if (property.second.name.find("departure") != std::string::npos)
		{
			sum *= myticket[property.second.index];
		}
	}
	std::cout << "Part2: " << sum << "\n";
	return;
}