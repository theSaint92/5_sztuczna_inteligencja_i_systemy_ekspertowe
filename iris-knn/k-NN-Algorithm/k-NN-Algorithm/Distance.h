#pragma once

class Distance
{
public:
	virtual double dist(const unsigned int &dimension, double point1[], double point2[]) = 0;
};

