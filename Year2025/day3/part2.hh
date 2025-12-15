#ifndef PART2_HH
#define PART2_HH

#include "typealiases.hh"

#include <fstream>
#include <optional>

namespace Part2 {

std::optional<UnsignedInt> getMaxJoltagesSum(std::ifstream& file);

}

#endif // PART2_HH
