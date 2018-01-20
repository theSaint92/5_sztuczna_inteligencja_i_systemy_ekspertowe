#pragma once
#include "Distance.h"

/**
	Odleg³oœæ Minkowskiego to generalizacja odleg³oœci Euklidesowej i Manhattan.
	Definicje odnajdziemy na https://en.wikipedia.org/wiki/Minkowski_distance .
	Warto zauwa¿yæ ¿e dla wartoœci p = 1 odleg³oœæ Minkowskiego odpowiada odle-
	g³oœci Manhattan, a dla p = 2 odleg³oœci Euklidesowej. 
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

