#pragma once
#include <vector>

class Transformer
{
public:
	/*
	 * Function transforming vector to uint64_t state
	 */
	virtual uint64_t getState(std::vector<int> values)=0;

	/*
	 * Function transformig state to vector of values that can be used in Board class
	 */
	virtual std::vector<int> getVector(int size, uint64_t state)=0;
	
	/*
	 * UNIMPLEMENTED AND UNUSED BUT POTENTIALY COULD SPEEDUP WHOLE ALGHORITHM
	 * Function that nextState after move in specifed direction
	 */
	//virtual uint64_t getNextState(int rows, int cols, uint64_t currentState, char moveDirection)=0;
};

