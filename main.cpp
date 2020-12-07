#include "Advent_of_code.h"
#include <chrono>
#include <iostream>

int main(int argc, char** argv)
{
	auto start = std::chrono::high_resolution_clock::now();
	Dec07::Puzzle1();
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Execution Duration: " << duration.count()*0.000001 << std::endl;
	return 1;
}

