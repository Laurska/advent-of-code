#include "digitcharutility.hh"

#include <stdexcept>

bool DigitCharUtility::isDigit(char c) {
	return c >= '0' and c <= '9';
}

UnsignedInt DigitCharUtility::digitCharToNumber(char digitChar) {
	if (not isDigit(digitChar)) {
		throw std::invalid_argument("digitChar must be a digit character.");
	}
	return digitChar - '0';
}
