#pragma once
#include "Distance.h"

/**
	Odleg�o�� Minkowskiego to generalizacja odleg�o�ci Euklidesowej i Manhattan.
	Definicje odnajdziemy na https://en.wikipedia.org/wiki/Minkowski_distance .
	Warto zauwa�y� �e dla warto�ci p = 1 odleg�o�� Minkowskiego odpowiada odle-
	g�o�ci Manhattan, a dla p = 2 odleg�o�ci Euklidesowej. 
*/

class MinkowskiDistance :
	public Distance
{
public:

	double p;
	MinkowskiDistance();
	MinkowskiDistance(double p);
	double dist(const unsigned int &dimension, double point1[], double point2[]);
	
};

