// fifteen.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <ctime>        // std::time
#include <cstdlib>		// std::rand, std::srand
#include "Board.h"
#include "Factorial.h"
#include "Result.h"
#include "Heuristic.h"

using namespace std;

enum ALGORITHM {
	BFS,
	DFS,
	ASTAR
};

int main(int argc, char* argv[])
{
	/*
	 * Picking how program works (some rework might happen here)
	 */
	int method = ALGORITHM::BFS;
	char* order = "PDLG";
	bool verbose = false;
	int heuristic = HEURISTIC::MANHATTAN;
	char* transformMethod = "hex";
	bool randomState = false;
	bool latex = false;

	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "--bfs") == 0 || strcmp(argv[i], "-b") == 0) {
			method = ALGORITHM::BFS;
			if (i < argc - 1) {
				order = argv[i + 1];
				i++;
			}
		}
		else if (strcmp(argv[i], "--dfs") == 0 || strcmp(argv[i], "-d") == 0) {
			method = ALGORITHM::DFS;
			if (i < argc - 1) {
				order = argv[i + 1];
				i++;
			}
		}
		else if (strcmp(argv[i], "--nn") == 0 || strcmp(argv[i], "-n") == 0) {
			method = ALGORITHM::ASTAR;
			if (i < argc - 1) {
				string h = argv[i + 1];
				heuristic = std::stoi(h);
				i++;
			}
		}
		else if (strcmp(argv[i], "--transform") == 0 || strcmp(argv[i], "-t") == 0) {
			if (i < argc - 1) {
				if (strcmp(argv[i + 1], "hex") == 0 || strcmp(argv[i + 1], "fac") == 0) {
					transformMethod = argv[i + 1];
				}
				else {
					cerr << "Invalid argument! Write --help/-h to get help";
					return 0;
				}
				i++;
			}
		}
		else if (strcmp(argv[i], "--verbose") == 0 || strcmp(argv[i], "-v") == 0) {
			verbose = true;
		}
		else if (strcmp(argv[i], "--verbose") == 0 || strcmp(argv[i], "-v") == 0) {
			verbose = true;
		}
		else if (strcmp(argv[i], "--random") == 0 || strcmp(argv[i], "-r") == 0) {
			randomState = true;
		}
		else if (strcmp(argv[i], "--latex") == 0 || strcmp(argv[i], "-l") == 0) {
			latex = true;
		}
		else if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
			std::cout << "USAGE: solver.exe [ -h ] [-b [order] | -d [order] | -n [number] ] [ -t hex|fac ] [ -v ] \n";
			std::cout << "\tWHERE:\n";
			std::cout << "\t-h\t--help     \tPrint this menu\n";
			std::cout << "\t-b\t--bfs      \tSets BFS search alghorithm (default)\n";
			std::cout << "\t-d\t--dfs      \tSets DFS search alghorithm\n";
			std::cout << "\t  \torder      \tPermutation of LDPG or R(random) specifing search order\n";
			std::cout << "\t-n\t--nn       \tSets Astar search alghorithm\n";
			std::cout << "\t  \tnumber     \tHeuristic function id (1 is manhattan, 2 is tileOnPlace)\n";
			std::cout << "\t-t\t--transform\tState transform mode hexadecimal or factorial\n";
			std::cout << "\t  \thex        \tHexadecimal transform method (default)\n";
			std::cout << "\t  \tfac        \tFactorial transform method\n";
			std::cout << "\t-v\t--verbose  \tPrints more info in output (needed for graphic part)\n";
			std::cout << "\t-r\t--random   \tAnalyze random puzzle (just need to pass size)\n";
			std::cout << "\t-l\t--latex    \tOutput form in latex (Doesn't print unsolvables)\n";
			return 0;
		}
		else {
			cerr << "Invalid argument! Write --help/-h to get help";
			return 0;
		}
	}
	//std::cout << "Method: " << method << " ,order: " << order << " ,verbose: " << verbose << " ,heuristic: " << heuristic << " ,transform: " << transformMethod << endl;
	
	
	/*
	 * Time to pickup data;
	 */
	vector<int> boardVector;
	int rows;
	int cols;

	try {
		cin >> rows;
		cin >> cols;
		if (!randomState) {
			int boardSize = rows*cols;
			for (int i = 0; i < boardSize; i++) {
				int temp;
				cin >> temp;
				boardVector.push_back(temp);
			}
		}
	}
	catch (const std::exception &e) {
		cerr << e.what();
		return 0;
	}


	/*
	 * Got the data
	 * Start the algorithm
	 */
	try {
		//Start random
		std::srand(unsigned(std::time(0)));

		//Declare board
		Board* board;
		if (randomState) board = new Board(rows,cols);
		else board = new Board(rows, cols, boardVector);

		//Setting transformer
		FactorialTransformer fac;
		HexaTransformer hexa;
		if (!strcmp(transformMethod, "hex")) {
			Board::changeTransformer(hexa);
		}
		else if (!strcmp(transformMethod, "fac")) {
			Board::changeTransformer(fac);
		}
		else { //Just to be sure i didnt miss something
			Board::changeTransformer(hexa);
		}
		
		//Solving
		Result res;
		clock_t begin = clock();
		if (board->isSolvable()) {
			if (method == BFS) {
				res = board->solveWithBFS(order);
			}
			else if (method == DFS) {
				res = board->solveWithDFS(order);
			}
			else if (method == ASTAR) {
				res = board->solveWithAStar(heuristic);
			}
		} 
		else {
			res.steps = -1;
		}
		clock_t end = clock();
		if (latex && res.steps != -1) {
			//\hline
			//	$rows \times cols$ & dlugosc_sciezka & odwiedzone_stany & czas_rozwiazania
			std::cout << "\t\\hline\n\t\t$";
			std::cout << rows << " \\times " << cols << "$ & ";
			std::cout << res.steps << " & " << res.visitedStates << " & " << end - begin << "ms \\\\\n";
		}
		if (!latex) {
			if (verbose) cout << rows << " " << cols << endl << board->toString();
			cout << res.steps << endl;
			if (res.steps != -1) cout << res.seqOfMoves << endl;
			if (verbose) {
				if (method == BFS) {
					cout << "BFS " << order << endl;
				}
				else if (method == DFS) {
					cout << "DFS " << order << endl;
				}
				else if (method == ASTAR) {
					cout << "AStar ";
					if (heuristic == HEURISTIC::MANHATTAN) {
						cout << "Manhattan" << endl;
					}
					else if (heuristic == HEURISTIC::TILEONPLACE) {
						cout << "Tile on place" << endl;
					}
				}
				cout << res.visitedStates << endl << end - begin << "ms" << endl;
			}
		}

	} catch (const std::exception &e) {
		cerr << e.what();
		if (latex) {
			//\hline
			//	$rows \times cols$ & dlugosc_sciezka & odwiedzone_stany & czas_rozwiazania
			std::cout << "\t\\hline\n\t\t$";
			std::cout << rows << " \\times " << cols << "$ & ";
			std::cout << "Nie Osiagnieto & POBIERZ &\\sim 75&s \\\\\n";
		}
		return 0;
	}

	return 0;
}

