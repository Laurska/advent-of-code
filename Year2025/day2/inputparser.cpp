#include "inputparser.hh"
#include "digitcharutility.hh"

#include <iostream>

Interval::Interval(UnsignedInt inclusiveStart, UnsignedInt inclusiveEnd):
	inclusiveStart_(inclusiveStart), inclusiveEnd_(inclusiveEnd)
{}

EndOfFile::EndOfFile()
{}

ParseError::ParseError(const std::string &message):
	message_(message)
{}


InputParser::InputParser(std::ifstream& file):
	file_(&file)
{}

ParseAttemptResult InputParser::tryReadInterval() {
	UnsignedIntReadAttemptResult startReadAttemptResult = tryReadUnsignedInt();
	if (std::holds_alternative<ParseError>(startReadAttemptResult)) {
		return std::get<ParseError>(startReadAttemptResult);
	}
	if (std::holds_alternative<EndOfFile>(startReadAttemptResult)) {
		if (moreIntervalsExpected_) {
			return ParseError("Missing an interval start after a ','.");
		}
		return EndOfFile();
	}

	char startEndSeparator;
	if (not file_->get(startEndSeparator) or startEndSeparator != '-') {
		return ParseError("Missing a '-' after an interval start.");
	}

	UnsignedIntReadAttemptResult endReadAttemptResult = tryReadUnsignedInt();
	if (std::holds_alternative<ParseError>(endReadAttemptResult)) {
		return std::get<ParseError>(endReadAttemptResult);
	}
	if (std::holds_alternative<EndOfFile>(endReadAttemptResult)) {
		return ParseError("Missing an interval end after a '-'.");
	}

	char separatorBetweenIntervals;
	bool separatorBetweenIntervalsExists = static_cast<bool>(file_->get(separatorBetweenIntervals));
	if (not separatorBetweenIntervalsExists) {
		moreIntervalsExpected_ = false;
	} else if (separatorBetweenIntervals == ',') {
		moreIntervalsExpected_ = true;
	} else if (separatorBetweenIntervals == '\n') {
		moreIntervalsExpected_ = false;
	} else {
		int separatorAsInteger = static_cast<int>(separatorBetweenIntervals);
		return ParseError("Incorrect separator between intervals. ',' or '\n' expected, got " + std::string({separatorBetweenIntervals}) + " (" + std::to_string(separatorAsInteger) + ").");
	}

	UnsignedInt start = std::get<UnsignedInt>(startReadAttemptResult);
	UnsignedInt end = std::get<UnsignedInt>(endReadAttemptResult);
	intervalsReadSuccessfully_ += 1;

	//std::cout << "intervalsReadSuccessfully_: " << intervalsReadSuccessfully_ << std::endl;
	return Interval(start, end);
}

UnsignedIntReadAttemptResult InputParser::tryReadUnsignedInt() {
	char c;
	if (not file_->get(c)) {
		return EndOfFile();
	}
	if (not DigitCharUtility::isDigit(c)) {
		return ParseError("First digit of a positive integer expected, got " + std::string({c}));
	}
	if (c == '0') {
		// The first digit must be non-zero.
		return ParseError("File contains a number that begins with a 0-digit");
	}

	UnsignedInt reversedResult = DigitCharUtility::digitCharToNumber(c);
	UnsignedInt digitMultiplier = 1;
	std::streampos posInFileBeforeReadingChar = file_->tellg();
	while (file_->get(c) and DigitCharUtility::isDigit(c)) {
		digitMultiplier *= 10;
		reversedResult += DigitCharUtility::digitCharToNumber(c) * digitMultiplier;
		posInFileBeforeReadingChar = file_->tellg();
	}
	if (file_) {
		//std::cout << "Calling seekg to return to c:s position. c: " << c << std::endl;
		file_->seekg(posInFileBeforeReadingChar);
	}
	UnsignedInt correctResult = 0;
	while (digitMultiplier > 0) {
		correctResult += (reversedResult % 10) * digitMultiplier;
		reversedResult /= 10;
		digitMultiplier /= 10;
	}
	//std::cout << "Successfully read a positive integer: " << correctResult << std::endl;
	return correctResult;
}
