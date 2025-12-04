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
	int DEBUG_position2 = startPos;
	unsigned int numberOfTimesPointingAtZero = 0;

	// just out of curiosity
	unsigned int numLines = 0;

	std::string line;
	while (std::getline(file, line)) {
		numLines += 1;

		char directionChar = line.front();
		if (directionChar != leftChar and directionChar != rightChar) {
			throw std::invalid_argument("Invalid direction character.");
		}
		int directionMultiplier = directionChar == leftChar ? -1 : 1;

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

		#if DEBUG_MAIN
		std::cout << "position before: " << position;
		#endif

		int movement = static_cast<int>(numSteps) * directionMultiplier;
		#if DEBUG_MAIN
		//std::cout << "; position + movement: " << (position + movement) << "; mod(position + movement, numOrientations): " << mod(position + movement, numOrientations);
		#endif
		position = mod(position + movement, numOrientations);
		if (position == 0) {
			numberOfTimesPointingAtZero += 1;
		}

		#if DEBUG_MAIN
		std::cout << "; movement: " << movement << "; new position: " << position << std::endl;
		#endif

		DEBUG_position2 = DEBUG_position2 + movement;
		std::cout << "DEBUG_position2: " << DEBUG_position2 << "; mod(DEBUG_position2, numOrientations): " << mod(DEBUG_position2, numOrientations) << std::endl;
		if (DEBUG_position2 % static_cast<int>(numOrientations) == 0 and position != 0) {
			throw std::logic_error("Bruh (line " + std::to_string(numLines) + ")");
		}
	}

	file.close();

	std::cout << "password: " << numberOfTimesPointingAtZero << std::endl;
	std::cout << "line count: " << numLines << std::endl;
}
