#include <iostream>
#include <cstdio>
#include "sudoku.h"

using namespace std;

int main() {

	char board[9][9];

	/* This section illustrates the use of the pre-supplied helper functions. */
	cout << "============== Pre-supplied functions ==================" << endl << endl;

	cout << "Calling load_board():" << endl;
	load_board("easy.dat", board);

	cout << endl << "Displaying Sudoku board with display_board():" << endl;
	display_board(board);
	cout << "Done!" << endl << endl;

	cout << "====================== Question 1 ======================" << endl << endl;

	load_board("easy.dat", board);
	cout << "Board is ";
	if (!is_complete(board))
		cout << "NOT ";
	cout << "complete." << endl << endl;

	load_board("easy-solution.dat", board);
	cout << "Board is ";
	if (!is_complete(board))
		cout << "NOT ";
	cout << "complete." << endl << endl;


	cout << "====================== Question 2 ======================" << endl << endl;

	load_board("easy.dat", board);

	// Should be OK
	cout << "Putting '1' into I8 is ";
	if (!make_move("I8", '1', board)) 
		cout << "NOT ";
	cout << "a valid move. The board is:" << endl;
	display_board(board);

	// write more tests
	
	cout << "Putting '5' into J8 is ";
	if (!make_move("J8", '5', board)) 
		cout << "NOT ";
	cout << "a valid move. The board is:" << endl;
	display_board(board);
  
	cout << "Putting '2' into C2 is ";
	if (!make_move("C2", '2', board)) 
		cout << "NOT ";
	cout << "a valid move. The board is:" << endl;
	display_board(board);
  
	/* //Loop testing
	char position[3];
	char digit = '1';
	
	//Repeat testing coords_in_range function
	while (position[0] != 'n' && position[1] != 'n'){
		cout << "Test position (enter nn to exit test loop) : ";
		cin >> position;
		cout << "Putting " << digit << " into " << position << " is ";
		if (!make_move(position, digit, board)) 
			cout << "NOT ";
		cout << "a valid move." << endl;
	}

	//Repeat testing make_move function
	char answer = 'y';
	while (answer == 'y'){
		cout << "Input digit :";
		cin >> digit;
		cout << "into position :";
		cin >> position;
		cout << "Putting " << digit << " into " << position << " is ";
		if (!make_move(position, digit, board)) 
			cout << "NOT ";
		cout << "a valid move. The board is:" << endl;
		display_board(board);
		cout << "Test another?(y/n) :";
		cin >> answer;
	}	
	*/
	
	cout << "====================== Question 3 ======================" << endl << endl;
  
	load_board("easy.dat", board);
	if (save_board("easy-copy.dat", board))
		cout << "Save board to 'easy-copy.dat' successful." << endl;
	else
		cout << "Save board failed." << endl;
	cout << endl;

	cout << "====================== Question 4 ======================" << endl << endl;
	
	load_board("easy.dat", board);
	if (solve_board(board)) {
		cout << "The 'easy' board has a solution:" << endl;
		display_board(board);
	} else 
		cout << "A solution cannot be found." << endl;
	cout << endl;

	load_board("medium.dat", board);
	if (solve_board(board)) {
		cout << "The 'medium' board has a solution:" << endl;
		display_board(board);
	} else 
		cout << "A solution cannot be found." << endl;
	cout << endl;

	// write more tests
	
	/*Incorrect initial input test: wrong number added prior to solve*/
	load_board("easy.dat", board);
	cout << "Changing the value of easy board 'A1' from '.' to 5 (wrong)" << endl;
	board[0][0] = '5';
	if (solve_board(board)) {
		cout << "The solve_board function isnt working correctly" << endl;
		display_board(board);
	} else 
		cout << "A solution cannot be found for the tampered 'easy' board. Good." << endl;
	cout << endl;
	
	
	cout << "====================== Question 5 ======================" << endl << endl;

	// write more tests
	
	//Test for "mystery1": found solution
	load_board("mystery1.dat", board);
	if (solve_board(board)) {
		cout << "The 'mystery1' board has a solution:" << endl;
		display_board(board);
	} else 
		cout << "A solution cannot be found." << endl;
	cout << endl;
  
	//Test for "mystery2": no solution found
	load_board("mystery2.dat", board);
	if (solve_board(board)) {
		cout << "The 'mystery2' board has a solution:" << endl;
		display_board(board);
	} else 
		cout << "A solution cannot be found." << endl;
	cout << endl;
  
	//Test for "mystery3": found solution
	load_board("mystery3.dat", board);
	if (solve_board(board)) {
		cout << "The 'mystery3' board has a solution:" << endl;
		display_board(board);
	} else 
		cout << "A solution cannot be found." << endl;
	cout << endl;
  
	/*Further Testing: Using function with embedded counter*/
  
	int counter = 0;
  
	//easy: solve_board function runs 2172 times
	load_board("easy.dat", board);
	solve_board_with_counter(board,counter);
	cout << "For 'easy.dat', function ran " << counter << " times" << endl;
	cout << endl;
  
	//medium: solve_board function runs 15662 times
	counter = 0;
	load_board("medium.dat", board);
	solve_board_with_counter(board,counter);
	cout << "For 'medium.dat', function ran " << counter << " times" << endl;
	cout << endl;
	
	//mystery1: solve_board function runs 421547 times
	counter = 0;
	load_board("mystery1.dat", board);
	solve_board_with_counter(board,counter);
	cout << "For 'mystery1.dat', function ran " << counter << " times" << endl;
	cout << endl;
	
	//mystery3: solve_board function runs 14134 times
	counter = 0;
	load_board("mystery3.dat", board);
	solve_board_with_counter(board,counter);
	cout << "For 'mystery3.dat', function ran " << counter << " times" << endl;

	return 0;
}
