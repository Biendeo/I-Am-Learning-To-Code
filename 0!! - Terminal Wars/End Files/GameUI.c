#include <stdio.h>
#include <stdlib.h>

#include "GameUI.h"
#include "MainGame.h"
#include "GameAI.h"
#include "FileIO.h"
#include "DrawingUI.h"
#include "Defines.h"

int main (int argc, char *argv[]) {
	char returnState;
	game data;
	game *dataPtr;
	data.p1.money = 5000;
	if (initialiseGame (dataPtr) == ALL_GOOD) {
		returnState = ALL_GOOD;
	}
	else {
		returnState = TEST_FAILED;
		printf("A test failed in main\n");
	}
	printf("data.p1.money = %d", data.p1.money);
	return returnState;
}