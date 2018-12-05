#ifndef POINT_H
#define POINT_H

#include <cstddef>

class Point
{
private:
	size_t row;
	size_t col;

public:
	Point(size_t = 0u, size_t = 0u);
	size_t getRow();
	void setRow(size_t);
	size_t getCol();
	void setCol(size_t);
};

#endif