#ifndef PART1_HH
#define PART1_HH

#include "typealiases.hh"

#include <fstream>
#include <optional>

namespace Part1 {

std::optional<UnsignedInt> getMaxJoltagesSum(std::ifstream& file);

}

#endif // PART1_HH
