#include "part1.hh"
#include "fileutility.hh"
#include "problem.hh"
#include "inputparsing.hh"
#include "digitcharutility.hh"

#include <vector>
#include <stdexcept>
#include <algorithm>
#include <iostream>

std::optional<UnsignedInt> Part1::getPart1AnswersSum(std::ifstream& file) {
	std::optional<FirstPassData> parseFirstPassAttemptResult = InputParsing::tryParseFirstPass(file);
	if (not parseFirstPassAttemptResult.has_value()) {
		return std::nullopt;
	}
	FirstPassData& parseFirstPassResult = parseFirstPassAttemptResult.value();

	std::vector<Problem>& problems = parseFirstPassResult.problems_;
	std::size_t greatestProblemWidthInFile = parseFirstPassResult.greatestProblemWidthInFile_;

	std::size_t numOperandLines = parseFirstPassResult.numOperandLines_;

	#if 0
	std::cout << "Operator line parsed successfully" << std::endl;
	for (const Problem& problem : problems) {
		std::cout << "width in file: " << problem.widthInFile() << std::endl;
	}
	#endif

	FileUtility::resetInputFileState(file);

	UnsignedInt answersSum = 0;
	std::string operandStr;
	operandStr.reserve(greatestProblemWidthInFile);
	for (std::size_t operandLine = 0; operandLine < numOperandLines; ++operandLine) {
		for (std::size_t iProblem = 0; iProblem < problems.size(); ++iProblem) {
			Problem& problem = problems.at(iProblem);
			for (std::size_t iChar = 0; iChar < problem.widthInFile(); ++iChar) {
				char c;
				if (not file.get(c)) {
					std::cout << "Failed to read character.";
					return std::nullopt;
				}
				bool isOperandCharacter = c == ' ' or DigitCharUtility::isDigitChar(c);
				if (not isOperandCharacter) {
					std::cout << "c is not an operand character. c: " << c << std::endl;
					return std::nullopt;
				}

				operandStr.push_back(c);
			}

			char charAfterOperand;
			if (not file.get(charAfterOperand)) {
				return std::nullopt;
			}
			bool lineEndsTooSoon = charAfterOperand == '\n' and iProblem < problems.size() - 1;
			bool lineEndsTooLate = charAfterOperand == ' ' and iProblem == problems.size() - 1;
			bool invalidDelimiter = charAfterOperand != ' ' and charAfterOperand != '\n';
			if (lineEndsTooSoon or lineEndsTooLate or invalidDelimiter) {
				std::cout << "charAfterOperand: " << charAfterOperand << "; lineEndsTooSoon: " << lineEndsTooSoon << "; lineEndsTooLate: " << lineEndsTooLate << "; invalidDelimiter: " << invalidDelimiter << std::endl;
				std::cout << "operandLine: " << operandLine << "; iProblem: " << iProblem << "; problems.size(): " << problems.size() << "; problem.widthInFile(): " << problem.widthInFile() << std::endl;
				return std::nullopt;
			}

			UnsignedInt operand = std::stoi(operandStr);
			problem.updateAnswer(operand);

			if (operandLine == numOperandLines - 1) {
				//std::cout << "answer " << iProblem << ": " << problem.answer() << std::endl;
				answersSum += problem.answer();
			}
			operandStr.clear();
		}
	}

	return answersSum;
}
