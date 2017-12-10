#pragma once

#include "Board.h"
#include "Factorial.h"
#include <math.h>
#include <Heuristic.h>

//For Manhattan
int boardRows = 0;
int boardCols = 0;
std::vector<int> rightRows;
std::vector<int> rightCols;

int manhattan(uint64_t const &state) {
	//Current board
	Board currentStateBoard(Board::rows, Board::cols, (char)0);
	currentStateBoard.getFromState(state);
	std::vector<int> vec = currentStateBoard.getValues();
	
	int size = Board::rows*Board::cols;
	//Did Soled board parameters changed?
	if (Board::rows != boardRows || Board::cols != boardCols) {
		boardRows = Board::rows;
		boardCols = Board::cols;

		std::vector<int> solvedSeq;
		for (int i = 1; i < size; i++) solvedSeq.push_back(i);
		solvedSeq.push_back(0);

		rightRows.resize(size);
		rightCols.resize(size);

		for (int i = 0; i < size; i++) {
			rightRows[solvedSeq[i]] = i / Board::cols + 1;
			rightCols[solvedSeq[i]] = i % Board::cols + 1;
		}
	}
	
	std::vector<int> thisRows(size);
	std::vector<int> thisCols(size);
	//std::vector<int> distance(size);
	int distance;
	
	for (int i = 0; i < size; i++) {
		thisRows[vec[i]] = i / Board::cols + 1;
		thisCols[vec[i]] = i % Board::cols + 1;
	}

	for (int i = 0; i < size; i++) {
		//distance[i] = abs(thisRows[i] - rightRows[i]) + abs(thisCols[i] - rightCols[i]);
		distance += abs(thisRows[i] - rightRows[i]) + abs(thisCols[i] - rightCols[i]);

	}

	//std::cerr << currentStateBoard.toString() << std::endl;
	//std::cerr << "ROWS: " << Board::rows << " COLS: " << Board::cols << " SIZE: " << size << std::endl;
	//std::cerr << "   rRow\trCol\tthisRow\tthisCol\tsize\n";
	//for (int i = 0; i < size; i++) {
	//	std::cerr << i << ": ";
	//	std::cerr << rightRows[i] << "\t";
	//	std::cerr << rightCols[i] << "\t";
	//		 
	//	std::cerr << thisRows[i] << "\t";
	//	std::cerr << thisCols[i] << "\t";
	//	std::cerr << distance[i] << "\t";
	//	std::cerr << std::endl;
	//}
	//throw std::exception("JUST NEED TO CHECK IT");
	return distance;
}

uint64_t scoreTileRightPlace(uint64_t const &state) {
	//Current board
	uint64_t result = 0;
	Board currentStateBoard(Board::rows, Board::cols, (char)0);
	currentStateBoard.getFromState(state);
	std::vector<int> values = currentStateBoard.getValues();

	for (unsigned int i = 0; i < values.size()-1; i++) {
		if (values[i] == i + 1) {
			//result += Factorial::getInstance().get(values.size() - i);
			result++;
		}
		if (&values.end() == 0) result++;
	}
	return result;
}

struct Comparator {
	static int heuristic;
	virtual bool operator()(uint64_t const &u, uint64_t const &v) {
		if (heuristic==HEURISTIC::MANHATTAN) return manhattan(u) > manhattan(v);
		else if (heuristic==HEURISTIC::TILEONPLACE) return scoreTileRightPlace(u) < scoreTileRightPlace(v);
		return u > v;
	}

	static void setHeuristic(int newHeuristic) {
		Comparator::heuristic = newHeuristic;
	}
};

int Comparator::heuristic = 1;


//struct Comparator {
//	virtual bool operator()(uint64_t const &u, uint64_t const &v) = 0;
//};
//
//
//struct VertexComparator : public Comparator {
//  bool operator()(uint64_t const &u, uint64_t const &v) {
//    return u < v;
//  }
//};
//
//struct ManhattanComparator : public Comparator {
//	bool operator()(uint64_t const &u, uint64_t const &v) {
//		return manhattan(u) > manhattan(v);
//	}
//};
//
//struct TileOnPlaceComparator : public Comparator {
//	bool operator()(uint64_t const &u, uint64_t const &v) {
//		return scoreTileRightPlace(u) < scoreTileRightPlace(v);
//	}
//};






