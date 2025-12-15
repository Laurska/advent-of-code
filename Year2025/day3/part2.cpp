#include "part2.hh"
#include "digitcharutility.hh"
#include "math.hh"

#include <iostream>

const UnsignedInt numDigitsToChoose = 12;

std::optional<UnsignedInt> Part2::getMaxJoltagesSum(std::ifstream& file) {
	UnsignedInt sum = 0;

	std::string line;
	std::size_t lineLength = 0;
	while (std::getline(file, line)) {
		if (line.size() < numDigitsToChoose) {
			return std::nullopt;
		}
		if (lineLength == 0) {
			// First line.
			lineLength = line.size();
		} else if (line.size() != lineLength) {
			return std::nullopt;
		}

		//UnsignedInt digits = 0;
		UnsignedInt digitMultiplier = Math::IntPow(10, numDigitsToChoose - 1); // I should add the IntPow function instead of hardcoding this.
		std::size_t nextDigitSearchStartIndex = 0;
		for (UnsignedInt iDigitChoice = 0; iDigitChoice < numDigitsToChoose; ++iDigitChoice) {
			UnsignedInt bestCandidate = 0;
			for (std::size_t iCandidate = nextDigitSearchStartIndex; iCandidate < lineLength - (numDigitsToChoose - 1 - iDigitChoice); ++iCandidate) {
				char candidateAsChar = line.at(iCandidate);
				if (not DigitCharUtility::isDigitChar(candidateAsChar)) {
					return std::nullopt;
				}

				UnsignedInt candidate = DigitCharUtility::digitCharToNumber(candidateAsChar);
				if (candidate <= bestCandidate) {
					continue;
				}

				bestCandidate = candidate;
				nextDigitSearchStartIndex = iCandidate + 1;
			}

			sum += bestCandidate * digitMultiplier;
			//digits += bestCandidate * digitMultiplier;
			digitMultiplier /= 10;
		}

		//std::cout << "Digits: " << digits << std::endl;
		//sum += digits;
	}

	return sum;
}
