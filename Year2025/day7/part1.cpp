#include "part1.hh"
#include "parser.hh"

#include <cstddef>
#include <unordered_set>
#include <iostream>

std::optional<UnsignedInt> Part1::calculateNumSplits(std::ifstream& file) {
	UnsignedInt numSplits = 0;
	std::unordered_set<std::size_t> columnsWithBeam;

	Parser parser(file);
	for (;;) {
		const Token token = parser.getNextToken();
		if (std::holds_alternative<ParseError>(token)) {
			const ParseError& errorToken = std::get<ParseError>(token);
			std::cout << "Parse error: " << errorToken.message() << std::endl;
			return std::nullopt;
		}
		if (std::holds_alternative<EndOfFile>(token)) {
			break;
		}

		if (std::holds_alternative<Source>(token)) {
			const Source& sourceToken = std::get<Source>(token);
			columnsWithBeam.insert(sourceToken.horizontalIndex());
			continue;
		}
		if (std::holds_alternative<Splitter>(token)) {
			const Splitter& splitterToken = std::get<Splitter>(token);
			std::size_t horIndex = splitterToken.horizontalIndex();
			std::unordered_set<std::size_t>::const_iterator iter = columnsWithBeam.find(horIndex);
			if (iter != columnsWithBeam.cend()) {
				columnsWithBeam.erase(iter);
				columnsWithBeam.insert(horIndex - 1);
				columnsWithBeam.insert(horIndex + 1);
				numSplits += 1;
			}
		}
	}

	return numSplits;
}
