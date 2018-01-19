#include "EuclideanDistance.h"
#include "cmath" //sqrt

double EuclideanDistance::dist(const unsigned int &dimension, double point1[], double point2[])
{
	double distance = 0;
	for (unsigned int i = 0; i<dimension; i++) {
		distance += (point1[i] - point2[i])*(point1[i] - point2[i]);
	}
	distance = sqrt(distance);
	return distance;
}
