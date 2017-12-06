#include "FactorialTransformer.h"
#include "Factorial.h"

uint64_t FactorialTransformer::getState(std::vector<int> values)
{
	uint64_t result = 0;
	size_t size = values.size();
	for (int i = 0; i < size; i++) {
		uint64_t factorial = Factorial::getInstance().get(size - i - 1);
		if(values[i] != 0) result += factorial * countSmallerThan(values[i],values);
		else result += factorial * (size-1-i);
		values[i] = 0;
	}
	return result;
}

std::vector<int> FactorialTransformer::getVector(int size,uint64_t state)
{
	std::vector<int> result;
	std::vector<int> calculated_fields;
	for (int i = 0; i < size; i++) {
		calculated_fields.push_back(i+1);
	}
	int num, field;
	for (int i = 0; i < size; i++) {
		num = state / Factorial::getInstance().get(size - i -1);
		state -= num*Factorial::getInstance().get(size - i -1);
		if (calculated_fields[num] == size) {
			field = 0;
		}
		else {
			field = calculated_fields[num];
		}
		calculated_fields.erase(calculated_fields.begin() + num);
		result.push_back(field);
	}
	return result;
}

int FactorialTransformer::countSmallerThan(int number, const std::vector<int> &values)
{
	int result = 0;
	for (int element : values) {
		if (element < number && element) result++;
	}	
	return result;
}

//uint64_t FactorialTransformer::getNextState(int rows,int cols, uint64_t currentState, char moveDirection)
//{
//	bool possible = 1;
//	//Checking if move is possible at all
//	//TODO
//	if (!possible) return -1; /*uint64_t -1 is basicly 0xffffffffffffffff so it's impossbile state to achive in any board*/
//	uint64_t result = 0;
//
//	return result;
//}