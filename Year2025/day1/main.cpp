#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

#define DEBUG_MAIN true
#define DEBUG_MOD false

//const std::string fileName = "example_input.txt";
const std::string fileName = "input.txt";

const char leftChar = 'L';
const char rightChar = 'R';
const int startPos = 50;
const unsigned int numOrientations = 100;

bool isDigit(char c) {
	return c >= '0' and c <= '9';
}

unsigned int mod(int n, unsigned int m) {
	int result = n % static_cast<int>(m);
	if (result < 0) {
		result += m;
	}
	return result;
}

int main() {
	std::ifstream file(fileName);
	if (!file) {
		throw std::invalid_argument("Could not open file " + fileName + ".");
	}

	int position = startPos;
	unsigned int numberOfTimesPointingAtZeroAfterRotation = 0;
	unsigned int numberOfTimesPointingAtZero = 0;

	// just out of curiosity
	unsigned int numLines = 0;

	std::string line;
	while (std::getline(file, line)) {
		numLines += 1;

		// Parsing
		char directionChar = line.front();
		if (directionChar != leftChar and directionChar != rightChar) {
			throw std::invalid_argument("Invalid direction character.");
		}
		bool rotateToLeft = directionChar == leftChar;

		unsigned int numSteps = 0;
		unsigned int digitMultiplier = 1;
		for (unsigned int iChar = line.size() - 1; iChar > 0; --iChar, digitMultiplier *= 10) {
			char c = line.at(iChar);
			if (!isDigit(c)) {
				throw std::invalid_argument("Non-digit character on a line after the direction character.");
			}
			unsigned int digitAsInteger = c - '0';
			numSteps += digitAsInteger * digitMultiplier;
		}

		// Main logic
		// Part 1 (position is also used in Part 2)
		int directionMultiplier = rotateToLeft ? -1 : 1;
		int movement = static_cast<int>(numSteps) * directionMultiplier;
		int newPosition = mod(position + movement, numOrientations);
		if (newPosition == 0) {
			numberOfTimesPointingAtZeroAfterRotation += 1;
		}

		// Part 2
		unsigned int numStepsToReachZeroOnce = (rotateToLeft and position != 0) ? position : numOrientations - position;
		if (numSteps >= numStepsToReachZeroOnce) {
			numberOfTimesPointingAtZero += 1;

			unsigned int numRemainingSteps = numSteps - numStepsToReachZeroOnce;
			numberOfTimesPointingAtZero += numRemainingSteps / numOrientations;
		}

		// Position updating (needed in both parts).
		position = newPosition;
	}

	file.close();

	std::cout << "password (part 1): " << numberOfTimesPointingAtZeroAfterRotation << std::endl;
	std::cout << "password (part 2): " << numberOfTimesPointingAtZero << std::endl;
	std::cout << "line count: " << numLines << std::endl;
}
