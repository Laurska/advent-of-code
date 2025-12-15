#include "inputparsing.hh"

#include <cstddef>
#include <vector>

std::optional<PaperRollGrid> InputParsing::parseFile(std::ifstream& file) {
	std::vector<bool> gridVec;

	std::size_t lineLength;
	std::size_t currentLineLength = 0;
	bool isFirstLine = true;

	for (;;) {
		char c;
		if (not file.get(c)) {
			if (isFirstLine or currentLineLength > 0) {
				return std::nullopt;
			}
			break;
		}
		if (c == '\n') {
			if (isFirstLine) {
				if (currentLineLength == 0) {
					return std::nullopt;
				}
				lineLength = currentLineLength;
				isFirstLine = false;
			} else if (currentLineLength < lineLength) {
				return std::nullopt;
			}

			currentLineLength = 0;
			continue;
		}
		if (not isFirstLine and currentLineLength == lineLength) {
			return std::nullopt;
		}
		if (c != '.' and c != '@') {
			return std::nullopt;
		}

		currentLineLength += 1;

		gridVec.push_back(c == '@');
	}

	return PaperRollGrid(gridVec, lineLength, gridVec.size() / lineLength);
}
