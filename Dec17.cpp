#include "Advent_of_code.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>


template <typename T>
struct Vector3
{
	T x, y, z;
};

struct Cube
{
	static const std::vector<Vector3<int>> adjacentCubes;
	Vector3<int> position;
	bool active;
	int activeAdjacentCubes;
	void Print()
	{
		printf("Cube (%d,%d,%d) \n", position.x, position.y, position.z);

	}
};

														// z +1
const std::vector<Vector3<int>> Cube::adjacentCubes = { {-1, 1, 1}, {0, 1, 1}, {1, 1, 1},   
														{-1, 0, 1}, {0, 0, 1}, {1, 0, 1},   
														{-1,-1, 1}, {0,-1, 1}, {1,-1, 1},   
														// z 0
														{-1, 1, 0}, {0, 1, 0}, {1, 1, 0},  
														{-1, 0, 0},            {1, 0, 0},  
														{-1,-1, 0}, {0,-1, 0}, {1,-1, 0},  
														// z -1
														{-1, 1, -1}, {0, 1,-1}, {1, 1,-1},
														{-1, 0, -1}, {0, 0,-1}, {1, 0,-1},
														{-1,-1, -1}, {0,-1,-1}, {1,-1,-1}};
struct PocketDimension
{
	Vector3<int> dimensions;
	int count;
	Cube* cubes;
	PocketDimension(int x, int y, int z)
	{
		dimensions = { x, y, z };
		count = x * y * z;
		cubes = new Cube[count];
		for (int i = 0; i < count; i++)
		{
			cubes[i].position.x = i % dimensions.x;
			cubes[i].position.y = (i / dimensions.x) % dimensions.y;
			cubes[i].position.z = (i / (dimensions.x * dimensions.y));
			cubes[i].active = false;
			cubes[i].activeAdjacentCubes = 0;
			//printf("Cube[%d] (%d,%d,%d) \n", i, cubes[i].position.x, cubes[i].position.y, cubes[i].position.z);
		}
	}

	Cube* GetCube(int x, int y, int z)
	{
		if (x < 0 || x > dimensions.x-1 ||
			y < 0 || y > dimensions.y-1 ||
			z < 0 || z > dimensions.z-1)
			return nullptr;

		int index = x + (y * dimensions.x) + (z * dimensions.x * dimensions.y);
		

		return &cubes[x + (y * dimensions.x) + (z * dimensions.x * dimensions.y)];
	}

	void SetActive(std::vector<char>& chars, char active)
	{
		int localDimension = sqrt(chars.size());

		Cube* middle = GetCube(dimensions.x / 2, dimensions.y / 2, dimensions.z / 2);
		for (int i = 0; i < chars.size(); i++)
		{
			int x = middle->position.x + -(localDimension / 2) + (i % localDimension);
			int y = middle->position.y + -(localDimension / 2) + (i / localDimension);
			int z = middle->position.z;
			Cube* cube = GetCube(x, y, z);

			if (chars[i] == active)
				cube->active = true;
				
		}
	}

	void CountAdjacent()
	{
		for (int i = 0; i < count; i++)
		{
			cubes[i].activeAdjacentCubes = 0;
			for (int j = 0; j < Cube::adjacentCubes.size(); j++)
			{
				Cube* cube = GetCube(cubes[i].position.x + Cube::adjacentCubes[j].x,
									 cubes[i].position.y + Cube::adjacentCubes[j].y,
									 cubes[i].position.z + Cube::adjacentCubes[j].z);
				if(cube)
					if (cube->active)
						cubes[i].activeAdjacentCubes++;
			}
		}
	}

	void Evolve()
	{
		for (int i = 0; i < count; i++)
		{
			if (cubes[i].active)
			{
				if (cubes[i].activeAdjacentCubes == 2 || cubes[i].activeAdjacentCubes == 3)
					cubes[i].active = true;
				else
					cubes[i].active = false;
			}
			else 
			{
				if (cubes[i].activeAdjacentCubes == 3)
					cubes[i].active = true;
				else
					cubes[i].active = false;
			}
		}
	}

	void PrintActive()
	{
		for (int i = 0; i < count; i++)
		{
			if(cubes[i].active)
				printf("Active Cube[%d] (%d,%d,%d) \n", i, cubes[i].position.x, cubes[i].position.y, cubes[i].position.z);
		}
	}
	void PrintZ()
	{
		printf("\nPrint Z \n");
		for (int i = 0; i < count; i++)
		{
			if (i % (dimensions.x * dimensions.y) == 0)
				printf("\n\nZ = %d", i / (dimensions.x * dimensions.y) - dimensions.x / 2);

			if (i % dimensions.x == 0)
				printf("\n");

			printf("[%d]", cubes[i].active);


			
		}
	}

	void PrintCount()
	{
		printf("\nPrint Count \n");
		for (int i = 0; i < count; i++)
		{
			if (i % (dimensions.x * dimensions.y) == 0)
				printf("\n\nZ = %d", i / (dimensions.x * dimensions.y) - dimensions.x / 2);

			if (i % dimensions.x == 0)
				printf("\n");

			printf("[%d]", cubes[i].activeAdjacentCubes);



		}
	}

	unsigned int CountActive()
	{
		unsigned int ret = 0;
		for (int i = 0; i < count; i++)
		{
			if (cubes[i].active)
				ret++;
		}
		return ret;
	}

	enum class PrintType
	{
		Coordinate,
		Active,
		ActiveAdjacent
	};

	void PrintGrid(PrintType type)
	{
		printf("\n Print Grid \n");
		for (int i = 0; i < count; i++)
		{
			if (i % dimensions.x == 0)
				printf("\n");

			if (i % (dimensions.x * dimensions.x) == 0)
				printf("\n");

			switch (type)
			{
			case PrintType::Coordinate: printf("[%d,%d,%d] ", cubes[i].position.x, cubes[i].position.y, cubes[i].position.z); break;
			case PrintType::Active: printf("[%d] ", cubes[i].active); break;
			case PrintType::ActiveAdjacent: printf("[%d] ", cubes[i].activeAdjacentCubes); break;
			}
			
			
		}
	}
};
void Dec17::Puzzle()
{
	std::ifstream file("Dec17_PuzzleInput.txt");

	PocketDimension* dimension;
	int cycles = 6;

	if (file.is_open())
	{
		std::string line = "";
		std::vector<char> chars;
		while (std::getline(file, line))
		{
			for(int i = 0; i<line.size(); i++)
				chars.push_back(line[i]);
		}
		int size = sqrt(chars.size()) + cycles*2;
		dimension = new PocketDimension(size, size, size);
		dimension->SetActive(chars, '#');

		//dimension->PrintGrid(PocketDimension::PrintType::Coordinate);


		
		for (int i = 0; i < 6; i++)
		{
			dimension->CountAdjacent();
			//dimension->PrintGrid(PocketDimension::PrintType::Active);
			//dimension->PrintGrid(PocketDimension::PrintType::ActiveAdjacent);
			dimension->Evolve();
			printf("Count: %d \n", dimension->CountActive());
		}
		
	}
	return;
}