#pragma once
#include "Instance.h"

class Classifier
{
	
public:
	virtual void classify(Instance &instance) = 0;
	virtual void build(const std::vector<Instance> &data) = 0;
};

