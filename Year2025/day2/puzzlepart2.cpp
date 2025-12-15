#include "puzzlepart2.hh"
#include "math.hh"

#include <iostream>

UnsignedInt PuzzlePart2::calculateSumForInterval(UnsignedInt a, UnsignedInt b) {
	UnsignedInt sum = 0;

	for (UnsignedInt n = a; n <= b; ++n) {
		UnsignedInt numDigits = Math::numDigits(n, 10);
		bool consistsOfMultipleOfASequence = false;
		for (UnsignedInt subSequenceLen = 1; subSequenceLen <= numDigits / 2; ++subSequenceLen) {
			if (numDigits % subSequenceLen != 0) {
				continue;
			}
			UnsignedInt temp = n;
			UnsignedInt numSubSequences = numDigits / subSequenceLen;

			bool allSubSequencesAreSame = true;
			for (UnsignedInt iSubSequence = 1; iSubSequence < numSubSequences; ++iSubSequence) {
				UnsignedInt powOf10 = Math::IntPow(10, subSequenceLen);
				if (temp % powOf10 != temp / powOf10 % powOf10) {
					allSubSequencesAreSame = false;
					break;
				}
				temp /= powOf10;
			}
			if (allSubSequencesAreSame) {
				consistsOfMultipleOfASequence = true;
				break;
			}
		}

		if (consistsOfMultipleOfASequence) {
			//std::cout << "n: " << n << std::endl;
			sum += n;
		}
	}

	return sum;
}
