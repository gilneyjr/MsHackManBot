#ifndef BOMB_H
#define BOMB_H

#include "Point.h"

class Bomb : public Point {
private:
	int timeToExplode;
public:
	Bomb(size_t = 0u, size_t = 0u, int = -1);
	int getTimeToExplode();
};

#endif