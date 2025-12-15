#ifndef OPERATION_HH
#define OPERATION_HH

#include "typealiases.hh"

class Operation {
public:
	using Function = UnsignedInt(*)(UnsignedInt, UnsignedInt);

	Operation(char symbol, UnsignedInt identity, Function funct);

	char symbol() const;
	UnsignedInt identity() const;
	Function funct() const;

private:
	char symbol_;
	UnsignedInt identity_;
	Function funct_;
};

#endif // OPERATION_HH
