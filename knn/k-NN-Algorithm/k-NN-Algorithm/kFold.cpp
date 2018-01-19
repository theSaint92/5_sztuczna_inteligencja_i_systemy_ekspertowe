#include "kFold.h"
#include <algorithm>

//Sort function for InstanceClass (by class name)
struct compareStruct
{
	inline bool operator() (Instance& ins1, Instance& ins2)
	{
		return (ins1.getClass() < ins2.getClass());
	}
};

void kFold::createFolds(std::vector<Instance> vec, int numOfFolds)
{
	//We sort it so after its easier to distribute it even between folds
	std::sort(vec.begin(), vec.end(), compareStruct());
	
	//Creating array for folds
	std::vector< std::vector<Instance> > folds;
	std::vector<Instance> empty;
	for (int i = 0; i < numOfFolds; i++)
	{
		folds.push_back(empty);
	}

	//Now push even number of elements to each array
	unsigned int size = vec.size();
	for (unsigned int i = 0; i < size; i++)
	{
		folds[i%numOfFolds].push_back(vec[i]);
	}
	this->folds = folds;
}

std::vector<Instance> kFold::getKFold(int k)
{
	return this->folds[k];
}

std::vector<Instance> kFold::getAllButKFold(int k)
{
	int size = 0;
	std::vector<Instance> result;
	
	for (std::vector<Instance> i : this->folds)
	{
		size += i.size();
	}
	size -= folds[k].size();

	result.reserve(size);

	int foldsLength = this->folds.size();
	for (int i = 0; i < foldsLength; i++) {
		if (i != k) {
			result.insert(result.end(), this->folds[i].begin(), this->folds[i].end());
		}
	}
	return result;
}

unsigned int kFold::getSize() {
	return this->folds.size();
}


