#include "token.hh"

ParseError::ParseError(std::string message):
	message_(std::move(message))
{}

const std::string& ParseError::message() const {
	return message_;
}

EndOfFile::EndOfFile() {
}

NewLine::NewLine() {
}

Source::Source(std::size_t horizontalIndex):
	horizontalIndex_(horizontalIndex)
{}

std::size_t Source::horizontalIndex() const {
	return horizontalIndex_;
}

Splitter::Splitter(std::size_t horizontalIndex):
	horizontalIndex_(horizontalIndex)
{}

std::size_t Splitter::horizontalIndex() const {
	return horizontalIndex_;
}
