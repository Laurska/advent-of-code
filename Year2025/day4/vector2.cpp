#include "vector2.hh"

Vector2::Vector2(int x, int y):
	x_(x), y_(y)
{}

int Vector2::x() const {
	return x_;
}

int Vector2::y() const {
	return y_;
}
