#include "parsedinput.hh"
#include "inputparsing.hh"
#include "part1.hh"
#include "part2.hh"

#include <iostream>
#include <string>
#include <optional>
#include <fstream>
#include <stdexcept>

const std::string& fileName = "input.txt";
//const std::string& fileName = "exampleInput.txt";

int main() {
	std::ifstream file(fileName);
	if (not file) {
		throw std::runtime_error("Could not open file");
	}

	std::optional<ParsedInput> parseAttemptResult = InputParsing::tryParseFile(file);
	if (not parseAttemptResult.has_value()) {
		throw std::runtime_error("Invalid file contents.");
	}
	const ParsedInput& parseResult = parseAttemptResult.value();
	file.close();
	//std::cout << "Input file was parsed successfully." << std::endl;

	UnsignedInt part1Result = Part1::findHowManyAvailableIngredientIdsAreFresh(parseResult);
	UnsignedInt part2Result = Part2::calculateHowManyIngredientIdsAreInFreshIntervals(parseResult);

	std::cout << "Part 1: " << part1Result << std::endl;
	std::cout << "Part 2: " << part2Result << std::endl;

	return EXIT_SUCCESS;
}
