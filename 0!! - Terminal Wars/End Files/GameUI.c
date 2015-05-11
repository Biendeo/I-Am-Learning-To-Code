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
	START_GAME;
	if (argv[1]) {
		loadGameData(data, argv[1]);
	}
	testDrawing(data);
	END_GAME;
	return ERROR_CODE;
}