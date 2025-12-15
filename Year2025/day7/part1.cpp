#include "part1.hh"
#include "fileutility.hh"

#include <cstddef>
#include <unordered_set>
#include <iostream>

const char sourceSymbol = 'S';
const char emptySpaceSymbol = '.';
const char splitterSymbol = '^';

std::optional<UnsignedInt> Part1::calculateNumSplits(std::ifstream& file) {
	UnsignedInt numSplits = 0;
	std::unordered_set<std::size_t> columnsWithBeam;

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
			if (not columnsWithBeam.empty()) {
				return std::nullopt;
			}
			columnsWithBeam.insert(currentLineLengthSoFar);
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

		std::unordered_set<std::size_t>::const_iterator iter = columnsWithBeam.find(currentLineLengthSoFar);
		if (iter != columnsWithBeam.cend()) {
			columnsWithBeam.erase(iter);
			columnsWithBeam.insert(currentLineLengthSoFar - 1);
			columnsWithBeam.insert(currentLineLengthSoFar + 1);
			numSplits += 1;
		}
		currentLineLengthSoFar += 1;
	}

	return numSplits;
}
