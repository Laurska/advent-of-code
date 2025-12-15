#ifndef INTEGERINTERVAL_H
#define INTEGERINTERVAL_H

#include "typealiases.hh"

class IntegerInterval {
public:
	IntegerInterval(UnsignedInt first, UnsignedInt last);

	UnsignedInt first() const;
	UnsignedInt last() const;

private:
	UnsignedInt first_;
	UnsignedInt last_;
};

#endif // INTEGERINTERVAL_H
