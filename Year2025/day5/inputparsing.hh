#ifndef INPUTPARSING_HH
#define INPUTPARSING_HH

#include "parsedinput.hh"
#include "typealiases.hh"

#include <optional>
#include <fstream>

struct UnsignedIntReadResult {
	UnsignedIntReadResult(UnsignedInt result, std::size_t indexAfter);

	UnsignedInt result_;
	std::size_t indexAfter_;
};

namespace InputParsing {

std::optional<ParsedInput> tryParseFile(std::ifstream& file);

}

#endif // INPUTPARSING_HH
