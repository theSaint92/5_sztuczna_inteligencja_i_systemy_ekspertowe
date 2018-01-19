#pragma once
#include "Distance.h"

/**
	Odleg�o�� Euklidesowa podniesiona do kwadratu. Pozwala
	na przy�pieszene oblicze� (Korzystaj�cz tej klasy nie 
	musimy pierwiastkowa� w funkcji dist).
*/

class EuclideanSquaredDistance :
	public Distance
{
public:
	double dist(const unsigned int &dimension, double point1[], double point2[]);
};