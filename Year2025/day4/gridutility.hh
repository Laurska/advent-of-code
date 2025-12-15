#ifndef GRIDUTILITY_H
#define GRIDUTILITY_H

#include "paperrollgrid.hh"

namespace GridUtility {

unsigned int howManyNeighborsContainAPaperRoll(const PaperRollGrid& grid, std::size_t x, std::size_t y);

}

#endif // GRIDUTILITY_H
