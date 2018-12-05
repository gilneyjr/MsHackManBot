#include "Bug.h"

Bug::Bug(size_t row, size_t col, int type) :
	Point::Point(row, col),
	type(type) {}