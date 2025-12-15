#include "part2.hh"
#include "integerintervalunion.hh"

UnsignedInt Part2::calculateHowManyIngredientIdsAreInFreshIntervals(const ParsedInput& parsedInput) {
	const IntegerIntervalUnion intervalUnion(parsedInput.idIntervals_);
	UnsignedInt result = 0;
	for (const IntegerInterval& interval : intervalUnion.distinctIntervals()) {
		result += interval.last() - interval.first() + 1;
	}
	return result;
}
