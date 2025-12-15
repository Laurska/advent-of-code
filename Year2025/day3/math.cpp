#include "math.hh"

#include <stdexcept>

Int Math::IntPow(Int base, UnsignedInt exponent) {
	if (exponent == 0) {
		if (base == 0) {
			throw std::invalid_argument("pow(0, 0) is undefined.");
		}
		return 1;
	}

	Int extraMultiplier = 1;
	while (exponent > 1) {
		if (exponent % 2 == 1) {
			extraMultiplier *= base;
		}
		base *= base;
		exponent /= 2;
	}
	return base * extraMultiplier;
}
