#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <vector>
#include "BehaviorTree.h"
#include "Composite.h"

class Sequence : public Composite {
public:
	bool run();
};

#endif