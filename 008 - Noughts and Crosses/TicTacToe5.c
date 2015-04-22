// Thomas Moffet, thomasmoffet, z5061905
// F09C, Joseph Harris
// 19/03/2015
// This program plays Tic Tac Toe on a 5x5 grid.

// THIS PROGRAM USES NICK ROBSON'S UNIFIED COLOUR HEADER!
// BEFORE YOU COMPILE, MAKE SURE THAT colours.h IS IN THE SAME FOLDER!
// https://gist.githubusercontent.com/nickrobson/ace0f9de4c18c801dc13/raw/d8955c775332ab69245ccdf085f7c92eb19fa557/colours.h

/*
The goal of Tic Tac Toe 5 is to get four of a similar shape in a row.
Each player takes alternating turns to try and get three in a row.

This program firstly asks whether O or X will go first.
Then, each turn, the board is drawn.
The player will then be asked what space they want to go in.
The program checks if they can go there. If they can't, it asks again.
Then the program checks if anyone has won yet. If not, turns swap.
If someone has won, the board is drawn once, and the game ends.
*/

#include <stdio.h>
#include <stdlib.h>
#include "colours.h"

int turnDecide ();
int gameTime (int);
void boardDraw (int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int);
int turnInput ();
int gameWinCheck (int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int);
int fourInARowCheck (int, int, int, int, int);
void winningMessage (int);

int main (int argc, char *argv[]) {
	
	// Firstly, turnOrder is defined as 1 if O goes first, or 2 if X.
	int turnOrder = turnDecide();
	
	// Now it's time to play the game.
	gameTime (turnOrder);
	
	// At the very end, this message shows.
	printf("Thanks for playing!\n");
	
	return EXIT_SUCCESS;
}

int turnDecide () {
	
	// A character will be defined to compute what the user typed.
	char getChar;
	printf("Who will go first? ");
	
	// This while loop ensures they type something compatible.
	while (getChar != 'o' || getChar != 'O' || getChar != 'x' || getChar != 'X') {
		printf("Type O or X. ");
		scanf("%c", &getChar);
		
		// Then, the program figures out what they typed.
		if (getChar == 'o' || getChar == 'O') {
			return 1;
		}
		else if (getChar == 'x' || getChar == 'X') {
			return 2;
		}
	}
	
	return EXIT_SUCCESS;
}

int gameTime (int turnOrder) {
	
	// The values of each cell are defined.
	// They are arranged from bottom-left, across and up each row.
	int cell1 = 0;
	int cell2 = 0;
	int cell3 = 0;
	int cell4 = 0;
	int cell5 = 0;
	int cell6 = 0;
	int cell7 = 0;
	int cell8 = 0;
	int cell9 = 0;
	int cell10 = 0;
	int cell11 = 0;
	int cell12 = 0;
	int cell13 = 0;
	int cell14 = 0;
	int cell15 = 0;
	int cell16 = 0;
	int cell17 = 0;
	int cell18 = 0;
	int cell19 = 0;
	int cell20 = 0;
	int cell21 = 0;
	int cell22 = 0;
	int cell23 = 0;
	int cell24 = 0;
	int cell25 = 0;
	
	// These are some values to detect how far through the game it is.
	int whoseTurn = turnOrder; // 1 is O is first, 2 if X is first.
	int currentTurn = 1;       // Counts up from 1, stops game at 10.
	int gameWon = 0;           // 1 if O wins, 2 if X wins.
	
	// This value detects what cell the user wants to input.
	int inputCell = 0;
	int validInput = 0;
	
	while (currentTurn <= 25 && gameWon == 0) {
		// The boardDraw function is called, and uses the 9 cell values.
		boardDraw (cell1, cell2, cell3, cell4, cell5, cell6, cell7, cell8, cell9, cell10, cell11, cell12, cell13, cell14, cell15, cell16, cell17, cell18, cell19, cell20, cell21, cell22, cell23, cell24, cell25);
		
		// The game will say whose turn it is.
		if (whoseTurn == 1) {
			printf("It's O's turn!\n");
		}
		else if (whoseTurn == 2) {
			printf("It's X's turn!\n");
		}
		
		while (validInput == 0) {
			// The turnInput function determines what cell the user wants.
			inputCell = turnInput ();
			
			// Then a calculation happens to insert the value.
			// It checks what cell they input, then if it's filled,
			// it asks agains. If it isn't, then it proceeds.
			if (inputCell == 1) {
				if (cell1 != 0) {
					printf("That cell is already filled.\n");
				}
				else {
					cell1 = whoseTurn;
					validInput = 1;
				}
			}
			else if (inputCell == 2) {
				if (cell2 != 0) {
					printf("That cell is already filled.\n");
				}
				else {
					cell2 = whoseTurn;
					validInput = 1;
				}
			}
			else if (inputCell == 3) {
				if (cell3 != 0) {
					printf("That cell is already filled.\n");
				}
				else {
					cell3 = whoseTurn;
					validInput = 1;
				}
			}
			else if (inputCell == 4) {
				if (cell4 != 0) {
					printf("That cell is already filled.\n");
				}
				else {
					cell4 = whoseTurn;
					validInput = 1;
				}
			}
			else if (inputCell == 5) {
				if (cell5 != 0) {
					printf("That cell is already filled.\n");
				}
				else {
					cell5 = whoseTurn;
					validInput = 1;
				}
			}
			else if (inputCell == 6) {
				if (cell6 != 0) {
					printf("That cell is already filled.\n");
				}
				else {
					cell6 = whoseTurn;
					validInput = 1;
				}
			}
			else if (inputCell == 7) {
				if (cell7 != 0) {
					printf("That cell is already filled.\n");
				}
				else {
					cell7 = whoseTurn;
					validInput = 1;
				}
			}
			else if (inputCell == 8) {
				if (cell8 != 0) {
					printf("That cell is already filled.\n");
				}
				else {
					cell8 = whoseTurn;
					validInput = 1;
				}
			}
			else if (inputCell == 9) {
				if (cell9 != 0) {
					printf("That cell is already filled.\n");
				}
				else {
					cell9 = whoseTurn;
					validInput = 1;
				}
			}
			else if (inputCell == 10) {
				if (cell10 != 0) {
					printf("That cell is already filled.\n");
				}
				else {
					cell10 = whoseTurn;
					validInput = 1;
				}
			}
			else if (inputCell == 11) {
				if (cell11 != 0) {
					printf("That cell is already filled.\n");
				}
				else {
					cell11 = whoseTurn;
					validInput = 1;
				}
			}
			else if (inputCell == 12) {
				if (cell12 != 0) {
					printf("That cell is already filled.\n");
				}
				else {
					cell12 = whoseTurn;
					validInput = 1;
				}
			}
			else if (inputCell == 13) {
				if (cell13 != 0) {
					printf("That cell is already filled.\n");
				}
				else {
					cell13 = whoseTurn;
					validInput = 1;
				}
			}
			else if (inputCell == 14) {
				if (cell14 != 0) {
					printf("That cell is already filled.\n");
				}
				else {
					cell14 = whoseTurn;
					validInput = 1;
				}
			}
			else if (inputCell == 15) {
				if (cell15 != 0) {
					printf("That cell is already filled.\n");
				}
				else {
					cell15 = whoseTurn;
					validInput = 1;
				}
			}
			else if (inputCell == 16) {
				if (cell16 != 0) {
					printf("That cell is already filled.\n");
				}
				else {
					cell16 = whoseTurn;
					validInput = 1;
				}
			}
			else if (inputCell == 17) {
				if (cell17 != 0) {
					printf("That cell is already filled.\n");
				}
				else {
					cell17 = whoseTurn;
					validInput = 1;
				}
			}
			else if (inputCell == 18) {
				if (cell18 != 0) {
					printf("That cell is already filled.\n");
				}
				else {
					cell18 = whoseTurn;
					validInput = 1;
				}
			}
			else if (inputCell == 19) {
				if (cell19 != 0) {
					printf("That cell is already filled.\n");
				}
				else {
					cell19 = whoseTurn;
					validInput = 1;
				}
			}
			else if (inputCell == 20) {
				if (cell20 != 0) {
					printf("That cell is already filled.\n");
				}
				else {
					cell20 = whoseTurn;
					validInput = 1;
				}
			}
			else if (inputCell == 21) {
				if (cell21 != 0) {
					printf("That cell is already filled.\n");
				}
				else {
					cell21 = whoseTurn;
					validInput = 1;
				}
			}
			else if (inputCell == 22) {
				if (cell22 != 0) {
					printf("That cell is already filled.\n");
				}
				else {
					cell22 = whoseTurn;
					validInput = 1;
				}
			}
			else if (inputCell == 23) {
				if (cell23 != 0) {
					printf("That cell is already filled.\n");
				}
				else {
					cell23 = whoseTurn;
					validInput = 1;
				}
			}
			else if (inputCell == 24) {
				if (cell24 != 0) {
					printf("That cell is already filled.\n");
				}
				else {
					cell24 = whoseTurn;
					validInput = 1;
				}
			}
			else if (inputCell == 25) {
				if (cell25 != 0) {
					printf("That cell is already filled.\n");
				}
				else {
					cell25 = whoseTurn;
					validInput = 1;
				}
			}
		}
		
		// This resets that value for the next turn.
		validInput = 0;
		
		// The game checks to see if a player has won.
		gameWon = gameWinCheck (cell1, cell2, cell3, cell4, cell5, cell6, cell7, cell8, cell9, cell10, cell11, cell12, cell13, cell14, cell15, cell16, cell17, cell18, cell19, cell20, cell21, cell22, cell23, cell24, cell25, whoseTurn);
		
		// Finally, to end the turn, the currentTurn moves up by 1, and the turns swap.
		if (whoseTurn == 1) {
			whoseTurn = 2;
		}
		else if (whoseTurn == 2) {
			whoseTurn = 1;
		}
		
		currentTurn++;
	}
	
	// At the end, the board is drawn for the final time.
	boardDraw (cell1, cell2, cell3, cell4, cell5, cell6, cell7, cell8, cell9, cell10, cell11, cell12, cell13, cell14, cell15, cell16, cell17, cell18, cell19, cell20, cell21, cell22, cell23, cell24, cell25);
	
	// And the winner is declared.
	winningMessage (gameWon);
	
	return EXIT_SUCCESS;
}

void boardDraw (int cell1, int cell2, int cell3, int cell4, int cell5, int cell6, int cell7, int cell8, int cell9, int cell10, int cell11, int cell12, int cell13, int cell14, int cell15, int cell16, int cell17, int cell18, int cell19, int cell20, int cell21, int cell22, int cell23, int cell24, int cell25) {
	
	// This tells colours.h to come up.
	SETUP
	
	// Some variables are called to monitor where the board drawing is at.
	int row = 0;
	int col = 0;
	
	// This just makes a bit of space for the board.
	printf("\n\n");
	
	// When all the rows are done, this while will end.
	while (row < 9) {
		
		// When all the columns are done in a row, this while will end.
		while (col < 9) {
			
			// This if is for drawing the + in the middle of the lines.
			if ((row == 1 || row == 3 || row == 5 || row == 7) && (col == 1 || col == 3 || col == 5 || col == 7)) {
				printf("+");
			}
			// This if is for drawing the vertical lines.
			else if (col == 1 || col == 3 || col == 5 || col == 7) {
				printf("|");
			}
			// This if is for drawing the horizontal lines.
			else if (row == 1 || row == 3 || row == 5 || row == 7) {
				printf("-");
			}
			
			// This is for drawing the current game layout.
			// These are in groups of three for each horizontal row.
			// The SET_FG things change the colour based on colours.h.
			// RESET changes it back.
			
			if (row == 0 && col == 0) {
				if (cell21 == 0) {
					SET_FG_DARKGRAY printf("U");
				}
				else if (cell21 == 1) {
					SET_FG_BLUE printf("O");
				}
				else if (cell21 == 2) {
					SET_FG_RED printf("X");
				}
				RESET
			}
			if (row == 0 && col == 2) {
				if (cell22 == 0) {
					SET_FG_DARKGRAY printf("V");
				}
				else if (cell22 == 1) {
					SET_FG_BLUE printf("O");
				}
				else if (cell22 == 2) {
					SET_FG_RED printf("X");
				}
				RESET
			}
			if (row == 0 && col == 4) {
				if (cell23 == 0) {
					SET_FG_DARKGRAY printf("W");
				}
				else if (cell23 == 1) {
					SET_FG_BLUE printf("O");
				}
				else if (cell23 == 2) {
					SET_FG_RED printf("X");
				}
				RESET
			}
			if (row == 0 && col == 6) {
				if (cell24 == 0) {
					SET_FG_DARKGRAY printf("X");
				}
				else if (cell24 == 1) {
					SET_FG_BLUE printf("O");
				}
				else if (cell24 == 2) {
					SET_FG_RED printf("X");
				}
				RESET
			}
			if (row == 0 && col == 8) {
				if (cell25 == 0) {
					SET_FG_DARKGRAY printf("Y");
				}
				else if (cell25 == 1) {
					SET_FG_BLUE printf("O");
				}
				else if (cell25 == 2) {
					SET_FG_RED printf("X");
				}
				RESET
			}
			
			if (row == 2 && col == 0) {
				if (cell16 == 0) {
					SET_FG_DARKGRAY printf("P");
				}
				else if (cell16 == 1) {
					SET_FG_BLUE printf("O");
				}
				else if (cell16 == 2) {
					SET_FG_RED printf("X");
				}
				RESET
			}
			if (row == 2 && col == 2) {
				if (cell17 == 0) {
					SET_FG_DARKGRAY printf("Q");
				}
				else if (cell17 == 1) {
					SET_FG_BLUE printf("O");
				}
				else if (cell17 == 2) {
					SET_FG_RED printf("X");
				}
				RESET
			}
			if (row == 2 && col == 4) {
				if (cell18 == 0) {
					SET_FG_DARKGRAY printf("R");
				}
				else if (cell18 == 1) {
					SET_FG_BLUE printf("O");
				}
				else if (cell18 == 2) {
					SET_FG_RED printf("X");
				}
				RESET
			}
			if (row == 2 && col == 6) {
				if (cell19 == 0) {
					SET_FG_DARKGRAY printf("S");
				}
				else if (cell19 == 1) {
					SET_FG_BLUE printf("O");
				}
				else if (cell19 == 2) {
					SET_FG_RED printf("X");
				}
				RESET
			}
			if (row == 2 && col == 8) {
				if (cell20 == 0) {
					SET_FG_DARKGRAY printf("T");
				}
				else if (cell20 == 1) {
					SET_FG_BLUE printf("O");
				}
				else if (cell20 == 2) {
					SET_FG_RED printf("X");
				}
				RESET
			}
			
			if (row == 4 && col == 0) {
				if (cell11 == 0) {
					SET_FG_DARKGRAY printf("K");
				}
				else if (cell11 == 1) {
					SET_FG_BLUE printf("O");
				}
				else if (cell11 == 2) {
					SET_FG_RED printf("X");
				}
				RESET
			}
			if (row == 4 && col == 2) {
				if (cell12 == 0) {
					SET_FG_DARKGRAY printf("L");
				}
				else if (cell12 == 1) {
					SET_FG_BLUE printf("O");
				}
				else if (cell12 == 2) {
					SET_FG_RED printf("X");
				}
				RESET
			}
			if (row == 4 && col == 4) {
				if (cell13 == 0) {
					SET_FG_DARKGRAY printf("M");
				}
				else if (cell13 == 1) {
					SET_FG_BLUE printf("O");
				}
				else if (cell13 == 2) {
					SET_FG_RED printf("X");
				}
				RESET
			}
			if (row == 4 && col == 6) {
				if (cell14 == 0) {
					SET_FG_DARKGRAY printf("N");
				}
				else if (cell14 == 1) {
					SET_FG_BLUE printf("O");
				}
				else if (cell14 == 2) {
					SET_FG_RED printf("X");
				}
				RESET
			}
			if (row == 4 && col == 8) {
				if (cell15 == 0) {
					SET_FG_DARKGRAY printf("O");
				}
				else if (cell15 == 1) {
					SET_FG_BLUE printf("O");
				}
				else if (cell15 == 2) {
					SET_FG_RED printf("X");
				}
				RESET
			}
			
			if (row == 6 && col == 0) {
				if (cell6 == 0) {
					SET_FG_DARKGRAY printf("F");
				}
				else if (cell6 == 1) {
					SET_FG_BLUE printf("O");
				}
				else if (cell6 == 2) {
					SET_FG_RED printf("X");
				}
				RESET
			}
			if (row == 6 && col == 2) {
				if (cell7 == 0) {
					SET_FG_DARKGRAY printf("G");
				}
				else if (cell7 == 1) {
					SET_FG_BLUE printf("O");
				}
				else if (cell7 == 2) {
					SET_FG_RED printf("X");
				}
				RESET
			}
			if (row == 6 && col == 4) {
				if (cell8 == 0) {
					SET_FG_DARKGRAY printf("H");
				}
				else if (cell8 == 1) {
					SET_FG_BLUE printf("O");
				}
				else if (cell8 == 2) {
					SET_FG_RED printf("X");
				}
				RESET
			}
			if (row == 6 && col == 6) {
				if (cell9 == 0) {
					SET_FG_DARKGRAY printf("I");
				}
				else if (cell9 == 1) {
					SET_FG_BLUE printf("O");
				}
				else if (cell9 == 2) {
					SET_FG_RED printf("X");
				}
				RESET
			}
			if (row == 6 && col == 8) {
				if (cell10 == 0) {
					SET_FG_DARKGRAY printf("J");
				}
				else if (cell10 == 1) {
					SET_FG_BLUE printf("O");
				}
				else if (cell10 == 2) {
					SET_FG_RED printf("X");
				}
				RESET
			}
			
			if (row == 8 && col == 0) {
				if (cell1 == 0) {
					SET_FG_DARKGRAY printf("A");
				}
				else if (cell1 == 1) {
					SET_FG_BLUE printf("O");
				}
				else if (cell1 == 2) {
					SET_FG_RED printf("X");
				}
				RESET
			}
			if (row == 8 && col == 2) {
				if (cell2 == 0) {
					SET_FG_DARKGRAY printf("B");
				}
				else if (cell2 == 1) {
					SET_FG_BLUE printf("O");
				}
				else if (cell2 == 2) {
					SET_FG_RED printf("X");
				}
				RESET
			}
			if (row == 8 && col == 4) {
				if (cell3 == 0) {
					SET_FG_DARKGRAY printf("C");
				}
				else if (cell3 == 1) {
					SET_FG_BLUE printf("O");
				}
				else if (cell3 == 2) {
					SET_FG_RED printf("X");
				}
				RESET
			}
			if (row == 8 && col == 6) {
				if (cell4 == 0) {
					SET_FG_DARKGRAY printf("D");
				}
				else if (cell4 == 1) {
					SET_FG_BLUE printf("O");
				}
				else if (cell4 == 2) {
					SET_FG_RED printf("X");
				}
				RESET
			}
			if (row == 8 && col == 8) {
				if (cell5 == 0) {
					SET_FG_DARKGRAY printf("E");
				}
				else if (cell5 == 1) {
					SET_FG_BLUE printf("O");
				}
				else if (cell5 == 2) {
					SET_FG_RED printf("X");
				}
				RESET
			}
			
			// If it's at the end of a line, it newlines.
			if (col == 8) {
				printf("\n");
			}
			
			// After all of that, it ups the column number.
			col++;
		}
		
		// At the end of a row, it resets the column and moves to the
		// next line.
		col = 0;
		row++;
	}
	
	// Some more line breaks for neatness.
	printf("\n\n");
}

int turnInput () {
	int inputValue;
	char inputCell;
	char extraInput;
	
	printf("What cell do you want to enter?\n");
	
	while (inputCell < 'A' || (inputCell > 'Y' && inputCell < 'a') || inputCell > 'y') {
		printf("(Enter the cell's corresponding letter.) ");
		inputCell = getchar();
		
		// I Googled this line, it nullifies any extra characters6
		// that are input. It's not clean, so I'm not encouraging that.
		// http://stackoverflow.com/questions/21234262/turbo-c-scanf-to-only-accept-one-character
		while( (extraInput = getchar()) != '\n' && extraInput != EOF);
	}
	
	if (inputCell >= 'A' && inputCell <= 'Y') {
		inputValue = inputCell - 64;
	}
	if (inputCell >= 'a' && inputCell <= 'y') {
		inputValue = inputCell - 96;
	}
	
	return inputValue;
}

int gameWinCheck (int cell1, int cell2, int cell3, int cell4, int cell5, int cell6, int cell7, int cell8, int cell9, int cell10, int cell11, int cell12, int cell13, int cell14, int cell15, int cell16, int cell17, int cell18, int cell19, int cell20, int cell21, int cell22, int cell23, int cell24, int cell25, int whoseTurn) {
	
	int gameWon = 0;
	
	//printf("%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", cell1, cell2, cell3, cell4, cell5, cell6, cell7, cell8, cell9, cell10, cell11, cell12, cell13, cell14, cell15, cell16, cell17, cell18, cell19, cell20, cell21, cell22, cell23, cell24, cell25);

	// Horizontal wins
	if ((cell1 == cell2) && (cell1 == cell3) && (cell1 == cell4) && (gameWon == 0)) {
		//printf("1 2 3 4\n");
		gameWon = fourInARowCheck (cell1, cell2, cell3, cell4, whoseTurn);
	}
	if ((cell2 == cell3) && (cell2 == cell4) && (cell2 == cell5) && (gameWon == 0)) {
		//printf("2 3 4 5\n");
		gameWon = fourInARowCheck (cell2, cell3, cell4, cell5, whoseTurn);
	}
	if ((cell6 == cell7) && (cell6 == cell8) && (cell6 == cell9) && (gameWon == 0)) {
		//printf("6 7 8 9\n");
		gameWon = fourInARowCheck (cell6, cell7, cell8, cell9, whoseTurn);
	}
	if ((cell7 == cell8) && (cell7 == cell9) && (cell7 == cell10) && (gameWon == 0)) {
		//printf("7 8 9 10\n");
		gameWon = fourInARowCheck (cell7, cell8, cell9, cell10, whoseTurn);
	}
	if ((cell11 == cell12) && (cell11 == cell13) && (cell11 == cell14) && (gameWon == 0)) {
		//printf("11 12 13 14\n");
		gameWon = fourInARowCheck (cell11, cell12, cell13, cell14, whoseTurn);
	}
	if ((cell2 == cell13) && (cell12 == cell14) && (cell12 == cell15) && (gameWon == 0)) {
		//printf("12 13 14 15\n");
		gameWon = fourInARowCheck (cell12, cell13, cell14, cell15, whoseTurn);
	}
	if ((cell16 == cell17) && (cell16 == cell18) && (cell16 == cell19) && (gameWon == 0)) {
		//printf("16 17 18 19\n");
		gameWon = fourInARowCheck (cell16, cell17, cell18, cell19, whoseTurn);
	}
	if ((cell17 == cell18) && (cell17 == cell19) && (cell17 == cell20) && (gameWon == 0)) {
		//printf("17 18 19 20\n");
		gameWon = fourInARowCheck (cell17, cell18, cell19, cell20, whoseTurn);
	}
	if ((cell21 == cell22) && (cell21 == cell23) && (cell21 == cell24) && (gameWon == 0)) {
		//printf("21 22 23 24\n");
		gameWon = fourInARowCheck (cell21, cell22, cell23, cell24, whoseTurn);
	}
	if ((cell22 == cell23) && (cell22 == cell24) && (cell22 == cell25) && (gameWon == 0)) {
		//printf("22 23 24 25\n");
		gameWon = fourInARowCheck (cell22, cell23, cell24, cell25, whoseTurn);
	}
	
	// Vertical wins
	if ((cell1 == cell6) && (cell1 == cell11) && (cell1 == cell16) && (gameWon == 0)) {
		//printf("1 6 11 16\n");
		gameWon = fourInARowCheck (cell1, cell6, cell11, cell16, whoseTurn);
	}
	if ((cell6 == cell11) && (cell6 == cell16) && (cell6 == cell21) && (gameWon == 0)) {
		//printf("6 11 16 21\n");
		gameWon = fourInARowCheck (cell6, cell11, cell16, cell21, whoseTurn);
	}
	if ((cell2 == cell7) && (cell2 == cell12) && (cell2 == cell17) && (gameWon == 0)) {
		//printf("2 7 12 17\n");
		gameWon = fourInARowCheck (cell2, cell7, cell12, cell17, whoseTurn);
	}
	if ((cell7 == cell12) && (cell7 == cell17) && (cell7 == cell2) && (gameWon == 0)) {
		//printf("7 12 17 22\n");
		gameWon = fourInARowCheck (cell2, cell12, cell17, cell22, whoseTurn);
	}
	if ((cell3 == cell8) && (cell3 == cell13) && (cell3 == cell18) && (gameWon == 0)) {
		//printf("3 8 13 18\n");
		gameWon = fourInARowCheck (cell3, cell8, cell13, cell18, whoseTurn);
	}
	if ((cell8 == cell13) && (cell8 == cell18) && (cell8 == cell23) && (gameWon == 0)) {
		//printf("8 13 18 23\n");
		gameWon = fourInARowCheck (cell8, cell13, cell18, cell23, whoseTurn);
	}
	if ((cell4 == cell9) && (cell4 == cell14) && (cell4 == cell19) && (gameWon == 0)) {
		//printf("4 9 14 19\n");
		gameWon = fourInARowCheck (cell4, cell9, cell14, cell19, whoseTurn);
	}
	if ((cell9 == cell14) && (cell9 == cell19) && (cell9 == cell24) && (gameWon == 0)) {
		//printf("9 14 19 24\n");
		gameWon = fourInARowCheck (cell9, cell14, cell19, cell24, whoseTurn);
	}
	if ((cell5 == cell10) && (cell5 == cell15) && (cell5 == cell20) && (gameWon == 0)) {
		//printf("5 10 15 20\n");
		gameWon = fourInARowCheck (cell5, cell10, cell15, cell20, whoseTurn);
	}
	if ((cell10 == cell15) && (cell10 == cell20) && (cell10 == cell25) && (gameWon == 0)) {
		//printf("10 15 20 25\n");
		gameWon = fourInARowCheck (cell10, cell15, cell20, cell25, whoseTurn);
	}	
	
	// Diagonal wins
	if ((cell1 == cell7) && (cell1 == cell13) && (cell1 == cell19) && (gameWon == 0)) {
		//printf("1 7 13 19\n");
		gameWon = fourInARowCheck (cell1, cell7, cell13, cell19, whoseTurn);
	}
	if ((cell7 == cell13) && (cell7 == cell19) && (cell7 == cell25) && (gameWon == 0)) {
		//printf("7 13 19 25\n");
		gameWon = fourInARowCheck (cell7, cell13, cell19, cell25, whoseTurn);
	}
	if ((cell2 == cell8) && (cell2 == cell14) && (cell2 == cell20) && (gameWon == 0)) {
		//printf("2 8 14 20\n");
		gameWon = fourInARowCheck (cell2, cell8, cell14, cell20, whoseTurn);
	}
	if ((cell6 == cell12) && (cell6 == cell18) && (cell6 == cell24) && (gameWon == 0)) {
		//printf("6 12 18 24\n");
		gameWon = fourInARowCheck (cell6, cell12, cell18, cell24, whoseTurn);
	}
	if ((cell5 == cell9) && (cell5 == cell13) && (cell5 == cell17) && (gameWon == 0)) {
		//printf("5 9 13 17\n");
		gameWon = fourInARowCheck (cell5, cell9, cell13, cell17, whoseTurn);
	}
	if ((cell9 == cell13) && (cell9 == cell17) && (cell9 == cell21) && (gameWon == 0)) {
		//printf("9 13 17 21\n");
		gameWon = fourInARowCheck (cell9, cell13, cell17, cell21, whoseTurn);
	}
	if ((cell4 == cell8) && (cell4 == cell12) && (cell4 == cell16) && (gameWon == 0)) {
		//printf("4 8 12 16\n");
		gameWon = fourInARowCheck (cell4, cell8, cell12, cell16, whoseTurn);
	}
	if ((cell10 == cell14) && (cell10 == cell18) && (cell10 == cell22) && (gameWon == 0)) {
		//printf("10 14 18 22\n");
		gameWon = fourInARowCheck (cell10, cell14, cell18, cell22, whoseTurn);
	}
	
	return gameWon;
}

// This function checks if the three in a row isn't blank.
int fourInARowCheck (int check1, int check2, int check3, int check4, int whoseTurn) {
	int gameWon;
	
	// If any of the three cells are blank, don't win.
	if (check1 == 0 || check2 == 0 || check3 == 0 || check4 == 0) {
		//printf("THE GAME IS NOT WIN\n");
		gameWon = 0;
	}
	
	// If all the cells are filled (and thus are equal), win.
	else {
		//printf("THE GAME IS WIN\n");
		gameWon = whoseTurn;
	}
	return gameWon;
}

void winningMessage (int whoWon) {
	if (whoWon == 0) {
		printf("It's a draw!\n");
	}
	else if (whoWon == 1) {
		printf("O won!\n");
	}
	else if (whoWon == 2) {
		printf("X won!\n");
	}
}