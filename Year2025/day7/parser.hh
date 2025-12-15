#ifndef PARSER_HH
#define PARSER_HH

#include "token.hh"

#include <fstream>

class Parser {
public:
	Parser(std::ifstream& file);

	Token getNextToken();

private:
	Token continueParsing();

	std::ifstream* file_;

	// This is false if an error has been encountered or if the end of the
	// file has been reached.
	bool canContinue_ = true;

	bool firstLine_ = true;
	bool emptySpaceLine_ = false;
	std::size_t lineLength_;
	std::size_t currentLineLengthSoFar_ = 0;

	bool sourceHasBeenFound_ = false;
	bool latestCharWasSplitter_ = false;
};

#endif // PARSER_HH
