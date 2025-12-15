#ifndef MATH_HH
#define MATH_HH

#include "typealiases.hh"

namespace Math {

UnsignedInt IntLogFloor(UnsignedInt n, UnsignedInt base);

UnsignedInt numDigits(UnsignedInt n, UnsignedInt base);

Int IntPow(Int base, UnsignedInt exponent);

}

#endif // MATH_HH
