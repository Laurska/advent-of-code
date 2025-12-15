#ifndef PART1_HH
#define PART1_HH

#include "typealiases.hh"

#include <optional>
#include <fstream>

namespace Part1 {

std::optional<UnsignedInt> calculateNumSplits(std::ifstream& file);

}

#endif // PART1_HH
