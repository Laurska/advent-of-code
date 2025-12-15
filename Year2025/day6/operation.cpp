#include "operation.hh"

Operation::Operation(char symbol, UnsignedInt identity, Function funct):
	symbol_(symbol), identity_(identity), funct_(funct)
{}

char Operation::symbol() const {
	return symbol_;
}

UnsignedInt Operation::identity() const {
	return identity_;
}

Operation::Function Operation::funct() const {
	return funct_;
}
