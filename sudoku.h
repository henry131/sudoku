#ifndef SUDOKU_H
#define SUDOKU_H

//Constant and Type Declarations

/*None*/

//Function Declarations

/*LOADS A SUDOKU BOARD FROM filename INTO THE ARRAY board*/
void load_board(const char *filename, char board[9][9]);

/*DISPLAYS ON SCREEN A FORMATTED SUDOKU BOARD FROM ARRAY board*/
void display_board(const char board[9][9]);

/*TRUE ONLY IF ALL BOARD POSITIONS WITHIN board ARE OCCUPIED BY DIGITS*/
bool is_complete(const char board[9][9]);

/*PUTS digit IN position ON board IF THE PROPOSED MOVE IS VALID*/
bool make_move(const char *position,char digit, char board[9][9]);

/*OUPUTS THE 2-D CHARACTER ARRAY board TO A FILE WITH NAME filename*/
bool save_board (const char *filename, char board[9][9]);

/*UPDATES board WITH SOLUTION TO SUDOKU PROBLEM, RETURNS FALSE IF UNABLE*/
bool solve_board (char board[9][9]);

/*UPDATES board WITH SOLUTION TO SUDOKU PROBLEM, RETURNS FALSE IF UNABLE*/
/*KEEPS COUNT OF HOW MANY TIMES FUNCTION IS CALLED RECURSIVELY IN counter*/
bool solve_board_with_counter (char board[9][9], int& counter);

#endif
