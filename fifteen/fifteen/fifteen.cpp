// fifteen.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include "Board.h"

using namespace std;


int main()
{
	std::srand(unsigned(std::time(0)));
	Board* board = new Board(3,3);
	cout << board->toString() << endl;
	int x = 0x11;
	cout << x << endl;
}

