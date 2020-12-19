#include "Advent_of_code.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


template <typename T>
struct Vector4
{
	T x, y, z, w;
};

struct Cube
{
	static std::vector<Vector4<int>> adjacentCubes;
	Vector4<int> position;
	bool active;
	int activeAdjacentCubes;
	void Print()
	{
		printf("Cube (%d,%d,%d) \n", position.x, position.y, position.z);

	}
	static void GenerateAdjacentCubeCoords()
	{
		adjacentCubes.clear();
		for (int w = 1; w > -2; w--)
			for (int z = 1; z > -2; z--)
				for (int y = 1; y > -2; y--)
					for (int x = -1; x < 2; x++)
						adjacentCubes.push_back({ x,y,z,w });
		adjacentCubes.erase(adjacentCubes.begin() + adjacentCubes.size()/2);
	}
};

std::vector<Vector4<int>> Cube::adjacentCubes;
				
struct PocketDimension
{
	Vector4<int> dimensions;
	int count;
	Cube* cubes;
	PocketDimension(int x, int y, int z, int w)
	{
		dimensions = { x, y, z, w };
		count = x * y * z * w;
		cubes = new Cube[count];
		for (int i = 0; i < count; i++)
		{
			cubes[i].position.x = i % dimensions.x;
			cubes[i].position.y = (i / dimensions.x) % dimensions.y;
			cubes[i].position.z = (i / (dimensions.x * dimensions.y) % dimensions.z);
			cubes[i].position.w = (i / (dimensions.x * dimensions.y * dimensions.z));
			cubes[i].active = false;
			cubes[i].activeAdjacentCubes = 0;
		}
	}

	Cube* GetCube(int x, int y, int z, int w)
	{
		if (x < 0 || x > dimensions.x-1 ||
			y < 0 || y > dimensions.y-1 ||
			z < 0 || z > dimensions.z-1 ||
			w < 0 || w > dimensions.w - 1)
			return nullptr;

		int index = x + (y * dimensions.x) + (z * dimensions.x * dimensions.y) + (w * dimensions.x * dimensions.y * dimensions.z);
		

		return &cubes[index];
	}

	void SetActive(std::vector<char>& chars, char active)
	{
		int localDimension = sqrt(chars.size());

		Cube* middle = GetCube(dimensions.x / 2, dimensions.y / 2, dimensions.z / 2, dimensions.w / 2);
		for (int i = 0; i < chars.size(); i++)
		{
			int x = middle->position.x + -(localDimension / 2) + (i % localDimension);
			int y = middle->position.y + -(localDimension / 2) + (i / localDimension);
			int z = middle->position.z;
			int w = middle->position.w;
			Cube* cube = GetCube(x, y, z, w);

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
									 cubes[i].position.z + Cube::adjacentCubes[j].z,
									 cubes[i].position.w + Cube::adjacentCubes[j].w);
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
				printf("Z=%d W=%d \n", cubes[i].position.z, cubes[i].position.w);

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
	Cube::GenerateAdjacentCubeCoords();
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
		int size = static_cast<int>(sqrt(chars.size()) + cycles*2);
		dimension = new PocketDimension(size, size, size, size);
		dimension->SetActive(chars, '#');
		printf("Count: %d \n", dimension->CountActive());
		
		for (int i = 0; i < 6; i++)
		{
			dimension->CountAdjacent();
			dimension->Evolve();
			printf("Count: %d \n", dimension->CountActive());
		}
		
	}
	return;
}