#include "SpatialHash.hpp"

#include <iostream>

int main(int argc, char** argv)
{
	SpatialHash sh(111.0f);

	std::cout << sh.ComputeHash(1.9999, 2.0001) << std::endl;

	auto strs = sh.GetHashesForCellsInRange(2.0f, 2.0f, 2500.0f);

	std::cout << "end." << std::endl;
	std::cin.get();
}
