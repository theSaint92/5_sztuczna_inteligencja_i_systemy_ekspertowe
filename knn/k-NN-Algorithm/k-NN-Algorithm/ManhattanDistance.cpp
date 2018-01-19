#include "ManhattanDistance.h"

double ManhattanDistance::dist(const unsigned int &dimension, double point1[], double point2[])
{
	double distance = 0;
	double temp = 0;
	for (unsigned int i=0; i<dimension; i++) {
		//Do we need to include cmath for abs()? no...
		temp = point1[i] - point2[i];
		if (temp > 0) distance += temp;
		else distance -= temp;
	}
	return distance;
}
