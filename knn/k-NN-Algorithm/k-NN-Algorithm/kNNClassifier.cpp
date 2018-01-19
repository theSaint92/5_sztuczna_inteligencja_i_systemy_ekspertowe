#include "kNNClassifier.h"
#include "EuclideanDistance.h"
#include "InstanceDist.h"
#include <set>

kNNClassifier::kNNClassifier() 
{
	this->distance = new EuclideanDistance();
	this->numOfNeighbours = 5;
}

kNNClassifier::~kNNClassifier()
{
	delete this->distance;
}

void kNNClassifier::classify(Instance &instance)
{
	std::multiset<InstanceDist> sorted;
	
	for (Instance i : this->data) {
		InstanceDist current;
		current.inst = i;
		current.distance = this->distance->dist(instance.getAttributes().size(), &i.getAttributes()[0], &instance.getAttributes()[0]);
		sorted.insert(current);
	}


}

void kNNClassifier::build(const std::vector<Instance> &data)
{
	this->data = data;
}

void kNNClassifier::setNumOfNeighbours(int k)
{
	this->numOfNeighbours = k;
}

void kNNClassifier::setDistanceMetrics(Distance* distance)
{
	this->distance = distance;
}
