// If you're viewing this, it's a bit out of date. The map.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAP_WIDTH  20
#define MAP_HEIGHT 15

#define GRASS    '0'
#define ROAD     '1'
#define WATER    '2'
#define TREE     '3'
#define MOUNTAIN '4'

int main(int argc, char *argv[]) {
	unsigned char mapGrid[MAP_WIDTH][MAP_HEIGHT] = {{0}};
	int xPos = 0;
	int yPos = 0;
	unsigned char bufferChar;
	
	FILE *file = fopen("map.txt", "r");
	
	while (yPos < MAP_HEIGHT) {
		while (xPos < MAP_WIDTH) {
			bufferChar = fgetc(file);
			if (GRASS <= bufferChar && bufferChar <= MOUNTAIN) {
				mapGrid[xPos][yPos] = bufferChar;
				printf("%c", bufferChar);
				xPos++;
			}
		}
		printf("\n");
		yPos++;
		xPos = 0;
	}
	
	printf("\n\n\n");
	fclose(file);
	
	xPos = 0;
	yPos = 0;
	
	while (yPos < MAP_HEIGHT) {
		while (xPos < MAP_WIDTH) {
			if (mapGrid[xPos][yPos] == GRASS)         printf("_");
			else if (mapGrid[xPos][yPos] == ROAD)     printf("#");
			else if (mapGrid[xPos][yPos] == WATER)    printf("~");
			else if (mapGrid[xPos][yPos] == TREE)     printf("4");
			else if (mapGrid[xPos][yPos] == MOUNTAIN) printf("^");
			else printf("%u", mapGrid[xPos][yPos]);
			
			xPos++;	
			}
		printf("\n");
		yPos++;
		xPos = 0;
	}
	return 0;
}