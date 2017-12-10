#pragma once
#include <string>

struct Result {
	//Setting default values in constructor
	Result() : steps(0), seqOfMoves(""), visitedStates(0){}

	//Elements
	int64_t steps;
	std::string seqOfMoves;
	uint64_t visitedStates;
};