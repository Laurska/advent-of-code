#include "paperrollgrid.hh"

#include <stdexcept>

PaperRollGrid::PaperRollGrid(const std::vector<bool>& gridVec, std::size_t width, std::size_t height):
	gridVec_(gridVec), width_(width), height_(height)
{
	if (width * height != gridVec.size()) {
		throw std::invalid_argument("width and height do not match gridVec size.");
	}
}

bool PaperRollGrid::hasPaperRollAt(std::size_t x, std::size_t y) const {
	validateGridIndices(x, y);
	return gridVec_.at(x + width_ * y);
}

std::size_t PaperRollGrid::width() const {
	return width_;
}

std::size_t PaperRollGrid::height() const {
	return height_;
}

void PaperRollGrid::setCellState(std::size_t x, std::size_t y, bool hasPaperRoll) {
	validateGridIndices(x, y);
	gridVec_.at(x + width_ * y) = hasPaperRoll;
}

void PaperRollGrid::validateGridIndices(std::size_t x, std::size_t y) const {
	if (x >= width_ or y >= height_) {
		throw std::invalid_argument("At least one of the grid indices is out of bounds.");
	}
}
