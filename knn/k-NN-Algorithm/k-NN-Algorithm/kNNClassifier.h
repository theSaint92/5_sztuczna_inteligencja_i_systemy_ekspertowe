#pragma once
#include "Instance.h"
#include "Distance.h"

class kNNClassifier
{
	Distance* distance;
	std::vector<Instance> data;
	int numOfNeighbours;

public:
	kNNClassifier();
	~kNNClassifier();
	std::string kNNClassifier::classify(std::vector<double> insAt);
	void build(const std::vector<Instance> &data);
	void setNumOfNeighbours(int k);
	void setDistanceMetrics(Distance* distance);
};

