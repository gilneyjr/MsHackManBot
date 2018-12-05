#ifndef SPAWNS
#define SPAWNS

#include "Point.h"

class Spawn : public Point {
private:
	int timeToSpawn;
public:
	Spawn(size_t = 0u, size_t = 0u, int  = -1);
	int getTimeToSpawn();
};

#endif