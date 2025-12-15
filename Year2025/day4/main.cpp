#include "paperrollgrid.hh"
#include "inputparsing.hh"
#include "part1.hh"
#include "part2.hh"

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <optional>

const std::string fileName = "input.txt";
//const std::string fileName = "exampleInput.txt";

int main() {
	std::ifstream file(fileName);
	if (not file) {
		throw std::runtime_error("Unable to open file.");
	}

	std::optional<PaperRollGrid> parseAttemptResult = InputParsing::parseFile(file);
	if (not parseAttemptResult.has_value()) {
		throw std::runtime_error("Invalid file contents.");
	}
	PaperRollGrid& grid = parseAttemptResult.value();

	file.close();

	#if 0
	unsigned int numPaperRolls = 0;
	for (std::size_t x = 0; x < grid.width(); ++x) {
		for (std::size_t y = 0; y < grid.width(); ++y) {
			numPaperRolls += static_cast<unsigned int>(grid.hasPaperRollAt(x, y));
		}
	}
	std::cout << "numPaperRolls: " << numPaperRolls << std::endl;
	std::cout << "Grid size: (" << grid.width() << ", " << grid.height() << ")" << std::endl;
	#endif

	unsigned int part1Result = Part1::findHowManyRollsAreReachable(grid);
	unsigned int part2Result = Part2::findHowManyRollsCanBeRemoved(grid);

	std::cout << "Part 1: " << part1Result << std::endl;
	std::cout << "Part 2: " << part2Result << std::endl;

	return EXIT_SUCCESS;
}
