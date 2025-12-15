#ifndef PROBLEM_HH
#define PROBLEM_HH

#include "operation.hh"

#include <cstddef>

class Problem {
public:
	Problem(const Operation& operation, std::size_t widthInFile);

	std::size_t widthInFile() const;
	UnsignedInt answer() const;

	void updateAnswer(UnsignedInt newOperand);

private:
	const Operation* operation_;
	std::size_t widthInFile_;
	UnsignedInt answer_;
};

#endif // PROBLEM_HH
