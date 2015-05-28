// This is an attempt to make an array inside a struct based on other
// variables. This can be used to set the size of the map dynamically.

#include <stdio.h>
#include <stdlib.h>

typedef struct gamedata {
	short mapWidth;
	short mapHeight;
	unsigned char *mapData;
	char errorCode;
} game;

int main (int argc, char *argv[]) {
	short mapWidth;
	short mapHeight;
	
	printf("Type two numbers. ");
	scanf("%d %d", &mapWidth, &mapHeight);
	game testGame;
	game *gamePtr;
	testGame.mapWidth = mapWidth;
	testGame.mapHeight = mapHeight;

	unsigned char *mapPtr = malloc(sizeof(char) * mapWidth * mapHeight);
	
	testGame.mapData = *mapPtr;
	
	printf("The array is size %d\n", sizeof(testGame.mapData));
	printf("If you see this, it's all good.\n");
	
	return EXIT_SUCCESS;
}

void tester (game* gamePtr) {
	if (gamePtr->mapData);
}