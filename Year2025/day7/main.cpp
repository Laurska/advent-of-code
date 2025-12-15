#include "part1.hh"
#include "part2.hh"

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <optional>

const std::string fileName = "input.txt";

int main() {
	std::ifstream file(fileName);
	if (not file) {
		throw std::runtime_error("Could not open file.");
	}

	std::optional<UnsignedInt> part1AttemptResult = Part1::calculateNumSplits(file);
	if (not part1AttemptResult.has_value()) {
		throw std::invalid_argument("Invalid file contents.");
	}
	UnsignedInt part1Result = part1AttemptResult.value();

	std::optional<UnsignedInt> part2AttemptResult = Part2::calculateNumTimelines(file);
	if (not part2AttemptResult.has_value()) {
		throw std::invalid_argument("Invalid file contents.");
	}
	UnsignedInt part2Result = part2AttemptResult.value();

	file.close();

	std::cout << "Part 1: " << part1Result << std::endl;
	std::cout << "Part 2: " << part2Result << std::endl;

	return EXIT_SUCCESS;
}
