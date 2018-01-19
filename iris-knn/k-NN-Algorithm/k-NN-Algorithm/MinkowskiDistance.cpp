#include "MinkowskiDistance.h"
#include "cmath" //pow,abs

MinkowskiDistance::MinkowskiDistance() {
	this->p = 3;
}

MinkowskiDistance::MinkowskiDistance(unsigned int p) {
	this->p = p;
}

double MinkowskiDistance::dist(const unsigned int &dimension, double point1[], double point2[])
{
	double distance = 0;
	for (unsigned int i=0; i<dimension; i++) {
		distance += pow(abs(point1[i] - point2[i]), this->p);
	}
	distance = pow(distance, 1.0/this->p);
	return distance;
}
