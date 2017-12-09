// fifteen.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <ctime>        // std::time
#include <cstdlib>		// std::rand, std::srand
#include "Board.h"
#include "Factorial.h"
#include "Result.h"

using namespace std;

enum ALGORITHM {
	BFS,
	DFS,
	ASTAR
};

enum HEURISTIC {
	FIRST,
	SECOND
};


int main(int argc, char* argv[])
{
	/*
	 * Picking how program works (some rework might happen here)
	 */
	int method = ALGORITHM::BFS;
	char* order = "PDLG";
	bool verbose = false;
	char* heuristic = "1";
	char* transformMethod = "hex";

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
				heuristic = argv[i + 1];
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
		else if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
			cout << "USAGE: solver.exe [ -h ] [-b [order] | -d [order] | -n [number] ] [ -t hex|fac ] [ -v ] \n";
			cout << "\tWHERE:\n";
			cout << "\t-h\t--help     \tPrint this menu\n";
			cout << "\t-b\t--bfs      \tSets BFS search alghorithm (default)\n";
			cout << "\t-d\t--dfs      \tSets DFS search alghorithm\n";
			cout << "\t  \torder      \tPermutation of LDPG or R(random) specifing search order\n";
			cout << "\t-n\t--nn       \tSets Astar search alghorithm\n";
			cout << "\t  \tnumber     \tHeuristic function id\n";
			cout << "\t-t\t--transform\tState transform mode hexadecimal or factorial\n";
			cout << "\t  \thex        \tHexadecimal transform method (default)\n";
			cout << "\t  \tfac        \tFactorial transform method\n";
			cout << "\t-v\t--verbose  \tPrints more info in output (needed for graphic part)\n";
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
		int boardSize = rows*cols;
		for (int i = 0; i < boardSize; i++) {
			int temp;
			cin >> temp;
			boardVector.push_back(temp);
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
		Board board(rows, cols, boardVector);

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
		if (method == BFS) {
			res = board.solveWithBFS(order);
		}
		else if (method == DFS) {
			res = board.solveWithDFS(order);
		}
		else if (method == ASTAR) {
			res = board.solveWithAStar(heuristic);
		}
		clock_t end = clock();
		if (verbose) cout << rows << " " << cols << endl << board.toString();
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
				cout << "AStar " << heuristic << endl;
			}
			cout << res.visitedStates << endl << end - begin << "ms" << endl;
		}


	} catch (const std::exception &e) {
		cerr << e.what();
		return 0;
	}


	//vector<int> unsolvable3{ 2,3,1,4,8,5,0,6,7 };
	//vector<int> almostSolved3{ 1,2,3,4,5,6,7,0,8 };
	//vector<int> simple4x4{ 5, 1, 2, 4, 9, 0, 3, 8, 10, 6, 7, 12, 13, 14, 11, 15 };
	//
	//Board* dwanadwa = new Board(2, 2);
	//Board* trzynatrzy = new Board(3, 3);
	//Board* czterynacztery = new Board(2,2);

	//cout << (hex) << UINTMAX_MAX << " " << 0xFFFFFFFFFFFFFFFF << endl;
	//for (int i = 0; i < 17; i++) {
	//	cout << i << "! = " << Factorial::getInstance().get(i) << endl;
	//}


	//FactorialTransformer fac;
	//Board::changeTransformer(fac);
	
	//cout << "BOARD:\n" << czterynacztery->toString() << endl;
	//uint64_t transformed = czterynacztery->transformToState();
	//cout << "State form: " << transformed << endl;
	//czterynacztery->getFromState(transformed);
	//cout << "After takeing from transformed form:\n" << czterynacztery->toString() << endl;

	/*
	 * Speed test between transformation methods
	 */
	//clock_t begin = clock();
	//for (int i = 1; i < 10000; i++) {
	//	board = new Board(4, 4);
	//	uint64_t transformed = board->transformToState();
	//	board->getFromState(transformed);
	//}
	//clock_t end = clock();
	//std::cout << "Wykonano w " << end - begin << " clocks\n";
	//
	//Board::changeTransformer(fac);
	//begin = clock();
	//for (int i = 1; i < 10000; i++) {
	//	board = new Board(4, 4);
	//	uint64_t transformed = board->transformToState();
	//	board->getFromState(transformed);
	//}
	//end = clock();
	//std::cout << "Wykonano w " << end - begin << " clocks\n";

	/*
	 * Testing of moveFreeTile method
	 */
	//for (int i = 1; i < 20; i++) {
	//	Board *board = new Board(2, 3);
	//	cout << "BOARD:\n" << board->toString() << endl;
	//	cout << "Logical result: " << board->moveFreeTile('D') << endl;
	//	cout << "BOARD AFTER:\n" << (dec) << board->toString() << endl;
	//	cout << "//////////////////////////////\n";
	//}

	/*

	* Testing BFS
	*/

	//clock_t begin = clock();

	//clock_t end = clock();
	//std::cout << "Wykonano w " << end - begin << " clocks\n";

	//try {
	//	cout << czterynacztery->toString() << endl;
	//	
	//	clock_t avarageTime = 0;
	//	for (int i = 0; i < 5; i++) {
	//		clock_t begin = clock();
	//		Result res = czterynacztery->solveWithBFS(order);
	//		clock_t end = clock();
	//
	//		cout << res.steps << endl << res.seqOfMoves << endl;
	//
	//		std::cout << "Wykonano w " << end - begin << " clocks\n";
	//		avarageTime += end;
	//		avarageTime -= begin;
	//	}
	//	std::cout << "srednio " << avarageTime/5 << " clocks\n";
	//
	//
	//}
	//
	//catch (const std::invalid_argument& e) {
	//	// Code that executes when an exception of type  
	//	// networkIOException is thrown in the try block  
	//	// ...  
	//	// Log error message in the exception object  
	//
	//	cerr << "ERROR: " << e.what();
	//}
	//catch (const std::domain_error& e) {
	//	// Code that handles another exception type  
	//	// ...  
	//	cerr << "ERROR: " << e.what();
	//}
	//catch (const std::out_of_range& e) {
	//	// Code that handles another exception type  
	//	// ...  
	//	cerr << "ERROR: " << e.what();
	//}
	//catch (const std::exception& e) {
	//	cerr << "ERROR: " << e.what();
	//}

	//delete dwanadwa;
	//delete trzynatrzy;
	//delete czterynacztery;

	return 0;
}

