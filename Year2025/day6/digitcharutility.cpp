#include "digitcharutility.hh"

#include <stdexcept>

bool DigitCharUtility::isDigitChar(char c) {
	return '0' <= c and c <= '9';
}

UnsignedInt DigitCharUtility::convertDigitCharToNumber(char digitChar) {
	if (not isDigitChar(digitChar)) {
		throw std::invalid_argument("Given character is not a digit character.");
	}
	return digitChar - '0';
}
