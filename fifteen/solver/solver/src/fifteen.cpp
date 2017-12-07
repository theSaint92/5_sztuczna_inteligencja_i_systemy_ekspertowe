// fifteen.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include "Board.h"
#include "Factorial.h"
#include "Result.h"

using namespace std;


int main(int argc, char* argv[])
{
	std::srand(unsigned(std::time(0)));

	HexaTransformer hexa;
	Board::changeTransformer(hexa);
	vector<int> unsolvable3{ 2,3,1,4,8,5,0,6,7 };
	vector<int> almostSolved3{ 1,2,3,4,5,6,0,7,8 };

	Board* dwanadwa = new Board(2, 2);
	Board* trzynatrzy = new Board(3, 3);
	Board* czterynacztery = new Board(3,3, almostSolved3);

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

	try {
		cout << czterynacztery->toString() << endl;
		
		clock_t avarageTime = 0;
		for (int i = 0; i < 5; i++) {
			clock_t begin = clock();
			Result res = czterynacztery->solveWithDFS("LGPD");
			clock_t end = clock();

			cout << res.steps << endl << res.seqOfMoves << endl;

			std::cout << "Wykonano w " << end - begin << " clocks\n";
			avarageTime += end;
			avarageTime -= begin;
		}
		std::cout << "srednio " << avarageTime/5 << " clocks\n";


	}
	
	catch (const std::invalid_argument& e) {
		// Code that executes when an exception of type  
		// networkIOException is thrown in the try block  
		// ...  
		// Log error message in the exception object  
	
		cerr << "ERROR: " << e.what();
	}
	catch (const std::domain_error& e) {
		// Code that handles another exception type  
		// ...  
		cerr << "ERROR: " << e.what();
	}
	catch (const std::out_of_range& e) {
		// Code that handles another exception type  
		// ...  
		cerr << "ERROR: " << e.what();
	}
	catch (const std::exception& e) {
		cerr << "ERROR: " << e.what();
	}





	delete dwanadwa;
	delete trzynatrzy;
	delete czterynacztery;

	return 0;
}

