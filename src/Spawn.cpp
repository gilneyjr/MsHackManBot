#include "Spawn.h"

Spawn::Spawn(size_t row, size_t col, int timeToSpawn) :
	Point::Point(row, col),
	timeToSpawn(timeToSpawn) {}

int Spawn::getTimeToSpawn() {
	return timeToSpawn;
}