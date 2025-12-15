#include "part2.hh"
#include "vector2.hh"
#include "gridutility.hh"

#include <vector>
#include <cstddef>
#include <algorithm>
#include <optional>
#include <queue>
#include <iostream>

namespace {

void visualizeNeighborRollCounts(const PaperRollGrid& grid, const std::vector<std::optional<unsigned int>>& neighborRollCounts) {
	std::cout << std::endl;
	for (std::size_t y = 0; y < grid.height(); ++y) {
		for (std::size_t x = 0; x < grid.width(); ++x) {
			const std::optional<unsigned int>& neighborRollCount = neighborRollCounts.at(x + grid.width() * y);
			char charToPrint;
			if (grid.hasPaperRollAt(x, y) != neighborRollCount.has_value()) {
				throw std::logic_error("Mismatch between container contents.");
			}
			if (grid.hasPaperRollAt(x, y)) {
				charToPrint = '0' + neighborRollCount.value();
			} else {
				charToPrint = '.';
			}
			std::cout << charToPrint;
		}
		std::cout << std::endl;
	}
	std::cout << " " << std::endl;
}

}

unsigned int Part2::findHowManyRollsCanBeRemoved(PaperRollGrid& grid) {
	unsigned int numEventuallyRemovableRolls = 0;

	std::queue<Vector2> rollsToRemove;
	std::vector<std::optional<unsigned int>> neighborRollCounts;
	neighborRollCounts.resize(grid.width() * grid.height());

	for (std::size_t x = 0; x < grid.width(); ++x) {
		for (std::size_t y = 0; y < grid.height(); ++y) {
			if (not grid.hasPaperRollAt(x, y)) {
				continue;
			}

			unsigned int neighborRollCount = GridUtility::howManyNeighborsContainAPaperRoll(grid, x, y);
			neighborRollCounts.at(x + grid.width() * y) = neighborRollCount;
			if (neighborRollCount >= 4) {
				continue;
			}

			rollsToRemove.push(Vector2(x, y));
		}
	}

	//visualizeNeighborRollCounts(grid, neighborRollCounts);

	while (not rollsToRemove.empty()) {
		Vector2 rollToRemove = rollsToRemove.front();
		rollsToRemove.pop();
		//std::cout << "rollToRemove: (" << rollToRemove.x() << ", " << rollToRemove.y() << ")" << std::endl;
		//std::cout << "rollsToRemove.size(): " << rollsToRemove.size() << std::endl;

		for (int neighborX = std::max(rollToRemove.x() - 1, 0); neighborX <= std::min(rollToRemove.x() + 1, static_cast<int>(grid.width()) - 1); ++neighborX) {
			for (int neighborY = std::max(rollToRemove.y() - 1, 0); neighborY <= std::min(rollToRemove.y() + 1, static_cast<int>(grid.height()) - 1); ++neighborY) {
				if (neighborX == rollToRemove.x() and neighborY == rollToRemove.y()) {
					continue;
				}

				if (not grid.hasPaperRollAt(neighborX, neighborY)) {
					continue;
				}

				std::optional<unsigned int>& neigborRollCountOfNeighbor = neighborRollCounts.at(neighborX + grid.width() * neighborY);
				neigborRollCountOfNeighbor = neigborRollCountOfNeighbor.value() - 1;
				if (neigborRollCountOfNeighbor.value() == 3) {
					rollsToRemove.push(Vector2(neighborX, neighborY));
				}
			}
		}

		grid.setCellState(rollToRemove.x(), rollToRemove.y(), false);
		neighborRollCounts.at(rollToRemove.x() + grid.width() * rollToRemove.y()) = std::nullopt;
		numEventuallyRemovableRolls += 1;

		//visualizeNeighborRollCounts(grid, neighborRollCounts);
	}

	return numEventuallyRemovableRolls;
}
