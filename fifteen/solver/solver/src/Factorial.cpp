#include "Factorial.h"

/*
 * Constructor - adding values of n! to n-th place of values.
 */
Factorial::Factorial()
{
	//Creating list of first 20 elements of n! seq (bigger are too big for uint64_t)
	uint64_t current = 1;
	this->values.push_back(1);
	for (int i = 1; i < 21; i++) {
		current *= i;
		this->values.push_back(current);
	}
}

/*
 * Function getting value of n!
 * usage: Factorial::getInstance().get(i)
 * range : 0 - 20 
 *		bigger are too big for uint64_t
 */
uint64_t Factorial::get(int number)
{
	if (number < 0) throw std::invalid_argument("received negative value");
	else if (number >= 21) throw std::invalid_argument("Too big argument (max 20)");
	else return this->values[number];
}

/*
 * Becouse its singleton
 */
Factorial& Factorial::getInstance()
{
	static Factorial instance;
	return instance;
}