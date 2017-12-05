#include "HexaTransformer.h"

uint64_t HexaTransformer::getState(std::vector<int> values) 
{
	uint64_t result = 0x0;
	for (int element : values)
		result = (result << 4) | (element & 0xF);
	return result;
}
std::vector<int> HexaTransformer::getVector(int size, uint64_t state)
{
	std::vector<int> result;
	for (int i = 0; i < size; i++)
	{
		result.push_back(state & 0xF);
		state = (state >> 4);
	}	
	std::reverse(result.begin(), result.end());
	return result;
}
