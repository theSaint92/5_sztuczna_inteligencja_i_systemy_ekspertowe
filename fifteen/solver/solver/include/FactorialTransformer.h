#pragma once
#include "Transformer.h"
class FactorialTransformer :
	public Transformer
{
	int countSmallerThan(int number,const std::vector<int> &values);
public:
	uint64_t getState(std::vector<int> values);
	std::vector<int> getVector(int size,uint64_t state);
	//uint64_t getNextState(int rows, int cols, uint64_t currentState, char moveDirection);
};

