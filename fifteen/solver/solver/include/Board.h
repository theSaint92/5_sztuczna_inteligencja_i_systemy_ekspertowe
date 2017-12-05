#pragma once

#include <Transformer.h>
#include <HexaTransformer.h>
#include <FactorialTransformer.h>
#include <vector>
#include <string>

class Board
{
private:
	Transformer* transformer;
	int rows;
	int cols;
	std::vector<int> values;

public:

	//Constructors
	Board();
	Board(int rows, int cols);
	Board(int rows, int cols, std::vector<int> values);

	~Board();

	//Getters
	int getRows();
	int getCols();
	std::vector<int> getValues();

	//Methods
	uint64_t transformToState();
	void getFromState(uint64_t state);
	std::string toString();
	void changeTransformer(std::string transformer);
};

