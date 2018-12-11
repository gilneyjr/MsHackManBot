#ifndef SELECTOR_H
#define SELECTOR_H

#include <vector>
#include "BehaviorTree.h"
#include "Composite.h"

class Selector : public Composite
{
public:
	bool run();
};

#endif