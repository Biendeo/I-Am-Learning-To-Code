#include <iostream>

enum spacevalue {
	empty,
	nought,
	cross
};

class TicTacToeGame {
	char space[9];
	char turnNumber;
	char whoseTurn;

	public:

	TicTacToeGame(char whoGoesFirst) {
		whoseTurn = whoGoesFirst;
		turnNumber = 1;
		for (unsigned char i = 0; i < 9; i++) {
			space[i] = empty;
		}
	}
	
	char getSpaceValue(unsigned char spaceNum);
	char getTurnNumber();
	char getWhoseTurn();
	void newTurn();
	char checkWin();
	void inputSpaceValue(unsigned char spaceNum);
};

char TicTacToeGame::getSpaceValue(unsigned char spaceNum) {
	return space[spaceNum];
}

char TicTacToeGame::getTurnNumber() {
	return turnNumber;
}

char TicTacToeGame::getWhoseTurn() {
	return whoseTurn;
}

void TicTacToeGame::newTurn() {
	turnNumber++;
	if (whoseTurn == nought) {
		whoseTurn = cross;
	} else {
		whoseTurn = nought;
	}
}

char TicTacToeGame::checkWin() {
	char space1, space2, space3;
	char whoWon = empty;

	for (unsigned char i = 0; ((i < 8) && (whoWon == empty)); i++) {
		switch (i) {
			case 0:
				space1 = getSpaceValue(0);
				space2 = getSpaceValue(1);
				space3 = getSpaceValue(2);
				break;
			case 1:
				space1 = getSpaceValue(3);
				space2 = getSpaceValue(4);
				space3 = getSpaceValue(5);
				break;
			case 2:
				space1 = getSpaceValue(6);
				space2 = getSpaceValue(7);
				space3 = getSpaceValue(8);
				break;
			case 3:
				space1 = getSpaceValue(0);
				space2 = getSpaceValue(3);
				space3 = getSpaceValue(6);
				break;
			case 4:
				space1 = getSpaceValue(1);
				space2 = getSpaceValue(4);
				space3 = getSpaceValue(7);
				break;
			case 5:
				space1 = getSpaceValue(2);
				space2 = getSpaceValue(5);
				space3 = getSpaceValue(8);
				break;
			case 6:
				space1 = getSpaceValue(0);
				space2 = getSpaceValue(4);
				space3 = getSpaceValue(8);
				break;
			case 7:
				space1 = getSpaceValue(2);
				space2 = getSpaceValue(4);
				space3 = getSpaceValue(6);
				break;
		}

		if ((space1 == space2) && (space2 == space3)) {
			whoWon = space1;
		}
	}

	return whoWon;
}

void TicTacToeGame::inputSpaceValue(unsigned char spaceNum) {
	space[spaceNum] = getWhoseTurn();
}

void splashScreen();
char decideWhoGoesFirst();
void gameTime(TicTacToeGame *g);
void boardDraw(TicTacToeGame *g);
void inputNumber(TicTacToeGame *g);
void printWinner(TicTacToeGame *g);

int main(int argc, char *argv[]) {
	splashScreen();

	char whoGoesFirst = decideWhoGoesFirst();
	TicTacToeGame g (whoGoesFirst);

	gameTime(&g);

	printWinner(&g);

	return 0;
}

void splashScreen() {
	std::cout << "+----------------+" << std::endl;
	std::cout << "|                |" << std::endl;
	std::cout << "|   Tic Tac Toe  |" << std::endl;
	std::cout << "|                |" << std::endl;
	std::cout << "+----------------+" << std::endl << std::endl;
}

char decideWhoGoesFirst() {
	char whoGoesFirst = empty;
	char inputChar = 0;

	while (whoGoesFirst == empty) {
		std::cout << "Which player will go first? (Type O or X) ";
		std::cin >> inputChar;
		if ((inputChar == 'o') || (inputChar == 'O')) {
			whoGoesFirst = nought;
		} else if((inputChar == 'x') || (inputChar == 'X')) {
			whoGoesFirst = cross;
		} else {
			std::cout << "That's not what I was expecting-> Try again." << std::endl;
		}
	}

	fflush(stdin);

	return whoGoesFirst;
}

void gameTime(TicTacToeGame *g) {
	while ((g->getTurnNumber() <= 9) && (g->checkWin() == empty)) {

		boardDraw(g);

		if (g->getWhoseTurn() == nought) {
			std::cout << "It's O's turn!" << std::endl;
		} else {
			std::cout << "It's X's turn!" << std::endl;
		}

		inputNumber(g);

		g->newTurn();
	}
}

void boardDraw(TicTacToeGame *g) {
	char row = 0;
	char col = 0;
	char charToDraw = empty;

	std::cout << std::endl;

	while (row < 5) {
		while (col < 5) {
			if ((row == 0) && (col == 0)) {
				charToDraw = g->getSpaceValue(6);
				if (charToDraw == empty) charToDraw = '7';
			} else if ((row == 0) && (col == 2)) {
				charToDraw = g->getSpaceValue(7);
				if (charToDraw == empty) charToDraw = '8';
			} else if ((row == 0) && (col == 4)) {
				charToDraw = g->getSpaceValue(8);
				if (charToDraw == empty) charToDraw = '9';
			} else if ((row == 2) && (col == 0)) {
				charToDraw = g->getSpaceValue(3);
				if (charToDraw == empty) charToDraw = '4';
			} else if ((row == 2) && (col == 2)) {
				charToDraw = g->getSpaceValue(4);
				if (charToDraw == empty) charToDraw = '5';
			} else if ((row == 2) && (col == 4)) {
				charToDraw = g->getSpaceValue(5);
				if (charToDraw == empty) charToDraw = '6';
			} else if ((row == 4) && (col == 0)) {
				charToDraw = g->getSpaceValue(0);
				if (charToDraw == empty) charToDraw = '1';
			} else if ((row == 4) && (col == 2)) {
				charToDraw = g->getSpaceValue(1);
				if (charToDraw == empty) charToDraw = '2';
			} else if ((row == 4) && (col == 4)) {
				charToDraw = g->getSpaceValue(2);
				if (charToDraw == empty) charToDraw = '3';
			} else if ((row % 2 == 1) && (col % 2 == 1)) {
				charToDraw = '+';
			} else if (row % 2 == 1) {
				charToDraw = '-';
			} else if (col % 2 == 1) {
				charToDraw = '|';
			}

			if (charToDraw == nought) {
				charToDraw = 'O';
			} else if (charToDraw == cross) {
				charToDraw = 'X';
			}

			std::cout << charToDraw;
			col++;
		}

		std::cout << std::endl;
		row++;
		col = 0;
	}

	std::cout << std::endl;
}

void inputNumber(TicTacToeGame *g) {
	unsigned char inputNum;
	bool bMoveDone = false;

	while (bMoveDone == false) {
		std::cout << "Type a number from 1 to 9. ";
		std::cin >> inputNum;

		inputNum -= '1';

		if (inputNum >= 9) {
			std::cout << "That wasn't a valid space. Try again." << std::endl;
		} else {
			if (g->getSpaceValue(inputNum) != empty) {
				std::cout << "That space was not empty. Try again." << std::endl;
			} else {
				g->inputSpaceValue(inputNum);
				bMoveDone = true;
			}
		}

		fflush(stdin);
	}
}

void printWinner(TicTacToeGame *g) {
	char winner = g->checkWin();

	if (winner == nought) {
		std::cout << "O won!" << std::endl;
	} else if (winner == cross) {
		std::cout << "X won!" << std::endl;
	}
}