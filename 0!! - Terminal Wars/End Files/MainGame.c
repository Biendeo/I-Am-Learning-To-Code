#include <stdio.h>
#include <stdlib.h>
#include "MainGame.h"
#include "FileIO.h"
#include "Defines.h"

int initialiseGame (game *gameData) {
	char returnState;
	
	gameData->p1.money = 10000;
	
	if (checkInitialiseGame (*gameData) == ALL_GOOD) {
		returnState = ALL_GOOD;
	}
	else {
		returnState = TEST_FAILED;
		printf("A test failed in intialiseGame\n");
	}
	return returnState;
}

int checkInitialiseGame (game *gameData) {
	char returnState;
	
	if (gameData->p1.money == 10000) {
		returnState = ALL_GOOD;
	}
	else {
		returnState = TEST_FAILED;
		printf("A test failed in checkInitialiseGame\n");
	}
	return returnState;
}