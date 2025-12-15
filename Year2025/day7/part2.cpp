#include "part2.hh"
#include "parser.hh"

#include <cstddef>
#include <unordered_map>
#include <iostream>

namespace {

void addPossibleTimelinesToColumn(std::unordered_map<std::size_t, UnsignedInt>& timeLineCountsSoFar, std::size_t column, UnsignedInt howManyToAdd) {
	std::unordered_map<std::size_t, UnsignedInt>::iterator iter = timeLineCountsSoFar.find(column);
	if (iter != timeLineCountsSoFar.end()) {
		iter->second += howManyToAdd;
	} else {
		timeLineCountsSoFar.insert({column, howManyToAdd});
	}
}

}

std::optional<UnsignedInt> Part2::calculateNumTimelines(std::ifstream& file) {
	std::unordered_map<std::size_t, UnsignedInt> timeLineCountsSoFar;

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
			timeLineCountsSoFar.insert({sourceToken.horizontalIndex(), 1});
			continue;
		}
		if (std::holds_alternative<Splitter>(token)) {
			const Splitter& splitterToken = std::get<Splitter>(token);
			const std::size_t horIndex = splitterToken.horizontalIndex();
			std::unordered_map<std::size_t, UnsignedInt>::iterator iter = timeLineCountsSoFar.find(horIndex);
			if (iter != timeLineCountsSoFar.end()) {
				UnsignedInt numPossibleTimelinesToThisSplitter = iter->second;
				timeLineCountsSoFar.erase(iter);
				addPossibleTimelinesToColumn(timeLineCountsSoFar, horIndex - 1, numPossibleTimelinesToThisSplitter);
				addPossibleTimelinesToColumn(timeLineCountsSoFar, horIndex + 1, numPossibleTimelinesToThisSplitter);
			}
		}
	}

	UnsignedInt numTimelines = 0;
	for (const std::pair<const std::size_t, UnsignedInt>& columnAndTimelineCount : timeLineCountsSoFar) {
		numTimelines += columnAndTimelineCount.second;
	}
	return numTimelines;
}
