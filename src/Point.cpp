#include "Point.h"

Point::Point(size_t row, size_t col) : row(row), col(col) {}

size_t Point::getRow() {
	return row;
}
void Point::setRow(size_t row) {
	this->row = row;
}
size_t Point::getCol() {
	return col;
}
void Point::setCol(size_t col) {
	this->col = col;
}