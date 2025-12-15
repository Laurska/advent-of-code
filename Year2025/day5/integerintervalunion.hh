#ifndef INTEGERINTERVALUNION_H
#define INTEGERINTERVALUNION_H

#include "integerinterval.hh"

#include <vector>

class IntegerIntervalStartComparer {
public:
	IntegerIntervalStartComparer();

	bool operator()(const IntegerInterval& lhs, const IntegerInterval& rhs);
};

class IntegerIntervalUnion {
public:
	IntegerIntervalUnion(const std::vector<IntegerInterval>& intervals);

	bool containsInteger(UnsignedInt n) const;

	const std::vector<IntegerInterval>& distinctIntervals() const;

private:
	std::vector<IntegerInterval> distinctIntervals_;
};

#endif // INTEGERINTERVALUNION_H
