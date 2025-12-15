#include "part1.hh"
#include "part2.hh"

#include <iostream>
#include <string>
#include <fstream>
#include <optional>
#include <stdexcept>

const std::string fileName = "input.txt";

int main() {
	std::ifstream file(fileName);
	if (not file) {
		throw std::invalid_argument("Could not read the file.");
	}

	std::optional<UnsignedInt> part1AttemptResult = Part1::getMaxJoltagesSum(file);
	if (not part1AttemptResult.has_value()) {
		throw std::invalid_argument("invalid file contents.");
	}
	UnsignedInt part1Result = part1AttemptResult.value();

	file.clear();
	file.seekg(0, std::ios::beg);

	std::optional<UnsignedInt> part2AttemptResult = Part2::getMaxJoltagesSum(file);
	if (not part2AttemptResult.has_value()) {
		throw std::invalid_argument("Invalid file contents");
	}
	UnsignedInt part2Result = part2AttemptResult.value();

	file.close();

	std::cout << "Part 1: " << part1Result << std::endl;
	std::cout << "Part 2: " << part2Result << std::endl;

	return EXIT_SUCCESS;
}
