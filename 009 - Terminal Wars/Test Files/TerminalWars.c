#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NO_FILE 1

#define MAP_WIDTH  20
#define MAP_HEIGHT 15

#define GRASS    '0'
#define ROAD     '1'
#define WATER    '2'
#define TREE     '3'
#define MOUNTAIN '4'

int readMap (unsigned char mapGrid[][MAP_HEIGHT]);

int main(int argc, char *argv[]) {
	unsigned char mapGrid[MAP_WIDTH][MAP_HEIGHT] = {{0}};
	
	int xPos = 0;
	int yPos = 0;
	
	if ((readMap (mapGrid[0][MAP_HEIGHT])) == NO_FILE) {
		return NO_FILE;
	}
	
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
	
	return EXIT_SUCCESS;
}

int readMap (unsigned char mapGrid[][MAP_HEIGHT]) {
	unsigned char bufferChar;
	int xPos = 0;
	int yPos = 0;
	
	FILE *file = fopen("map.txt", "r");
	
	if (!file) {
		return NO_FILE;
	}
	
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
	
	return EXIT_SUCCESS;
}