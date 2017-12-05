#pragma once

#include "Transformer.h"
#include "HexaTransformer.h"
#include "FactorialTransformer.h"
#include "Result.h"
#include <vector>
#include <string>
#include <memory>

class Board
{
private:
	static Transformer* transformer;
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
	static void changeTransformer(Transformer &transformer);
	bool moveFreeTile(char moveDirection);

	//Solving methods
	Result solveWithBFS(std::string order);
	Result solveWithDFS(std::string order);
	Result solveWithHeuristic();
};

