#include "part2.hh"
#include "fileutility.hh"

#include <cstddef>
#include <unordered_map>
#include <iostream>

const char sourceSymbol = 'S';
const char emptySpaceSymbol = '.';
const char splitterSymbol = '^';

std::optional<UnsignedInt> Part2::calculateNumTimelines(std::ifstream& file) {
	std::unordered_map<std::size_t, UnsignedInt> timeLineNumsSoFar;

	FileUtility::resetInputFileState(file);

	bool firstLine = true;
	bool emptySpaceLine = false;
	std::size_t lineLength;
	std::size_t currentLineLengthSoFar = 0;

	bool latestCharWasSplitter = false;

	for (;;) {
		char c;
		if (not file.get(c)) {
			if (firstLine or emptySpaceLine or currentLineLengthSoFar != 0) {
				return std::nullopt;
			}
			break;
		}

		if (c == '\n') {
			if (firstLine) {
				lineLength = currentLineLengthSoFar;
				firstLine = false;
			} else {
				if (currentLineLengthSoFar < lineLength) {
					return std::nullopt;
				}
			}
			currentLineLengthSoFar = 0;
			emptySpaceLine = not emptySpaceLine;
			continue;
		}
		if (not firstLine and currentLineLengthSoFar == lineLength) {
			return std::nullopt;
		}

		if (c == emptySpaceSymbol) {
			latestCharWasSplitter = false;
			currentLineLengthSoFar += 1;
			continue;
		}

		if (firstLine) {
			if (c != sourceSymbol) {
				return std::nullopt;
			}
			if (not timeLineNumsSoFar.empty()) {
				return std::nullopt;
			}
			timeLineNumsSoFar.insert({currentLineLengthSoFar, 1});
			currentLineLengthSoFar += 1;
			continue;
		}

		if (c != splitterSymbol) {
			return std::nullopt;
		}
		if (currentLineLengthSoFar == 0 or currentLineLengthSoFar == lineLength - 1) {
			// Splitter found at an edge of the diagram.
			return std::nullopt;
		}
		if (latestCharWasSplitter) {
			// There must be at least one unit of empty space between splitters.
			return std::nullopt;
		}
		latestCharWasSplitter = true;

		std::unordered_map<std::size_t, UnsignedInt>::iterator iter = timeLineNumsSoFar.find(currentLineLengthSoFar);
		if (iter != timeLineNumsSoFar.end()) {
			UnsignedInt numPossibleTimeLinesToThisSplitter = iter->second;
			timeLineNumsSoFar.erase(iter);
			std::unordered_map<std::size_t, UnsignedInt>::iterator leftIter = timeLineNumsSoFar.find(currentLineLengthSoFar - 1);
			if (leftIter != timeLineNumsSoFar.end()) {
				leftIter->second += numPossibleTimeLinesToThisSplitter;
			} else {
				timeLineNumsSoFar.insert({currentLineLengthSoFar - 1, numPossibleTimeLinesToThisSplitter});
			}
			std::unordered_map<std::size_t, UnsignedInt>::iterator rightIter = timeLineNumsSoFar.find(currentLineLengthSoFar + 1);
			if (rightIter != timeLineNumsSoFar.end()) {
				rightIter->second += numPossibleTimeLinesToThisSplitter;
			} else {
				timeLineNumsSoFar.insert({currentLineLengthSoFar + 1, numPossibleTimeLinesToThisSplitter});
			}
		}
		currentLineLengthSoFar += 1;
	}

	UnsignedInt numTimelines = 0;
	for (const std::pair<const std::size_t, UnsignedInt>& columnAndTimelineCount : timeLineNumsSoFar) {
		numTimelines += columnAndTimelineCount.second;
	}
	return numTimelines;
}
