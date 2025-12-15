#include "integerintervalunion.hh"

#include <algorithm>
#include <iostream>

// IntegerIntervalStartComparer implementation
IntegerIntervalStartComparer::IntegerIntervalStartComparer() {
}

bool IntegerIntervalStartComparer::operator()(const IntegerInterval& lhs, const IntegerInterval& rhs) {
	return lhs.first() > rhs.first();
}

// IntegerIntervalUnion implementations
IntegerIntervalUnion::IntegerIntervalUnion(const std::vector<IntegerInterval>& intervals) {
	if (intervals.empty()) {
		return;
	}

	IntegerIntervalStartComparer comparer;
	std::vector<IntegerInterval> heapVec = intervals;
	std::make_heap(heapVec.begin(), heapVec.end(), comparer);

	distinctIntervals_.push_back(heapVec.front());
	std::pop_heap(heapVec.begin(), heapVec.end(), comparer);
	for (std::size_t iInterval = 1; iInterval < heapVec.size(); ++iInterval) {
		const IntegerInterval intervalToAdd = heapVec.front();
		std::pop_heap(heapVec.begin(), heapVec.end() - iInterval, comparer);

		const IntegerInterval& lastExistingInterval = distinctIntervals_.back();

		if (intervalToAdd.first() <= lastExistingInterval.last() + 1) {
			distinctIntervals_.back() = IntegerInterval(lastExistingInterval.first(), std::max(lastExistingInterval.last(), intervalToAdd.last()));
		} else {
			distinctIntervals_.push_back(intervalToAdd);
		}
		//std::cout << "intervalToAdd: " << intervalToAdd.first() << " " << intervalToAdd.last() << std::endl;
		//std::cout << "iInterval: " << iInterval << std::endl;
	}

	//std::cout << "heapVec.size(): "<< heapVec.size() << std::endl;
	//std::cout << "intervals_.size(): "<< intervals_.size() << std::endl;
}

bool IntegerIntervalUnion::containsInteger(UnsignedInt n) const {
	std::size_t l = 0;
	std::int64_t r = distinctIntervals_.size() - 1;
	while (static_cast<std::int64_t>(l) <= r) {
		std::size_t m = l + (r - l) / 2;
		const IntegerInterval& interval = distinctIntervals_.at(m);
		if (interval.last() < n) {
			l = m + 1;
		} else if (interval.first() > n) {
			r = m - 1;
		} else {
			return true;
		}
	}
	return false;
}

const std::vector<IntegerInterval>& IntegerIntervalUnion::distinctIntervals() const {
	return distinctIntervals_;
}
