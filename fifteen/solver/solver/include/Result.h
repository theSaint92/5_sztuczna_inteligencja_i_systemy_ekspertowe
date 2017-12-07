#pragma once
#include <string>

struct Result {
	//Setting default values in constructor
	Result() : steps(-1), seqOfMoves("") {}

	//Elements
	int64_t steps;
	std::string seqOfMoves;
};