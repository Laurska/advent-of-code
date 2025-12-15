#include "inputparsing.hh"
#include "fileutility.hh"
#include "digitcharutility.hh"

#include <cstdint>
#include <stdexcept>
#include <iostream>

FirstPassData::FirstPassData(std::vector<Problem> problems, std::size_t greatestProblemWidthInFile, std::size_t sumOfProblemWidths, std::size_t numOperandLines):
	problems_(problems), greatestProblemWidthInFile_(greatestProblemWidthInFile), sumOfProblemWidths_(sumOfProblemWidths), numOperandLines_(numOperandLines)
{}

namespace {

bool isOperatorSymbol(char c) {
	return
		c == NeededOperations::addition.symbol()
		or c == NeededOperations::multiplication.symbol();
}

}

std::optional<FirstPassData> InputParsing::tryParseFirstPass(std::ifstream& file) {
	FileUtility::resetInputFileState(file);

	std::vector<Problem> problems;
	std::size_t greatestProblemWidthInFile = 0;
	std::size_t sumOfProblemWidths = 0;

	std::size_t numOperandLines = 0;

	//bool atStartOfLine = true;
	//bool inOperatorLine = false;
	bool parsingAProblem = false;

	char currentProblemSymbol;
	std::size_t currentProblemWidthInFile;

	bool operatorLineHasBeenParsed = false;

	for (;;) {
		char c;
		if (not file.get(c)) {
			if (not operatorLineHasBeenParsed) {
				std::cout << "File ended before operator line was parsed." << std::endl;
				return std::nullopt;
			}
			break;
		}
		if (operatorLineHasBeenParsed) {
			// There should be nothing after the operator line.
			// The last character in the file is expected to be the '\n' of
			// the operator line.
			std::cout << "File did not end right after operator line." << std::endl;
			return std::nullopt;
		}

		if (not parsingAProblem) {
			if (c == '\n') {
				numOperandLines += 1;
			} else if (isOperatorSymbol(c)) {
				parsingAProblem = true;
				currentProblemSymbol = c;
				currentProblemWidthInFile = 1;
			}
			continue;
		}

		bool endOfProblemDetected = c == '\n' or isOperatorSymbol(c);
		if (not endOfProblemDetected and c != ' ') {
			std::cout << "Unexpected character. c: " << c << std::endl;
			return std::nullopt;
		}

		if (not endOfProblemDetected) {
			currentProblemWidthInFile += 1;
			continue;
		}

		if (isOperatorSymbol(c)) {
			// Subtract the extra 1 that was added by the space between
			// problems.
			currentProblemWidthInFile -= 1;
		}

		// Add a new problem.
		const Operation* operation;
		if (currentProblemSymbol == NeededOperations::addition.symbol()) {
			operation = &NeededOperations::addition;
		} else if (currentProblemSymbol == NeededOperations::multiplication.symbol()) {
			operation = &NeededOperations::multiplication;
		} else {
			throw std::logic_error("Unhandled operator symbol.");
		}
		problems.push_back(Problem(*operation, currentProblemWidthInFile));

		// Update bookkeeping variables
		greatestProblemWidthInFile = std::max(currentProblemWidthInFile, greatestProblemWidthInFile);
		sumOfProblemWidths += currentProblemWidthInFile;
		if (isOperatorSymbol(c)) {
			currentProblemSymbol = c;
			currentProblemWidthInFile = 1;
		} else if (c == '\n') {
			operatorLineHasBeenParsed = true;
		} else {
			throw std::logic_error("Contradiction in logic.");
		}
	}

	return FirstPassData(std::move(problems), greatestProblemWidthInFile, sumOfProblemWidths, numOperandLines);
}

std::optional<std::vector<OperandStorageType>> InputParsing::tryParseVerticalOperands(std::ifstream& file, FirstPassData& firstPassData) {
	FileUtility::resetInputFileState(file);

	std::vector<OperandStorageType> operands;
	operands.resize(firstPassData.sumOfProblemWidths_);

	std::size_t problemIndex = 0;
	std::size_t horizontalIndex = 0;
	std::size_t firstHorizontalIndexForCurrentProblem = 0;

	for (;;) {
		char c;
		if (not file.get(c)) {
			std::cout << "Could not read character." << std::endl;
			return std::nullopt;
		}

		bool lineEnded = c == '\n';
		bool allProblemsHandled = problemIndex == firstPassData.problems_.size();
		if (lineEnded != allProblemsHandled) {
			std::cout << "Contradicting lineEnded and allProblemsHandled. lineEnded: " << lineEnded << "; allProblemsHandled: " << allProblemsHandled << std::endl;
			return std::nullopt;
		}

		if (allProblemsHandled) {
			problemIndex = 0;
			horizontalIndex = 0;
			firstHorizontalIndexForCurrentProblem = 0;
			continue;
		}

		if (horizontalIndex == 0 and isOperatorSymbol(c)) {
			break;
		}

		bool isDigit = DigitCharUtility::isDigitChar(c);
		bool isOperandCharacter = isDigit or c == ' ';
		if (not isOperandCharacter) {
			std::cout << "Operand character (digit or space) expected, got " << c << std::endl;
			return std::nullopt;
		}

		if (isDigit) {
			OperandStorageType& operand = operands.at(horizontalIndex);
			operand *= 10;
			operand += static_cast<OperandStorageType>(DigitCharUtility::convertDigitCharToNumber(c));
		}

		Problem& problem = firstPassData.problems_.at(problemIndex);
		std::size_t lastHorizontalIndexForCurrentProblem = firstHorizontalIndexForCurrentProblem + problem.widthInFile() - 1;
		if (horizontalIndex == lastHorizontalIndexForCurrentProblem) {
			if (problemIndex < firstPassData.problems_.size() - 1) {
				char spaceBetweenProblems;
				if (not file.get(spaceBetweenProblems)) {
					return std::nullopt;
				}
				if (spaceBetweenProblems != ' ') {
					return std::nullopt;
				}
			}
			problemIndex += 1;
			firstHorizontalIndexForCurrentProblem = horizontalIndex + 1;
		}
		horizontalIndex += 1;
	}

	return operands;
}
