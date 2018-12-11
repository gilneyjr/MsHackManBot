#include "Condition.h"

Condition::Condition(std::function<bool()> conditionFunc) {
	this->conditionFunc = conditionFunc;
}

bool Condition::run() {
	return conditionFunc();
}