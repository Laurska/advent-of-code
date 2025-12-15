#include "typealiases.hh"
#include "math.hh"
#include "inputparser.hh"
#include "puzzlepart1usingsumformulas.hh"
#include "puzzlepart1easyapproach.hh"
#include "puzzlepart2.hh"

#include <iostream>
#include <fstream>
#include <stdexcept>

const std::string fileName = "input.txt";

int main() {
	UnsignedInt part1TotalSumWithSumFormulasApproach = 0;
	UnsignedInt part1TotalSumWithEasyApproach = 0;

	UnsignedInt part2TotalSum = 0;

	std::ifstream file(fileName);
	InputParser parser(file);

	for (;;) {
		ParseAttemptResult intervalReadAttemptResult = parser.tryReadInterval();
		if (std::holds_alternative<ParseError>(intervalReadAttemptResult)) {
			const std::string& errorMessage = std::get<ParseError>(intervalReadAttemptResult).message_;
			throw std::invalid_argument("Invalid file contents: " + errorMessage);
		}
		if (std::holds_alternative<EndOfFile>(intervalReadAttemptResult)) {
			//std::cout << "ParseAttemptResult is EndOfFile." << std::endl;
			break;
		}

		const Interval& interval = std::get<Interval>(intervalReadAttemptResult);
		UnsignedInt a = interval.inclusiveStart_;
		UnsignedInt b = interval.inclusiveEnd_;

		UnsignedInt part1IntervalSumUsingSumFormulas = PuzzlePart1UsingSumFormulas::calculateSumForInterval(a, b);
		UnsignedInt part1IntervalSumCalculatedInEasierWay = PuzzlePart1EasyApproach::calculateSumForInterval(a, b);
		if (part1IntervalSumUsingSumFormulas != part1IntervalSumCalculatedInEasierWay) {
			std::cout
				<< "mismatch between interval sum calculation approaches on interval: " << a << "-" << b
				<< "; sum calculation results: sum formulas: " << part1IntervalSumUsingSumFormulas
				<< "; easy: " << part1IntervalSumCalculatedInEasierWay
				<< std::endl;
		}
		part1TotalSumWithSumFormulasApproach += part1IntervalSumUsingSumFormulas;
		part1TotalSumWithEasyApproach += part1IntervalSumCalculatedInEasierWay;

		UnsignedInt part2IntervalSum = PuzzlePart2::calculateSumForInterval(a, b);
		part2TotalSum += part2IntervalSum;
	}
	file.close();

	if (part1TotalSumWithSumFormulasApproach != part1TotalSumWithEasyApproach) {
		std::cout
			<< "Total sums of the Part 1 interval sums calculated with different approaches don't match."
			<< "; part1TotalSumWithSumFormulasApproach: " << part1TotalSumWithSumFormulasApproach
			<< "; part1TotalSumWithEasyApproach: " << part1TotalSumWithEasyApproach
			<< std::endl;
	} else {
		std::cout << "Part 1: " << part1TotalSumWithSumFormulasApproach << std::endl;
		std::cout << "Part 2: " << part2TotalSum << std::endl;
	}
	return EXIT_SUCCESS;
}
