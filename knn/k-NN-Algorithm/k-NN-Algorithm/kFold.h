#pragma once
#include <vector>
#include "Instance.h"

class kFold
{
	std::vector< std::vector<Instance> > folds;
public:
	void createFolds(std::vector<Instance> vec, int numOfFolds);
	std::vector<Instance> getKFold(int k);
	std::vector<Instance> getAllButKFold(int k);
	unsigned int getSize();
};

