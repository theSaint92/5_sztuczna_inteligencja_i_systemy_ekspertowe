#pragma once
#include <vector>

class Transformer
{
public:
	virtual uint64_t getState(std::vector<int> values)=0;
	virtual std::vector<int> getVector(uint64_t state)=0;
};

