#include "part1.hh"
#include "gridutility.hh"

#include <iostream>

unsigned int Part1::findHowManyRollsAreReachable(const PaperRollGrid& grid) {
	unsigned int numReachableRolls = 0;
	for (std::size_t x = 0; x < grid.width(); ++x) {
		for (std::size_t y = 0; y < grid.width(); ++y) {
			unsigned int neighborRollCount = GridUtility::howManyNeighborsContainAPaperRoll(grid, x, y);
			if (not grid.hasPaperRollAt(x, y)) {
				continue;
			}
			if (neighborRollCount >= 4) {
				continue;
			}

			numReachableRolls += 1;
			//std::cout << "(" << x << ", " << y << ") " << std::endl;
		}
	}
	return numReachableRolls;
}
