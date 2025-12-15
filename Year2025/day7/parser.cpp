#include "parser.hh"
#include "fileutility.hh"

#include <stdexcept>

const char sourceSymbol = 'S';
const char emptySpaceSymbol = '.';
const char splitterSymbol = '^';

Parser::Parser(std::ifstream& file):
	file_(&file)
{
	FileUtility::resetInputFileState(file);
}

Token Parser::getNextToken() {
	if (not canContinue_) {
		throw std::logic_error(
			"Attempt to continue parsing after finishing it"
			" or encountering an error."
		);
	}

	Token token = continueParsing();
	if (std::holds_alternative<ParseError>(token) or std::holds_alternative<EndOfFile>(token)) {
		canContinue_ = false;
	}
	return token;
}

Token Parser::continueParsing() {
	for (;;) {
		char c;
		if (not file_->get(c)) {
			if (firstLine_ or emptySpaceLine_ or currentLineLengthSoFar_ != 0) {
				return ParseError("File ends at an invalid position.");
			}
			return EndOfFile();
		}

		if (c == '\n') {
			if (firstLine_) {
				if (not sourceHasBeenFound_) {
					return ParseError("Source missing");
				}
				lineLength_ = currentLineLengthSoFar_;
				firstLine_ = false;
			} else if (currentLineLengthSoFar_ < lineLength_) {
				return ParseError(
					"Found a line that is shorter than earlier ones."
					" All lines must have the same length."
				);
			}
			currentLineLengthSoFar_ = 0;
			emptySpaceLine_ = not emptySpaceLine_;
			return NewLine();
		}
		if (not firstLine_ and currentLineLengthSoFar_ == lineLength_) {
			return ParseError(
				"Found a line that is longer than earlier ones."
				" All lines must have the same length."
			);
		}

		if (c == emptySpaceSymbol) {
			latestCharWasSplitter_ = false;
			currentLineLengthSoFar_ += 1;
			continue;
		}

		if (firstLine_) {
			if (c != sourceSymbol) {
				return ParseError("Unexpected character in the first line (source line): " + std::string({c}));
			}
			if (sourceHasBeenFound_) {
				return ParseError("There must be only one source.");
			}
			std::size_t sourceHorIndex = currentLineLengthSoFar_;
			sourceHasBeenFound_ = true;
			currentLineLengthSoFar_ += 1;
			return Source(sourceHorIndex);
		}

		if (c != splitterSymbol) {
			return ParseError("Unexpected character in a splitter line: " + std::string({c}));
		}
		if (currentLineLengthSoFar_ == 0 or currentLineLengthSoFar_ == lineLength_ - 1) {
			return ParseError(
				"Splitters must not be at the edges of the diagram."
				" There must be at least one unit of empty space on both sides of a splitter."
			);
		}
		if (latestCharWasSplitter_) {
			return ParseError(
				"Found splitters that are right beside each other."
				" At least one unit of empty space between splitters is required."
			);
		}
		latestCharWasSplitter_ = true;

		std::size_t splitterHorIndex = currentLineLengthSoFar_;
		currentLineLengthSoFar_ += 1;
		return Splitter(splitterHorIndex);
	}
}
