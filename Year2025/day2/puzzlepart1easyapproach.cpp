#include "puzzlepart1easyapproach.hh"
#include "math.hh"

UnsignedInt PuzzlePart1EasyApproach::calculateSumForInterval(UnsignedInt a, UnsignedInt b) {
	UnsignedInt sum = 0;
	for (UnsignedInt n = a; n <= b; ++n) {
		UnsignedInt numDigits = Math::numDigits(n, 10);
		if (numDigits % 2 == 1) {
			// Set n equal to the last number whose number of digits is equal to
			// numDigits. That way, the incremtation code in the loop header
			// will set n equal to the first number whose number of digits
			// is numDigits + 1.
			n = Math::IntPow(10, numDigits) - 1;
			continue;
		}
		UnsignedInt firstDigits = n / Math::IntPow(10, numDigits / 2);
		UnsignedInt lastDigits = n % Math::IntPow(10, numDigits / 2);
		if (firstDigits == lastDigits) {
			sum += n;
		}
	}

	return sum;
}
