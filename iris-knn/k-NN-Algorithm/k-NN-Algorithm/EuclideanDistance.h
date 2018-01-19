#pragma once
#include "Distance.h"

/**
	Realizujemy odleg³oœæ Euklidesow¹
*/

class EuclideanDistance :
	public Distance
{
public:
	double dist(const unsigned int &dimension, double point1[], double point2[]);
};

