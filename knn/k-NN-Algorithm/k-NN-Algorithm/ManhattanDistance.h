#pragma once
#include "Distance.h"

/**
	Realizujemy odleg³oœæ Manhattan
*/

class ManhattanDistance :
	public Distance
{
public:
	double dist(const unsigned int &dimension, double point1[], double point2[]);
};

