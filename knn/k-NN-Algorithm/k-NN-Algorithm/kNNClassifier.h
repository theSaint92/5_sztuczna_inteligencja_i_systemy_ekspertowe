#pragma once
#include "Classifier.h"
#include "Distance.h"

class kNNClassifier :
	public Classifier
{
	Distance* distance;
	std::vector<Instance> data;
	int numOfNeighbours;

public:
	kNNClassifier();
	~kNNClassifier();
	void classify(Instance &instance);
	void build(const std::vector<Instance> &data);
	void setNumOfNeighbours(int k);
	void setDistanceMetrics(Distance* distance);
};

