#ifndef GATE_H
#define GATE_H

#include "Point.h"

class Gate : public Point
{
private:
	char side;
public:
	Gate(size_t = 0u, size_t = 0u, char = '\0');
};

#endif