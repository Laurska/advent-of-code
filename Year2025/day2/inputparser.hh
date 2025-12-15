#ifndef INPUTPARSER_H
#define INPUTPARSER_H

#include "typealiases.hh"

#include <string>
#include <variant>
#include <fstream>

struct Interval {
	Interval(UnsignedInt inclusiveStart, UnsignedInt inclusiveEnd);

	UnsignedInt inclusiveStart_;
	UnsignedInt inclusiveEnd_;
};

struct EndOfFile {
	EndOfFile();
};

struct ParseError {
	ParseError(const std::string& message);

	std::string message_;
};

using UnsignedIntReadAttemptResult = std::variant<UnsignedInt, EndOfFile, ParseError>;
using ParseAttemptResult = std::variant<Interval, EndOfFile, ParseError>;

class InputParser {
public:
	InputParser(std::ifstream& file);

	// Reads an interval. Also consumes the separator character (,) between
	// intervals.
	ParseAttemptResult tryReadInterval();

private:
	UnsignedIntReadAttemptResult tryReadUnsignedInt();

	std::ifstream* file_;
	bool moreIntervalsExpected_ = false;

	UnsignedInt intervalsReadSuccessfully_ = 0;
};

#endif // INPUTPARSER_H
