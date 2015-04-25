#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// These headers are redundant when they're already called. An IFDEF
// needs to be used.
#include "MainGame.h"
#include "FileIO.h"
#include "Defines.h"

game *buildGame () {
	game *data = malloc(sizeof(game));
	char settings[5];
	char inputChar;
	char *inputString;
	FILE *file;
	printf("Type 0 to play a new game, or 1 to load a game. ");
	settings[0] = getchar();
	
	if (settings[0] == '0') {
		printf("Enter what a map file. (or leave blank for default). ");
		gets(inputString);
		gets(inputString);
		if (strlen(inputString) >= 2) {
			file = fopen(inputString, "r");
			if (file == NULL) {
				printf("Error FILE_NOT_FOUND\n");
				ERROR_CODE = FILE_NOT_FOUND;
			} else {
				loadMapFileData (data, file);
			}
			fclose(file);
		} else {
			loadMapDefaultData (data);
		}

	} else if (settings[0] == '1') {
		printf("Enter the save name. ");
		gets(inputString);
		file = fopen(inputString, "r");
		if (file == NULL) {
			printf("Error FILE_NOT_FOUND\n");
			ERROR_CODE = FILE_NOT_FOUND;
		} else {
			//loadGame (data, file);
		}
		fclose(file);
	} else {
		printf("Error BAD_SETUP_INPUT\n");
		ERROR_CODE = BAD_SETUP_INPUT;
	}
	return data;
}

void initialiseGame (game *data) {
	// THIS IS NOT DONE YET.
	ERROR_CODE = 0;
	data->p1.money = 10000;
	
	checkInitialiseGame (data);
}

void checkInitialiseGame (game *data) {
	// THIS IS NOT DONE YET.
	if (data->p1.money != 10000) {
		reportError (data, TEST_FAILED);
		printf("A test failed in checkInitialiseGame, error: %d\n", ERROR_CODE);
	}
}

// Phase this out.
void reportError (game *data, char errorCode) {
	ERROR_CODE = errorCode;
}

void freeGame (game *data) {
	free(data);
}