#include "Advent_of_code.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <exception>
#include <iostream>
#include <unordered_map>
#include <thread>

const int tilewidth = 10;
const int tileheight = 10;

struct Tile
{
	enum class SIDES
	{
		LEFT, LEFT_FLIP,
		RIGHT, RIGHT_FLIP,
		UP, UP_FLIP,
		DOWN, DOWN_FLIP,
		SIDE_COUNT
	};

	int id;
	char cells[tilewidth * tileheight];
	std::unordered_map<SIDES, std::string> sides;

	void GenerateSides()
	{
		for (int i = 0; i < tilewidth; i++)
		{
			sides[SIDES::UP] += cells[i]; 
			sides[SIDES::UP_FLIP] += cells[(tilewidth-1)-i];
			sides[SIDES::DOWN] += cells[((tilewidth-1) * tileheight)+i];
			sides[SIDES::DOWN_FLIP] += cells[(tilewidth * tileheight) - (i+1)];
			sides[SIDES::LEFT] += cells[tilewidth * i];
			sides[SIDES::LEFT_FLIP] += cells[(tilewidth - 1) * tileheight - tilewidth*i];
			sides[SIDES::RIGHT] += cells[ tilewidth * (i+1) - 1];
			sides[SIDES::RIGHT_FLIP] += cells[ (tilewidth * tileheight)-1 - tilewidth*i];
		}
		return;
	}

	void RotateLeft()
	{
		char rotation[tilewidth * tileheight];
		for (int y = 0; y < tileheight; y++)
		{
			for (int x = 0; x < tilewidth; x++)
			{
				int toIndex = x + (y * tilewidth);
				int fromIndex = (tilewidth-y-1) + (x * tilewidth);
				rotation[toIndex] = cells[fromIndex];
			}
		}
		for (int i = 0; i < tilewidth * tileheight; i++)
		{
			cells[i] = rotation[i];
		}
	} 

	void Flip()
	{
		for (int y = 0; y < tileheight; y++)
		{
			for (int lx = 0, rx = tilewidth-1; lx < rx; lx++, rx--)
			{
				int lhs = (y * tilewidth) + lx;
				int rhs = (y * tilewidth) + rx;
				bool tmp = cells[lhs];
				cells[lhs] = cells[rhs];
				cells[rhs] = tmp;
			}
		}
	}
};

std::vector<Tile> tiles;


void PrintTile(Tile& tile)
{
	std::cout << "Tile " << tile.id << ": \n";
	for (int y = 0; y < tileheight; y++)
	{
		for (int x = 0; x < tilewidth; x++)
		{
			int index = x + y * tilewidth;
			std::cout << tile.cells[index];
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}
void PrintTiles()
{
	for (auto &tile : tiles)
	{
		PrintTile(tile);
	}
}

void CompareSides(Tile& lhs, Tile& rhs) // Top LHS vs Bot RHS
{
	for (auto lside : lhs.sides)
	{
		for (auto rside : rhs.sides)
		{

			if (lside.second.compare(rside.second) == 0)
			{
				std::cout << "Match Tile: " << lhs.id << " Side: " << lside.second;
				std::cout << " with Tile: " << rhs.id << " Side: " << rside.second << "\n";
			}
		}
	}
}

void CompareTiles(Tile &lhs, Tile& rhs) // Top LHS vs Bot RHS
{
	for (int i = 0; i < 8; i++)
	{
		bool match = true;
		if (i == 4)
			lhs.Flip();
		for (int j = 0; j < tilewidth; j++)
		{
			int lhsIndex = j;
			int rhsIndex = j + (tileheight - 1) * tilewidth;
			if (lhs.cells[lhsIndex] != rhs.cells[rhsIndex])
			{
				match = false;
				std::cout << "Mismatch \n";
				break;
			}
		}
		if(match)
			std::cout << "Match \n";
		lhs.RotateLeft();
		
	}

	for (int i = 0; i < 8; i++)
	{
		if (i == 4)
			rhs.Flip();
		bool match = true;
		for (int j = 0; j < tilewidth; j++)
		{
			int lhsIndex = j;
			int rhsIndex = j + (tileheight - 1) * tilewidth;
			if (rhs.cells[lhsIndex] != lhs.cells[rhsIndex])
			{
				match = false;
				std::cout << "Mismatch \n";
				break;
			}
		}
		if (match)
			std::cout << "Match \n";
		rhs.RotateLeft();
		
	}
}

void Dec20::Puzzle()
{
	enum class INPUT
	{
		ID,
		TILES
	};

	std::ifstream file("Dec20_PuzzleInput.txt");
	long double sum = 0;
	INPUT input = INPUT::ID;
	if (file.is_open())
	{
		std::string line = "";
		Tile tile;
		int cellposition = 0;
		while (std::getline(file, line))
		{
			if (line.empty())
			{
				input = INPUT::ID;
				tiles.push_back(tile);
				tile = Tile();
				cellposition = 0;
				continue;
			}

			if (input == INPUT::ID)
			{
				auto from = line.find(' ');
				auto to = line.find(':');
				std::string sid = line.substr(from+1, to-from-1);
				tile.id = std::stoi(sid);
				input = INPUT::TILES;
			}
			else if (input == INPUT::TILES)
			{ 
				for (auto &c : line)
				{
					tile.cells[cellposition++] = c;
				}
			}
		}
	}
	
	for (auto &t : tiles)
	{
		t.GenerateSides();
	}

	for (int i = 0; i < tiles.size()-1; i++)
	{
		for (int j = i+1; j < tiles.size(); j++)
		{
			CompareSides(tiles[i], tiles[j]);
		}
	}
	
//	tiles[0].Flip();
	//tiles[0].RotateLeft();
	PrintTile(tiles[0]);
	//tiles[1].Flip();
	//tiles[1].RotateLeft();
	PrintTile(tiles[1]);
	//CompareTiles(tiles[0], tiles[1]);


	while(true)
	{
		system("CLS");
		PrintTile(tiles[0]);
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		tiles[0].RotateLeft();	
	}

	
	
	return;
}