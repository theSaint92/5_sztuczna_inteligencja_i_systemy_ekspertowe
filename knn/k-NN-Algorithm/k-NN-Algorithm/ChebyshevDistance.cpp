#include "ChebyshevDistance.h"

double ChebyshevDistance::dist(const unsigned int &dimension, double point1[], double point2[])
{
	double distance = 0;
	double temp = 0;
	for (unsigned int i = 0; i<dimension; i++) {
		//Do we need to include cmath for abs()? no...
		temp = point1[i] - point2[i];
		if (temp < 0) temp = -temp;
		if (distance < temp) distance = temp;
	}
	return distance;
}

