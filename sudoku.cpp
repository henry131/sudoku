#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char *filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in)
    cout << "Failed!" << endl;
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << endl;
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3))
    cout << "  +===========+===========+===========+" << endl;
  else
    cout << "  +---+---+---+---+---+---+---+---+---+" << endl;
}

/* internal helper function */
void print_row(const char *data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << endl;
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) 
    cout << (char) ('1'+r) << "   ";
  cout << endl;
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/* add your functions here */

/*function to check if all board positions are occupied by digits*/
bool is_complete (const char board[9][9]) {
	for (int r = 0; r < 9; r++){
		for (int c = 0; c < 9; c++){
			if (!isdigit(board[r][c]))
				return false; 
		}
	} 
	return true;
}

/*helper function to check input coordinates are in board range*/
bool coords_in_range (int pos_row, int pos_col) {
	if (pos_row < 0 || pos_row > 8)
		return false; //Check input row is between A and I inclusive
	if (pos_col < 0 || pos_col > 8)
		return false; //Check input column is between 1 and 9 inclusive
	return true;
}

/*helper function check input is valid with regard to existing input*/
bool position_valid (int pos_row, int pos_col, char digit, char board[9][9]) {
	for (int column = 0; column < 9; column++){
		if (board[pos_row][column] == digit)  
			return false;  //Check no existing number in row
	}
	for (int row = 0; row < 9; row++){
		if (board[row][pos_col] == digit)  
			return false;  //Check no existing number in column
	}
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			if (board[((pos_row / 3)*3)+i][((pos_col / 3)*3)+j] == digit)
				return false;  //Check no exisitng number in 3x3
		}
	} 
	return true;
}

/*Function that updates board with proposed move if it is valid*/
bool make_move (const char *position, char digit, char board[9][9]) {
	int pos_row = (int) toupper( position[0] ) - 65;
	int pos_col = (int) position[1] - 49;
	if (position[2] != '\0')
		return false; //Check row/column inputs are single digit
	if (digit < 49 || digit > 57)  
		return false; //Check digit input is valid
	if (!coords_in_range(pos_row, pos_col))  
		return false; //Check intended input coordinates within board range
	if (!position_valid(pos_row, pos_col, digit, board))
		return false; //Check input is logically valid
	board[pos_row][pos_col] = digit;
	return true; //Input is valid: change board and return true
}

/*Outputs the 2-D character array board to file called filename*/
bool save_board (const char *filename, char board[9][9]) {
	ofstream out_stream;
	out_stream.open(filename);
	if (out_stream.fail())
		return false;
	for (int i=0; i<9; i++){
		for (int j=0; j<9; j++){
			out_stream.put(board[i][j]);
		}
		out_stream.put('\n');
	}
	out_stream.close();
	return true;
}

/*Updates sudoku grid in board with solution, returns false if fails*/
bool solve_board (char board[9][9]) {
	int row = 0;
	int column = 0;
	//Cycle through columns then rows looking for non-digit square
	while (row < 9 && board[row][column] != '.') {
		column ++;
		if (column == 9) {
			row++;
			column = 0;
		}
	}
	if (row == 9) //Base Case: found no non-digit squares, complete
		return true;
	//Convert row and column to char *position for make_move function
	char *position;
	position = new char[3];
	position[0] = (char)row + 65;
	position[1] = (char)column + 49;
	position[2] = '\0';
	//Cycle through numbers and check input valid
	//Recurse until no valid move or base case is reached
	for (char i='1'; i<='9'; i++) {
		if (make_move(position,i,board) && solve_board(board)){
			return true;
		}
	}
	delete [] position;
	board[row][column] = '.';
	return false;
}

/*Updates sudoku grid in board with solution, returns false if fails*/
/*Increases value of counter by 1 each time function is run*/
bool solve_board_with_counter (char board[9][9], int& counter){
	counter++; //Counter to monitor repetitions of function
	int row = 0;
	int column = 0;
	while (row < 9 && board[row][column] != '.') {
		column ++;
		if (column == 9) {
			row++;
			column = 0;
		}
	}
	if (row == 9)
		return true;
	char *position;
	position = new char[3];
	position[0] = (char)row + 65;
	position[1] = (char)column + 49;
	position[2] = '\0';
	for (char i='1'; i<='9'; i++) {
		if (make_move(position,i,board) 
				&& solve_board_with_counter(board,counter)){
			return true;
		}
	}
	delete [] position;
	board[row][column] = '.';
	return false;
}
