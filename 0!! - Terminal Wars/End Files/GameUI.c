#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Defines.h"
#include "GameUI.h"
#include "MainGame.h"
#include "GameAI.h"
#include "FileIO.h"
#include "DrawingUI.h"

// After capturing works, this will be the next priority.
int main (int argc, char *argv[]) {
	srand(time(NULL));
	screenSplash();
	if (!argv[1]) {
		START_GAME;
	testDrawing(data);
	END_GAME;
	return ERROR_CODE;
	} else {
		game *data = malloc(sizeof(game));
		loadGameData(data, argv[1]);
	if (ERROR_CODE == ALL_GOOD) {
		testDrawing(data);
	}
	END_GAME;
	return ERROR_CODE;
	}
}