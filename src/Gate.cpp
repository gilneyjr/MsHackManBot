#include "Gate.h"

Gate::Gate(size_t row, size_t col, char side) : 
	Point::Point(row, col),
	side(side) {}