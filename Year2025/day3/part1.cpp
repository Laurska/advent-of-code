#include "part1.hh"
#include "digitcharutility.hh"

#include <algorithm>
#include <iostream>

std::optional<UnsignedInt> Part1::getMaxJoltagesSum(std::ifstream& file) {
	bool firstLine = true;
	std::size_t currentLineLength = 0;
	std::size_t lineLength = 0;

	std::optional<UnsignedInt> firstDigit = std::nullopt;
	std::optional<UnsignedInt> secondDigit = std::nullopt;
	std::optional<UnsignedInt> previousFirstDigit = std::nullopt;

	UnsignedInt sumOfMaxJoltagesOfBanks = 0;
	for (;;) {
		char c;
		if (not file.get(c)) {
			if (firstDigit.has_value()) {
				// In this case, there have been digits after the last '\n'.
				return std::nullopt;
			}
			return sumOfMaxJoltagesOfBanks;
		}
		if (c == '\n') {
			if (currentLineLength < 2) {
				std::cout << "Line is shorter than 2 characters." << std::endl;
				return std::nullopt;
			}
			if (not firstLine and currentLineLength < lineLength) {
				std::cout << "Line is shorter than earlier lines." << std::endl;
				return std::nullopt;
			}

			if (firstLine) {
				lineLength = currentLineLength;
			}
			firstLine = false;

			// Sum update and line state cleanup.
			if (secondDigit == std::nullopt) {
				// This is for situations where the largest digit
				// is the last digit.
				secondDigit = firstDigit.value();
				firstDigit = previousFirstDigit.value();
			}
			sumOfMaxJoltagesOfBanks += firstDigit.value() * 10 + secondDigit.value();

			firstDigit = std::nullopt;
			secondDigit = std::nullopt;
			previousFirstDigit = std::nullopt;
			currentLineLength = 0;
			continue;
		}
		if (not firstLine and currentLineLength == lineLength) {
			std::cout << "Line is longer than earlier lines. lineLength: " << lineLength << "; currentLineLength: " << currentLineLength << std::endl;
			return std::nullopt;
		}
		if (not DigitCharUtility::isDigitChar(c)) {
			return std::nullopt;
		}

		currentLineLength += 1;

		UnsignedInt digitAsNumber = DigitCharUtility::digitCharToNumber(c);
		if (not firstDigit.has_value()) {
			firstDigit = digitAsNumber;
		} else if (digitAsNumber > firstDigit.value()) {
			previousFirstDigit = firstDigit.value();
			firstDigit = digitAsNumber;
			secondDigit = std::nullopt;
		} else if (not secondDigit.has_value() or digitAsNumber > secondDigit.value()) {
			secondDigit = digitAsNumber;
		}
	}
}
