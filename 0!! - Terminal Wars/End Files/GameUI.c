#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Defines.h"
#include "GameUI.h"
#include "MainGame.h"
#include "GameAI.h"
#include "FileIO.h"
#include "DrawingUI.h"

int main (int argc, char *argv[]) {
	START_GAME;
	// These lines are just a test to see if the data actually changed.
	printf("data->p1.money = %d\n", data->p1.money);
	printf("Program ended in state %d\n", ERROR_CODE);
	END_GAME;
	return ERROR_CODE;
}