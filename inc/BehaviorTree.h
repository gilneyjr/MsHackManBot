#ifndef BEHAVIORTREE_H
#define BEHAVIORTREE_H

class BehaviorTree {
public:
	virtual ~BehaviorTree();
	virtual bool run() = 0;
};

#endif