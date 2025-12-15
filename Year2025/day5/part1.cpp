#include "part1.hh"
#include "integerintervalunion.hh"

#include <iostream>

UnsignedInt Part1::findHowManyAvailableIngredientIdsAreFresh(const ParsedInput& parsedInput) {
	const IntegerIntervalUnion intervalUnion(parsedInput.idIntervals_);
	UnsignedInt howManyFresh = 0;
	for (UnsignedInt id : parsedInput.ids_) {
		howManyFresh += static_cast<UnsignedInt>(intervalUnion.containsInteger(id));
	}
	return howManyFresh;
}
