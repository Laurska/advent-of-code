#include "integerinterval.hh"

IntegerInterval::IntegerInterval(UnsignedInt first, UnsignedInt last):
	first_(first), last_(last)
{}

UnsignedInt IntegerInterval::first() const {
	return first_;
}

UnsignedInt IntegerInterval::last() const {
	return last_;
}
