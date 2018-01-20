#pragma once
#include "Instance.h"

#include <sstream>
#include <iomanip>

struct InstanceDist {

	double distance;
	Instance inst;

	bool operator<(InstanceDist other) const
	{
		return distance < other.distance;
	}

	std::string toString() 
	{
		std::stringstream ss;
		ss << "Distance: " << std::setw(7) << std::setprecision(5) << distance << " ";
		ss << inst.toString();
		return ss.str();
	}


};