#pragma once
#include <sstream>

struct InstanceOccurence {

	std::string instanceClass;
	int occurences;
	double lowestDistance;

	bool operator<(InstanceOccurence other) const
	{
		if (occurences == other.occurences)
			return lowestDistance < other.lowestDistance;
		else
			return occurences > other.occurences;
	}

	std::string toString()
	{
		std::stringstream ss;
		ss << "Class: " << instanceClass;
		ss << " Occurences: " << occurences;
		ss << " LowestDistance: " << lowestDistance;
		return ss.str();
	}
};