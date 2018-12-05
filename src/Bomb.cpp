#include "Bomb.h"

Bomb::Bomb(size_t row, size_t col, int timeToExplode) :
	Point::Point(row, col),
	timeToExplode(timeToExplode) {}

int Bomb::getTimeToExplode() {
	return timeToExplode;
}