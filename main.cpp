#include "Advent_of_code.h"
#include <chrono>
#include <iostream>

int main(int argc, char** argv)
{
	auto start = std::chrono::high_resolution_clock::now();
	int iterations = 10000;
	for (int i = 0; i < iterations; i++)
		Dec10::Puzzle();
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Execution Duration: " << duration.count()/static_cast<double>(10000) << std::endl;
	return 1;
}

