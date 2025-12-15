#include "math.hh"
#include "flags.hh"

#include <stdexcept>
#include <iostream>

UnsignedInt Math::IntLogFloor(UnsignedInt n, UnsignedInt base) {
	if (base == 0 or base == 1) {
		throw std::invalid_argument("Logarithm is not defined for non-positive bases or base 1. got base = " + std::to_string(base) + ".");
	}
	if (n == 0) {
		throw std::invalid_argument("Logarithm is only defined for positive numbers. got n = " + std::to_string(n) + ".");
	}

	UnsignedInt result = 0;
	for (;;) {
		n /= base;
		if (n == 0) {
			return result;
		}
		result += 1;
	}
}

UnsignedInt Math::numDigits(UnsignedInt n, UnsignedInt base) {
	return Math::IntLogFloor(n, base) + 1;
}

Int Math::IntPow(Int base, UnsignedInt exponent) {
	if (exponent == 0) {
		if (base == 0) {
			throw std::invalid_argument("pow(0, 0) is undefined.");
		}
		return 1;
	}
	Int extraMultiplier = 1;
	while (exponent > 1) {
		#if DEBUG_INT_POW
		std::cout << "base: " << base << "; exponent: " << exponent << "; extraMultiplier: " << extraMultiplier << std::endl;
		#endif
		if (exponent % 2 == 1) {
			extraMultiplier *= base;
		}
		base *= base;
		exponent /= 2;
	}
	#if DEBUG_INT_POW
	std::cout << "after loop: base: " << base << "; exponent: " << exponent << "; extraMultiplier: " << extraMultiplier << std::endl;
	#endif
	return base * extraMultiplier;
}
