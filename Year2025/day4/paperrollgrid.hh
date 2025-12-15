#ifndef PAPERROLLGRID_HH
#define PAPERROLLGRID_HH

#include <vector>
#include <cstddef>

class PaperRollGrid {
public:
	PaperRollGrid(const std::vector<bool>& gridVec, std::size_t width, std::size_t height);

	bool hasPaperRollAt(std::size_t x, std::size_t y) const;

	std::size_t width() const;
	std::size_t height() const;

	void setCellState(std::size_t x, std::size_t y, bool hasPaperRoll);

private:
	void validateGridIndices(std::size_t x, std::size_t y) const;

	std::vector<bool> gridVec_;
	std::size_t width_;
	std::size_t height_;
};

#endif // PAPERROLLGRID_HH
