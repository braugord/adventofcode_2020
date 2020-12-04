#include "Advent_of_code.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>

struct PassPort
{
	std::unordered_map<std::string, std::string> data;

	void ParseKeyValue(std::string keyvalue)
	{
		std::string key = keyvalue.substr(0, keyvalue.find(':'));
		keyvalue.erase(0, key.size() + 1);
		data[key] = keyvalue;
	}

	void ParseData(std::string data)
	{
		while (!data.empty())
		{
			size_t i = (data.find(' '));
			std::string keyvalue = (i == 0) ? data : data.substr(0, i);
			data.erase(0, keyvalue.size()+1);
			ParseKeyValue(keyvalue);
		}
	}

	bool ContainsKeylist()
	{
		static const std::string keylist[]{ {"byr"}, {"iyr"}, {"eyr"}, {"hgt"}, {"hcl"}, {"ecl"}, {"pid"} };
		for (int i = 0; i < sizeof(keylist) / sizeof(keylist[0]); i++)
			if (data[keylist[i]].empty())
				return false;
		return true;
	}

	bool IsValid1()
	{
		return ContainsKeylist();
	}

	bool IsValid2()
	{
		if (!ContainsKeylist())
			return false;
		
		int byr = std::stoi(data["byr"]);
		if (byr < 1920 || byr > 2002)
			return false;

		int iyr = std::stoi(data["iyr"]);
		if (iyr < 2010 || iyr > 2020)
			return false;

		int eyr = std::stoi(data["eyr"]);
		if (eyr < 2020 || eyr > 2030)
			return false;

		std::string unit = data["hgt"].substr(data["hgt"].size() - 2, data["hgt"].size());
		int value = std::stoi(data["hgt"].substr(0, data["hgt"].size()-2));
		if (unit != "cm" && unit != "in")
			return false;
		if (unit == "cm" && (value < 150 || value > 193))
			return false;
		else if (unit == "in" && (value < 59 || value > 76))
			return false;

		if (data["hcl"].size() != 7)
			return false;
		for(int i = 1; i<data["hcl"].size(); i++)
			if (!isxdigit(data["hcl"][i]))
				return false;

		static const std::string eyeColors = "amb blu brn gry grn hzl oth";
		if (eyeColors.find(data["ecl"]) == std::string::npos)
			return false;

		if (data["pid"].size() != 9)
			return false;

		return true;
	}
};

void Dec04::Puzzle()
{
	std::string line = "";
	std::ifstream file("Dec04_PuzzleInput.txt");
	std::vector<PassPort> passports;
	
	if (file.is_open())
	{
		PassPort pp;
		while (std::getline(file, line))
		{
			if (line.empty())
			{
				passports.push_back(pp);
				pp = PassPort();
				continue;
			}
			else
			{
				pp.ParseData(line);
			}
		}
	}

	unsigned int valid1 = 0;
	unsigned int valid2 = 0;

	for (int i = 0; i < passports.size(); i++)
	{
		if(passports[i].IsValid1())
			valid1++;
		if (passports[i].IsValid2())
			valid2++;
	}
	
	std::cout << "Puzzle 1; " << valid1 << std::endl;
	std::cout << "Puzzle 1; " << valid2 << std::endl;
}
