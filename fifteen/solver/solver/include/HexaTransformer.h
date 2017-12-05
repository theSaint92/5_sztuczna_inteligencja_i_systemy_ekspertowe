#pragma once
#include "Transformer.h"
class HexaTransformer :
	public Transformer
{
public:
	uint64_t getState(std::vector<int> values);
	std::vector<int> getVector(int size,uint64_t state);
};

