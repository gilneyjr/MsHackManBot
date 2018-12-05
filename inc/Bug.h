#ifndef BUG_H
#define BUG_H

#include "Point.h"

class Bug : public Point
{
private:
	int type;
public:
	Bug(size_t  = 0u, size_t  = 0u, int  = -1);
};

#endif