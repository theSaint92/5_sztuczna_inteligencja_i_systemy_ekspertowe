bool Board::isSolvable() {
	//Get permutation
	std::vector<int> permutation = this->values;
	//Get rid of 0 element (represents empty puzzle)
	int emptyPuzzleRow;
	for (int i = 0; i < permutation.size(); i++) {
		if (permutation[i] == 0) {
			permutation.erase(permutation.begin()+ i);
			//Getting row of empty puzzle
			emptyPuzzleRow = i / this->cols + 1;
			break;
		}
	}
	//Trivial case
	if (this->cols == 1 || this->rows == 1) {
		return std::is_sorted(permutation.begin(), 
			permutation.end());
	}
	//Getting inversions count
	int inversions = 0;
	for (int i = 0; i < permutation.size(); i++) {
		for (int j = i+1; j < permutation.size(); j++) {
			if (permutation[i] > permutation[j]) 
				inversions++;
		}
	}

	if (this->cols % 2 == 1 && inversions%2 == 0) { //Thrm 1
		return true;
	}
	if (this->cols %2 == 0) { //Theorem 2 and 3
		if ((this->rows - emptyPuzzleRow) % 2 == 
			0 && inversions % 2 == 0) return true;//2
		else if ((this->rows - emptyPuzzleRow) % 2 == 
			1 && inversions % 2 == 1) return true;//3
	}
	return false;
}