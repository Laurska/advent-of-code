#ifndef NEEDEDOPERATIONS_HH
#define NEEDEDOPERATIONS_HH

#include "typealiases.hh"
#include "operation.hh"

namespace NeededOperations {

const Operation addition = Operation('+', 0, [](UnsignedInt a, UnsignedInt b){ return a + b; });
const Operation multiplication = Operation('*', 1, [](UnsignedInt a, UnsignedInt b){ return a * b; });

}

#endif // NEEDEDOPERATIONS_HH
