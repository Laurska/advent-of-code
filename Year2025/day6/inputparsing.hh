#ifndef INPUTPARSING_HH
#define INPUTPARSING_HH

#include "problem.hh"
#include "neededoperations.hh"

#include <vector>
#include <fstream>
#include <optional>
#include <cstddef>

using OperandStorageType = std::uint16_t;

struct FirstPassData {
	FirstPassData(std::vector<Problem> problems, std::size_t greatestProblemWidthInFile, std::size_t sumOfProblemWidths, std::size_t numOperandLines);

	std::vector<Problem> problems_;
	std::size_t greatestProblemWidthInFile_ = 0;
	std::size_t sumOfProblemWidths_ = 0;

	std::size_t numOperandLines_ = 0;
};

namespace InputParsing {

std::optional<FirstPassData> tryParseFirstPass(std::ifstream& file);

std::optional<std::vector<OperandStorageType>> tryParseVerticalOperands(std::ifstream& file, FirstPassData& firstPassData);

}

#endif // INPUTPARSING_HH
