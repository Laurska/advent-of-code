#include "gridutility.hh"

unsigned int GridUtility::howManyNeighborsContainAPaperRoll(const PaperRollGrid& grid, std::size_t x, std::size_t y) {
	std::size_t width = grid.width();
	std::size_t height = grid.height();

	unsigned int count =
		static_cast<unsigned int>(x < width - 1 and grid.hasPaperRollAt(x + 1, y))
		+ static_cast<unsigned int>(x < width - 1 and y < height - 1 and grid.hasPaperRollAt(x + 1, y + 1))
		+ static_cast<unsigned int>(y < height - 1 and grid.hasPaperRollAt(x, y + 1))
		+ static_cast<unsigned int>(x > 0 and y < height - 1 and grid.hasPaperRollAt(x - 1, y + 1))
		+ static_cast<unsigned int>(x > 0 and grid.hasPaperRollAt(x - 1, y))
		+ static_cast<unsigned int>(x > 0 and y > 0 and grid.hasPaperRollAt(x - 1, y - 1))
		+ static_cast<unsigned int>(y > 0 and grid.hasPaperRollAt(x, y - 1))
		+ static_cast<unsigned int>(x < width - 1 and y > 0 and grid.hasPaperRollAt(x + 1, y - 1));

	return count;
}
