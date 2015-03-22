// Thomas Moffet, thomasmoffet, z5061905
// F09C, Joseph Harris
// 19/03/2015
// This program plays Tic Tac Toe.

/*
The goal of Tic Tac Toe is to get three of a similar shape in a row.
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
#include <windows.h>

int turnDecide ();
int gameTime (int);
void boardDraw (int, int, int, int, int, int, int, int, int);
int turnInput ();
int gameWinCheck (int, int, int, int, int, int, int, int, int, int);
int threeInARowCheck (int, int, int, int);
void winningMessage (int);

int main (int argc, char *argv[]){
	
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
		if (getChar == 'o' || getChar == 'O'){
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
	// They are arranged like a keyboard's numpad.
	int cell1 = 0;
	int cell2 = 0;
	int cell3 = 0;
	int cell4 = 0;
	int cell5 = 0;
	int cell6 = 0;
	int cell7 = 0;
	int cell8 = 0;
	int cell9 = 0;
	
	// These are some values to detect how far through the game it is.
	int whoseTurn = turnOrder; // 1 is O is first, 2 if X is first.
	int currentTurn = 1;       // Counts up from 1, stops game at 10.
	int gameWon = 0;           // 1 if O wins, 2 if X wins.
	
	// This value detects what cell the user wants to input.
	int inputCell = 0;
	int validInput = 0;
	
	while (currentTurn <= 9 && gameWon == 0) {
		// The boardDraw function is called, and uses the 9 cell values.
		boardDraw (cell1, cell2, cell3, cell4, cell5, cell6, cell7, cell8, cell9);
		
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
			if (inputCell == 1){
				if (cell1 != 0){
					printf("That cell is already filled.\n");
				}
				else {
					cell1 = whoseTurn;
					validInput = 1;
				}
			}
			else if (inputCell == 2){
				if (cell2 != 0) {
					printf("That cell is already filled.\n");
				}
				else {
					cell2 = whoseTurn;
					validInput = 1;
				}
			}
			else if (inputCell == 3){
				if (cell3 != 0) {
					printf("That cell is already filled.\n");
				}
				else {
					cell3 = whoseTurn;
					validInput = 1;
				}
			}
			else if (inputCell == 4){
				if (cell4 != 0){
					printf("That cell is already filled.\n");
				}
				else {
					cell4 = whoseTurn;
					validInput = 1;
				}
			}
			else if (inputCell == 5){
				if (cell5 != 0){
					printf("That cell is already filled.\n");
				}
				else {
					cell5 = whoseTurn;
					validInput = 1;
				}
			}
			else if (inputCell == 6){
				if (cell6 != 0){
					printf("That cell is already filled.\n");
				}
				else {
					cell6 = whoseTurn;
					validInput = 1;
				}
			}
			else if (inputCell == 7){
				if (cell7 != 0){
					printf("That cell is already filled.\n");
				}
				else {
					cell7 = whoseTurn;
					validInput = 1;
				}
			}
			else if (inputCell == 8){
				if (cell8 != 0){
					printf("That cell is already filled.\n");
				}
				else {
					cell8 = whoseTurn;
					validInput = 1;
				}
			}
			else if (inputCell == 9){
				if (cell9 != 0){
					printf("That cell is already filled.\n");
				}
				else {
					cell9 = whoseTurn;
					validInput = 1;
				}
			}
		}
		
		// This resets that value for the next turn.
		validInput = 0;
		
		// The game checks to see if a player has won.
		gameWon = gameWinCheck (cell1, cell2, cell3, cell4, cell5, cell6, cell7, cell8, cell9, whoseTurn);
		
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
	boardDraw (cell1, cell2, cell3, cell4, cell5, cell6, cell7, cell8, cell9);
	
	// And the winner is declared.
	winningMessage (gameWon);
	
	return EXIT_SUCCESS;
}

void boardDraw (int cell1, int cell2, int cell3, int cell4, int cell5, int cell6, int cell7, int cell8, int cell9) {
	
	// This is something fancy so that Windows knows to change colours.
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	// Some variables are called to monitor where the board drawing is at.
	int row = 0;
	int col = 0;
	
	// This just makes a bit of space for the board.
	printf("\n\n");
	
	// When all the rows are done, this while will end.
	while (row < 5) {
		
		// When all the columns are done in a row, this while will end.
		while (col < 5) {
			
			// This if is for drawing the + in the middle of the lines.
			if ((row == 1 || row == 3) && (col == 1 || col == 3)) {
				printf("+");
			}
			// This if is for drawing the vertical lines.
			else if (col == 1 || col == 3) {
				printf("|");
			}
			// This if is for drawing the horizontal lines.
			else if (row == 1 || row == 3) {
				printf("-");
			}
			
			// This is for drawing the current game layout.
			if (row == 0 && col == 0) {
				if (cell7 == 0) {
					SetConsoleTextAttribute(hConsole, 8);
					printf("7");
					SetConsoleTextAttribute(hConsole, 7);
				}
				else if (cell7 == 1) {
					SetConsoleTextAttribute(hConsole, 9);
					printf("O");
					SetConsoleTextAttribute(hConsole, 7);
				}
				else if (cell7 == 2) {
					SetConsoleTextAttribute(hConsole, 12);
					printf("X");
					SetConsoleTextAttribute(hConsole, 7);
				}
			}
			if (row == 0 && col == 2) {
				if (cell8 == 0) {
					SetConsoleTextAttribute(hConsole, 8);
					printf("8");
					SetConsoleTextAttribute(hConsole, 7);
				}
				else if (cell8 == 1) {
					SetConsoleTextAttribute(hConsole, 9);
					printf("O");
					SetConsoleTextAttribute(hConsole, 7);
				}
				else if (cell8 == 2) {
					SetConsoleTextAttribute(hConsole, 12);
					printf("X");
					SetConsoleTextAttribute(hConsole, 7);
				}
			}
			if (row == 0 && col == 4) {
				if (cell9 == 0) {
					SetConsoleTextAttribute(hConsole, 8);
					printf("9");
					SetConsoleTextAttribute(hConsole, 7);
				}
				else if (cell9 == 1) {
					SetConsoleTextAttribute(hConsole, 9);
					printf("O");
					SetConsoleTextAttribute(hConsole, 7);
				}
				else if (cell9 == 2) {
					SetConsoleTextAttribute(hConsole, 12);
					printf("X");
					SetConsoleTextAttribute(hConsole, 7);
				}
				
			}
			if (row == 2 && col == 0) {
				if (cell4 == 0) {
					SetConsoleTextAttribute(hConsole, 8);
					printf("4");
					SetConsoleTextAttribute(hConsole, 7);
				}
				else if (cell4 == 1) {
					SetConsoleTextAttribute(hConsole, 9);
					printf("O");
					SetConsoleTextAttribute(hConsole, 7);
				}
				else if (cell4 == 2) {
					SetConsoleTextAttribute(hConsole, 12);
					printf("X");
					SetConsoleTextAttribute(hConsole, 7);
				}
			}
			if (row == 2 && col == 2) {
				if (cell5 == 0) {
					SetConsoleTextAttribute(hConsole, 8);
					printf("5");
					SetConsoleTextAttribute(hConsole, 7);
				}
				else if (cell5 == 1) {
					SetConsoleTextAttribute(hConsole, 9);
					printf("O");
					SetConsoleTextAttribute(hConsole, 7);
				}
				else if (cell5 == 2) {
					SetConsoleTextAttribute(hConsole, 12);
					printf("X");
					SetConsoleTextAttribute(hConsole, 7);
				}
			}
			if (row == 2 && col == 4) {
				if (cell6 == 0) {
					SetConsoleTextAttribute(hConsole, 8);
					printf("6");
					SetConsoleTextAttribute(hConsole, 7);
				}
				else if (cell6 == 1) {
					SetConsoleTextAttribute(hConsole, 9);
					printf("O");
					SetConsoleTextAttribute(hConsole, 7);
				}
				else if (cell6 == 2) {
					SetConsoleTextAttribute(hConsole, 12);
					printf("X");
					SetConsoleTextAttribute(hConsole, 7);
				}
			}
			if (row == 4 && col == 0) {
				if (cell1 == 0) {
					SetConsoleTextAttribute(hConsole, 8);
					printf("1");
					SetConsoleTextAttribute(hConsole, 7);
				}
				else if (cell1 == 1) {
					SetConsoleTextAttribute(hConsole, 9);
					printf("O");
					SetConsoleTextAttribute(hConsole, 7);
				}
				else if (cell1 == 2) {
					SetConsoleTextAttribute(hConsole, 12);
					printf("X");
					SetConsoleTextAttribute(hConsole, 7);
				}
			}
			if (row == 4 && col == 2) {
				if (cell2 == 0) {
					SetConsoleTextAttribute(hConsole, 8);
					printf("2");
					SetConsoleTextAttribute(hConsole, 7);
				}
				else if (cell2 == 1) {
					SetConsoleTextAttribute(hConsole, 9);
					printf("O");
					SetConsoleTextAttribute(hConsole, 7);
				}
				else if (cell2 == 2) {
					SetConsoleTextAttribute(hConsole, 12);
					printf("X");
					SetConsoleTextAttribute(hConsole, 7);
				}
			}
			if (row == 4 && col == 4) {
				if (cell3 == 0) {
					SetConsoleTextAttribute(hConsole, 8);
					printf("3");
					SetConsoleTextAttribute(hConsole, 7);
				}
				else if (cell3 == 1) {
					SetConsoleTextAttribute(hConsole, 9);
					printf("O");
					SetConsoleTextAttribute(hConsole, 7);
				}
				else if (cell3 == 2) {
					SetConsoleTextAttribute(hConsole, 12);
					printf("X");
					SetConsoleTextAttribute(hConsole, 7);
				}
			}
			
			// If it's at the end of a line, it newlines.
			if (col == 4) {
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
	int inputCell;
	
	printf("What cell do you want to enter? ");
	 
	while (inputCell <= 0 || inputCell >= 10){
		printf("(Enter a number between 1 and 9) ");
		scanf("%d", &inputCell);
	}
	
	return inputCell;
}

int gameWinCheck (int cell1, int cell2, int cell3, int cell4, int cell5, int cell6, int cell7, int cell8, int cell9, int whoseTurn) {
	
	int gameWon = 0;
	
	//printf("%d %d %d %d %d %d %d %d %d\n", cell1, cell2, cell3, cell4, cell5, cell6, cell7, cell8, cell9);

	// Horizontal wins
	if ((cell1 == cell2) && (cell1 == cell3) && (gameWon == 0)) {
		//printf("1 2 3\n");
		gameWon = threeInARowCheck (cell1, cell2, cell3, whoseTurn);
	}
	if ((cell4 == cell5) && (cell4 == cell6) && (gameWon == 0)) {
		//printf("4 5 6\n");
		gameWon = threeInARowCheck (cell4, cell5, cell6, whoseTurn);
	}
	if ((cell7 == cell8) && (cell7 == cell9) && (gameWon == 0)) {
		//printf("7 8 9\n");
		gameWon = threeInARowCheck (cell7, cell8, cell9, whoseTurn);
	}
	
	// Vertical wins
	if ((cell1 == cell4) && (cell1 == cell7) && (gameWon == 0)) {
		//printf("1 4 7\n");
		gameWon = threeInARowCheck (cell1, cell4, cell7, whoseTurn);
	}
	if ((cell2 == cell5) && (cell2 == cell8) && (gameWon == 0)) {
		//printf("2 5 8\n");
		gameWon = threeInARowCheck (cell2, cell5, cell8, whoseTurn);
	}
	if ((cell3 == cell6) && (cell3 == cell9) && (gameWon == 0)) {
		//printf("3 6 9\n");
		gameWon = threeInARowCheck (cell3, cell6, cell9, whoseTurn);
	}
	
	// Diagonal wins
	if ((cell1 == cell5) && (cell1 == cell9) && (gameWon == 0)) {
		//printf("1 5 9\n");
		gameWon = threeInARowCheck (cell1, cell5, cell9, whoseTurn);
	}
	if ((cell3 == cell5) && (cell3 == cell7) && (gameWon == 0)) {
		//printf("3 5 7\n");
		gameWon = threeInARowCheck (cell3, cell5, cell7, whoseTurn);
	}
	return gameWon;
}

// This function checks if the three in a row isn't blank.
int threeInARowCheck (int check1, int check2, int check3, int whoseTurn) {
	int gameWon;
	
	// If any of the three cells are blank, don't win.
	if (check1 == 0 || check2 == 0 || check3 == 0) {
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