#ifndef INPUTPARSING_HH
#define INPUTPARSING_HH

#include "paperrollgrid.hh"

#include <fstream>
#include <optional>

namespace InputParsing {

std::optional<PaperRollGrid> parseFile(std::ifstream& file);

}

#endif // INPUTPARSING_HH
