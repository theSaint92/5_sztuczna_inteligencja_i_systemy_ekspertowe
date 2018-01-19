#pragma once
#include "Distance.h"

/**
	Realizujemy odleg�o�� Manhattan
*/

class ManhattanDistance :
	public Distance
{
public:
	double dist(const unsigned int &dimension, double point1[], double point2[]);
};

