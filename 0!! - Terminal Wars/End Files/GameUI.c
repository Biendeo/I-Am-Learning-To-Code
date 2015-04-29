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

int main (int argc, char *argv[]) {
	// This is to test the screenClear function.
	srand(time(NULL));
	screenSplash();
	START_GAME;
	testDrawing(data);
	END_GAME;
	return ERROR_CODE;
}