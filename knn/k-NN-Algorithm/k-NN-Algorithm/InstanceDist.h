#pragma once
#include "Instance.h"

struct InstanceDist {

	double distance;
	Instance inst;

	bool operator<(InstanceDist other) const
	{
		return distance > other.distance;
	}

};