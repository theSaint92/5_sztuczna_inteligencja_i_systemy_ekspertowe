#include "kNNClassifier.h"
#include "EuclideanDistance.h"
#include "InstanceDist.h"
#include "InstanceOccurence.h"
#include <set>
#include <iostream>
#include <utility>      // pair
#include <algorithm>	// sort

kNNClassifier::kNNClassifier() 
{
	//this->distance = new EuclideanDistance();
	this->numOfNeighbours = 5;
}

kNNClassifier::~kNNClassifier()
{
	//delete this->distance;
}

std::string kNNClassifier::classify(std::vector<double> insAt)
{
	// mulitset nie jest jednak optymalny - lepiej zrobic vector i zwykly sort - my bad :(
	std::multiset<InstanceDist> sorted;
	
	for (Instance i : this->data) {
		InstanceDist current;
		current.inst = i;
		current.distance = this->distance->dist(insAt.size(), &i.getAttributes()[0], &insAt[0]);
		sorted.insert(current);
	}

	//Choose the class pointed by nearest neighbours
	std::vector< InstanceOccurence > classList;
	
	int i = 0;
	for (InstanceDist insd : sorted) 
	{
		if (i < this->numOfNeighbours) {
			// classList is non-empty
			bool found = false;
			for (InstanceOccurence &currentClass : classList) {
				if (currentClass.instanceClass == insd.inst.getClass())
				{
					currentClass.occurences += 1;
					/* We dont have to check this becouse data is already sorted by distance*/
					//if (insd.distance < currentClass.lowestDistance)
					//	currentClass.lowestDistance = insd.distance;
					found = true;
					break;
				}
			}
			if (!found) {
				InstanceOccurence newOccurence;
				newOccurence.instanceClass = insd.inst.getClass();
				newOccurence.occurences = 1;
				newOccurence.lowestDistance = insd.distance;
				classList.push_back(newOccurence);
			}
			i++;
		}
		else break;
	}
	//Picking lowest element (Most elements, if even least distance)
	InstanceOccurence lowest = *std::min_element(classList.begin(), classList.end());

	return lowest.instanceClass;

	//Testing
	//for (InstanceDist i : sorted) 
	//{
	//	std::cout << i.toString() << std::endl;
	//}
	//for (InstanceOccurence i : classList)
	//{
	//	std::cout << i.toString() << std::endl;
	//}
	//std::cout << "LOWEST OCCURENCE: " << lowest.toString() << std::endl;
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
