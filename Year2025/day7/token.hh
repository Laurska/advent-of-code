#ifndef TOKEN_HH
#define TOKEN_HH

#include <cstddef>
#include <variant>
#include <string>

class ParseError {
public:
	ParseError(std::string message);

	const std::string& message() const;

private:
	std::string message_;
};

class EndOfFile {
public:
	EndOfFile();

private:
};

class NewLine {
public:
	NewLine();

private:
};

class Source {
public:
	Source(std::size_t horizontalIndex);

	std::size_t horizontalIndex() const;

private:
	std::size_t horizontalIndex_;
};

class Splitter {
public:
	Splitter(std::size_t horizontalIndex);

	std::size_t horizontalIndex() const;

private:
	std::size_t horizontalIndex_;
};

using Token = std::variant<ParseError, EndOfFile, NewLine, Source, Splitter>;

#endif // TOKEN_HH
