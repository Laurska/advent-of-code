#include "puzzlepart1usingsumformulas.hh"
#include "math.hh"

#include <stdexcept>
#include <iostream>

namespace {

UnsignedInt calculateSumForIntervalOfKs(UnsignedInt kMin, UnsignedInt kMax) {
	UnsignedInt geomSumElemCount = kMax - kMin + 1;

	UnsignedInt geomSum1 = Math::IntPow(100, kMin) / 100 * (1 - Math::IntPow(100, geomSumElemCount)) / (-99);
	UnsignedInt geomSum2 = Math::IntPow(10, kMin) / 10 * (1 - Math::IntPow(10, geomSumElemCount)) / (-9);
	UnsignedInt kMinPowOf1000 = Math::IntPow(1000, kMin);
	UnsignedInt geomSumElemCountPowOf1000 = Math::IntPow(1000, geomSumElemCount);
	UnsignedInt geomSum3 = kMinPowOf1000 / 100 * (1 - geomSumElemCountPowOf1000) / (-99);
	UnsignedInt geomSum4 = kMinPowOf1000 / 10 * (1 - geomSumElemCountPowOf1000) / (-9);

	return 9 * (geomSum1 - geomSum2 + geomSum3 + geomSum4) / 2;
}

}

// Calculates the sum of numbers that are in the integer interval [a, b] and
// whose base 10 -representation consists of a sequence of digits repeated twice.
UnsignedInt PuzzlePart1UsingSumFormulas::calculateSumForInterval(UnsignedInt a, UnsignedInt b) {
	if (b < a) {
		throw std::invalid_argument("b (interval inclusive end) must be greater than or equal to a (interval inclusive start).");
	}
	if (a == 0) {
		throw std::invalid_argument("Interval must only contain positive numbers.");
	}

	UnsignedInt kA = Math::numDigits(a, 10);
	UnsignedInt kB = Math::numDigits(b, 10);

	UnsignedInt mFirst;
	if (kA % 2 == 1) {
		mFirst = Math::IntPow(10, (kA - 1) / 2);
	} else {
		UnsignedInt powOf10 = Math::IntPow(10, kA / 2);
		UnsignedInt dAFirst = a / powOf10;
		UnsignedInt dALast = a % powOf10;
		if (dALast <= dAFirst) {
			mFirst = dAFirst;
		} else {
			mFirst = dAFirst + 1;
		}
	}
	UnsignedInt mLast;
	if (kB % 2 == 1) {
		mLast = Math::IntPow(10, (kB - 1) / 2) - 1;
	} else {
		UnsignedInt powOf10 = Math::IntPow(10, kB / 2);
		UnsignedInt dBFirst = b / powOf10;
		UnsignedInt dBLast = b % powOf10;
		if (dBLast >= dBFirst) {
			mLast = dBFirst;
		} else {
			mLast = dBFirst - 1;
		}
	}

	if (mFirst > mLast) {
		return 0;
	}

	UnsignedInt kFirst = Math::numDigits(mFirst, 10);
	UnsignedInt kLast = Math::numDigits(mLast, 10);
	if (kFirst == kLast) {
		return ((mLast - mFirst + 1) * (1 + Math::IntPow(10, kFirst)) * (mFirst + mLast)) / 2;
	}

	UnsignedInt kFirstPowOf10 = Math::IntPow(10, kFirst);
	UnsignedInt sKFirst = ((kFirstPowOf10 - mFirst) * (1 + kFirstPowOf10)) / 2;

	UnsignedInt kLastMinus1PowOf10 = Math::IntPow(10, kLast - 1);
	UnsignedInt kLastPowOf10 = kLastMinus1PowOf10 * 10;
	UnsignedInt sKLast = ((mLast - kLastMinus1PowOf10 + 1) * (1 + kLastPowOf10) * (mLast + kLastMinus1PowOf10)) / 2;

	if (kLast - kFirst == 1) {
		return sKFirst + sKLast;
	}

	UnsignedInt kMin = kFirst + 1;
	UnsignedInt kMax = kLast - 1;
	UnsignedInt sKsBetween = calculateSumForIntervalOfKs(kMin, kMax);

	return sKFirst + sKsBetween + sKLast;
}
