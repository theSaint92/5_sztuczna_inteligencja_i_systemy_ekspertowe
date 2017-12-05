#include "Board.h"
#include <vector>
#include <algorithm> //random_shuffle
#include <sstream> //toString()
#include <string> //toString()

Transformer* Board::transformer = NULL;

Board::Board()
{
	this->rows = 4;
	this->cols = 4;
	// generete some random state of the puzzle using built-in random generator:
	for (int i = 0; i < 16; i++) this->values.push_back(i);
	std::random_shuffle(this->values.begin(), this->values.end());
}

Board::Board(int rows, int cols)
{
	if (rows*cols > 16 || rows*cols <= 0) throw std::invalid_argument("rows*cols must be in range (1...16)");
	this->rows = rows;
	this->cols = cols;
	// generete some random state of the puzzle using built-in random generator:
	int size = this->rows*this->cols;
	for (int i = 0; i < size; i++) this->values.push_back(i);
	std::random_shuffle(this->values.begin(), this->values.end());
}

Board::Board(int rows, int cols, std::vector<int> values)
{
	if (rows*cols > 16 || rows*cols <= 0) throw std::invalid_argument("rows*cols must be in range (1...16)");
	if (rows*cols != values.size()) throw std::invalid_argument("rows*cols must be equal to values vector size");
	this->rows = rows;
	this->cols = cols;
	this->values = values;
}

uint64_t Board::transformToState()
{
	if( transformer == NULL ) throw std::domain_error("Transformer is not defined!");
	return this->transformer->getState(this->values);
}

void Board::getFromState(uint64_t state)
{
	if (transformer == NULL) throw std::domain_error("Transformer is not defined!");
	this->values = this->transformer->getVector(this->rows*this->cols, state);
}

std::string Board::toString()
{
	std::ostringstream oss;

	if (!this->values.empty())
	{
		int size = this->values.size();
		
		for (int i = 0; i < size; i++) {
			oss << this->values[i] << "\t";
			if ((i+1)%this->cols == 0) oss << "\n";
		}
	}

	return oss.str();
}

void Board::changeTransformer(Transformer &newTransformer)
{
	transformer = &newTransformer;
}

bool Board::moveFreeTile(char moveDirection)
{
	//Getting position of 0 element
	int zeroPosition = -1;
	for (unsigned int i = 0; i < this->values.size(); i++)
	{
		if (!values[i])
		{
			zeroPosition = i;
			break;
		}
	}
	if (zeroPosition == -1) throw std::domain_error("Board doesn't have 0 element?!");

	if (moveDirection == 'L') {
		//We can't left if 0 element is in first column
		if (!(zeroPosition%rows)) return false;
		else std::swap(this->values[zeroPosition], this->values[zeroPosition-1]);
	}
	else if (moveDirection == 'P') {
		//We can't right if 0 element is in last column
		if (!((zeroPosition+1)%rows)) return false;
		else std::swap(this->values[zeroPosition], this->values[zeroPosition + 1]);
	}
	else if (moveDirection == 'G') {
		//We can't up if 0 element is in first row
		if (zeroPosition<this->cols) return false;
		else std::swap(this->values[zeroPosition], this->values[zeroPosition - this->cols]);
	}
	else if (moveDirection == 'D') {
		//We can't down if 0 element is in last row
		if (zeroPosition>(this->cols*this->rows-this->rows-1)) return false;
		else std::swap(this->values[zeroPosition], this->values[zeroPosition + this->cols]);
	}
	else return false;
	return true;
}

Result Board::solveWithBFS(std::string order) 
{
	Result result;

	return result;
}

Result Board::solveWithDFS(std::string order)
{
	Result result;

	return result;

}

Result Board::solveWithHeuristic()
{
	Result result;

	return result;
}
