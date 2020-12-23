#include "Advent_of_code.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <exception>
#include <iostream>
#include <unordered_map>
#include <regex>

std::vector<std::string> messages;
std::unordered_map<int, std::vector<int>> rules;
std::vector<std::vector<std::string>> permutations;

std::vector<std::string> Traverse(int index, int depth)
{
	std::vector<std::string> ret;

	if (rules[index].size() == 1)
	{
		if (rules[index][0] == -1)
		{
			ret.push_back("a");
			return ret;
		}
		else if (rules[index][0] == -2)
		{
			ret.push_back("b");
			return ret;
		}
		else
		{
			std::vector<std::string> v = Traverse(rules[index][0], depth+1);
			for (int i = 0; i < v.size(); i++)
			{
				ret.push_back(v[i]);
			}
			return ret;
		}
	}

	
		auto delim = std::find(rules[index].begin(), rules[index].end(), -3);
		if(delim == rules[index].end())
		{
			std::vector<std::string> v1 = Traverse(rules[index][0], depth + 1);
			std::vector<std::string> v2 = Traverse(rules[index][1], depth + 1);
			for (int j = 0; j < v1.size(); j++)
			{
				for (int k = 0; k < v2.size(); k++)
				{
					ret.push_back(v1[j] + v2[k]);
				}
			}
		}
		else
		{
			int delimPosition = std::distance(rules[index].begin(), delim);
			int postDelim = (rules[index].size() - 1) - delimPosition;
			if (delimPosition == 1)
			{
				std::vector<std::string> v1 = Traverse(rules[index][delimPosition - 1], depth + 1);
				for (auto s : v1)
					ret.push_back(s);
			}
			else if (delimPosition == 2)
			{
				std::vector<std::string> v1 = Traverse(rules[index][delimPosition - 2], depth + 1);
				std::vector<std::string> v2 = Traverse(rules[index][delimPosition - 1], depth + 1);
				for (int j = 0; j < v1.size(); j++)
				{
					for (int k = 0; k < v2.size(); k++)
					{
						ret.push_back(v1[j] + v2[k]);
					}
				}
			}
			if (postDelim == 1)
			{
				std::vector<std::string> v1 = Traverse(rules[index][delimPosition + 1], depth + 1);
				for (auto s : v1)
					ret.push_back(s);
			}
			else if (postDelim == 2)
			{
				std::vector<std::string> v1 = Traverse(rules[index][delimPosition + 1], depth + 1);
				std::vector<std::string> v2 = Traverse(rules[index][delimPosition + 2], depth + 1);
				for (int j = 0; j < v1.size(); j++)
				{
					for (int k = 0; k < v2.size(); k++)
					{
						ret.push_back(v1[j] + v2[k]);
					}
				}
			}
			else if (postDelim == 3)
			{
				std::vector<std::string> v1 = Traverse(rules[index][delimPosition + 1], depth + 1);
				std::vector<std::string> v2 = Traverse(rules[index][delimPosition + 2], depth + 1);
				std::vector<std::string> v3 = Traverse(rules[index][delimPosition + 3], depth + 1);
				for (int j = 0; j < v1.size(); j++)
				{
					for (int k = 0; k < v2.size(); k++)
					{
						for (int l = 0; l < v2.size(); l++)
						{
							ret.push_back(v1[j] + v2[k] + v2[l]);
						}
					}
				}
			}
		}
	return ret;
}

void TraverseRules()
{
	std::vector<int> start = rules[0];
	
	for (int i = 0; i < start.size(); i++)
	{
		std::vector<std::string> v = Traverse(start[i], 1);
		permutations.push_back(v);
	}
}

int CompareMessages()
{
	int validCount = 0;
	for (int i = 0; i < messages.size(); i++)
	{
		int tmpCount = validCount;
		for (int j = 0; j < permutations[0].size(); j++)
		{
			std::string s = messages[i].substr(0, permutations[0][j].size());
			if (s.compare(permutations[0][j]) == 0)
			{
				//std::cout << "Part Valid: " << permutations[0][j] << "\n";
				for (int k= 0; k < permutations[1].size(); k++)
				{
					std::string ss = s + permutations[1][k];
					if (ss.compare(messages[i]) == 0)
					{
						std::cout << "All Valid messages[" << i << "]: \n" << ss << "\n vs \n" << messages[i] << "\n\n";
						validCount++;
					}
				}
			}
		}
	}
	return validCount;
}

int CompareRecursive()
{
	int validCount = 0;
	auto v1 = Traverse(42, 1);
	auto v2 = Traverse(31, 1);
	int substringsize = v1[0].size();
	for (int i = 0; i < messages.size(); i++)
	{
		std::string msg = messages[i];
		bool checkv1 = true;
		bool checkv2 = true;
		int matchv1 = 0;
		int matchv2 = 0;
		bool fullmatch = true;
		for (int j = 0; j < msg.size(); j+= substringsize)
		{
			std::string substring = msg.substr(j, substringsize);
			auto f1 = std::find(v1.begin(), v1.end(), substring);
			auto f2 = std::find(v2.begin(), v2.end(), substring);
			if (checkv1 && f1 != v1.end())
			{
				matchv1++;
			}
			else if (checkv2 && f2 != v2.end())
			{
				matchv2++;
				checkv1 = false;
			}
			else
			{
				checkv2 = false;
			}
		}
		if (!checkv1 && checkv2 && matchv2 < matchv1)
		{
			validCount++;
		}
	}
	return validCount;
}

void Dec19::Puzzle()
{
	enum class INPUT
	{
		RULES,
		MESSAGES
	};
	
	std::ifstream file("Dec19_PuzzleInput.txt");
	long double sum = 0;
	INPUT input = INPUT::RULES;
	if (file.is_open())
	{
		std::string line = "";
		while (std::getline(file, line))
		{
			if (line.empty())
			{
				input = INPUT::MESSAGES;
				continue;
			}

			if (input == INPUT::RULES)
			{
				int index = std::stoi(line.substr(0, line.find(':')));
				line.erase(0, line.find(' ')+1);

				std::stringstream ss(line);
				std::string s;
				while (ss >> s)
				{
					if(s.compare("\"a\"") == 0)
						rules[index].push_back(-1);
					else if(s.compare("\"b\"") == 0)
						rules[index].push_back(-2);
					else if (s.compare("|") == 0)
						rules[index].push_back(-3);
					else
					{
						int value = std::stoi(s);
						rules[index].push_back(value);
					}
				}
			}
			else if (input == INPUT::MESSAGES)
			{
				messages.push_back(line);
			}
		}
	}
	TraverseRules();
	int part1 = CompareMessages();
	
	int part2 = CompareRecursive();

	std::cout << "Part1: " << part1 << "\n";
	std::cout << "Part2: " << part2 << "\n";
	return;
}