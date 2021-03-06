#pragma once
#include "Distance.h"

/**
	Realizujemy odległość Euklidesową
*/

class EuclideanDistance :
	public Distance
{
public:
	double dist(const unsigned int &dimension, double point1[], double point2[]);
};

