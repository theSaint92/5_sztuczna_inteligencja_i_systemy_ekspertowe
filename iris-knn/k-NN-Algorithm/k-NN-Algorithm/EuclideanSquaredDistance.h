#pragma once
#include "Distance.h"

/**
	Odleg³oœæ Euklidesowa podniesiona do kwadratu. Pozwala
	na przyœpieszene obliczeñ (Korzystaj¹cz tej klasy nie 
	musimy pierwiastkowaæ w funkcji dist).
*/

class EuclideanSquaredDistance :
	public Distance
{
public:
	double dist(const unsigned int &dimension, double point1[], double point2[]);
};