#include "inputparsing.hh"
#include "integerinterval.hh"

#include <cstddef>

UnsignedIntReadResult::UnsignedIntReadResult(UnsignedInt result, std::size_t indexAfter):
	result_(result), indexAfter_(indexAfter)
{}

namespace {

bool isDigitChar(char c) {
	return '0' <= c and c <= '9';
}

std::optional<UnsignedIntReadResult> tryReadUnsignedInt(const std::string str, std::size_t startIndex) {
	std::size_t indexAfterNumber = startIndex;
	for (std::size_t iChar = startIndex; iChar < str.size(); ++iChar) {
		char c = str.at(iChar);
		if (not isDigitChar(c)) {
			break;
		}
		indexAfterNumber += 1;
	}
	if (indexAfterNumber == startIndex) {
		return std::nullopt;
	}

	UnsignedInt result = std::stoll(str.substr(startIndex, indexAfterNumber - startIndex));
	return UnsignedIntReadResult(result, indexAfterNumber);
}

}

std::optional<ParsedInput> InputParsing::tryParseFile(std::ifstream& file) {
	ParsedInput result;

	bool fileSection2Reached = false;
	std::string line;
	while (std::getline(file, line)) {
		if (not fileSection2Reached) {
			if (line.empty()) {
				fileSection2Reached = true;
				continue;
			}

			std::optional<UnsignedIntReadResult> intervalStartParseAttemptResult = tryReadUnsignedInt(line, 0);
			if (not intervalStartParseAttemptResult.has_value()) {
				return std::nullopt;
			}
			const UnsignedIntReadResult& intervalStartParseResult = intervalStartParseAttemptResult.value();

			if (line.at(intervalStartParseResult.indexAfter_) != '-') {
				return std::nullopt;
			}

			std::optional<UnsignedIntReadResult> intervalEndParseAttemptResult = tryReadUnsignedInt(line, intervalStartParseResult.indexAfter_ + 1);
			if (not intervalEndParseAttemptResult.has_value()) {
				return std::nullopt;
			}
			const UnsignedIntReadResult& intervalEndParseResult = intervalEndParseAttemptResult.value();

			if (intervalEndParseResult.indexAfter_ < line.size()) {
				return std::nullopt;
			}

			UnsignedInt intervalStart = intervalStartParseResult.result_;
			UnsignedInt intervalEnd = intervalEndParseResult.result_;
			if (intervalStart > intervalEnd) {
				return std::nullopt;
			}

			result.idIntervals_.push_back(IntegerInterval(intervalStart, intervalEnd));
		} else {
			std::optional<UnsignedIntReadResult> idParseAttemptResult = tryReadUnsignedInt(line, 0);
			if (not idParseAttemptResult.has_value()) {
				return std::nullopt;
			}
			const UnsignedIntReadResult& idParseResult = idParseAttemptResult.value();

			if (idParseResult.indexAfter_ < line.size()) {
				return std::nullopt;
			}

			result.ids_.push_back(idParseResult.result_);
		}
	}

	return result;
}
