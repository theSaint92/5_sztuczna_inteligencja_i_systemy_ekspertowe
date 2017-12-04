#include "Board.h"
#include <vector>
#include <algorithm> //random_shuffle
#include <sstream> //toString()
#include <string> //toString()


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
	if (rows*cols > 20 || rows*cols <= 0) throw std::invalid_argument("rows*cols must be in range (1...20)");
	this->rows = rows;
	this->cols = cols;
	// generete some random state of the puzzle using built-in random generator:
	int size = this->rows*this->cols;
	for (int i = 0; i < size; i++) this->values.push_back(i);
	std::random_shuffle(this->values.begin(), this->values.end());
}

Board::Board(int rows, int cols, std::vector<int> values)
{
	if (rows*cols > 20 || rows*cols <= 0) throw std::invalid_argument("rows*cols must be in range (1...20)");
	if (rows*cols != values.size()) throw std::invalid_argument("rows*cols must be equal to values vector size");
	this->rows = rows;
	this->cols = cols;
	this->values = values;
}

Board::~Board()
{
}

uint64_t Board::transformToState()
{
	//TODO
	return 0;
}

void Board::getFromState(uint64_t state)
{
	//TODO
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