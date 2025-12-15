#ifndef PARSEDINPUT_HH
#define PARSEDINPUT_HH

#include "integerinterval.hh"

#include <vector>

struct ParsedInput {
	ParsedInput();

	std::vector<IntegerInterval> idIntervals_;
	std::vector<UnsignedInt> ids_;
};

#endif // PARSEDINPUT_HH
