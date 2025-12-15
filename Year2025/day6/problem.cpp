#include "problem.hh"

Problem::Problem(const Operation& operation, std::size_t widthInFile):
	operation_(&operation), widthInFile_(widthInFile), answer_(operation.identity())
{}

std::size_t Problem::widthInFile() const {
	return widthInFile_;
}

UnsignedInt Problem::answer() const {
	return answer_;
}

void Problem::updateAnswer(UnsignedInt newOperand) {
	answer_ = operation_->funct()(answer_, newOperand);
}
