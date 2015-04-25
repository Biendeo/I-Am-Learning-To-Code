#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Defines.h"
#include "GameUI.h"
#include "MainGame.h"
#include "GameAI.h"
#include "FileIO.h"
#include "DrawingUI.h"

void loadMapFileData (game *data, FILE *file) {
	int xPos = 0;
	int yPos = 0;
	unsigned char bufferChar;
	
	while ((yPos < MAP_HEIGHT) || (bufferChar != EOF)) {
		while ((xPos < MAP_WIDTH) || (bufferChar != EOF)) {
			bufferChar = fgetc(file);
			if (bufferChar == CHAR_NULL_HQ) {
				data->mapData[xPos][yPos] = NULL_HQ;
				xPos++;
			} else if (bufferChar == CHAR_NULL_CITY) {
				data->mapData[xPos][yPos] = NULL_CITY;
				xPos++;
			} else if (bufferChar == CHAR_NULL_BASE) {
				data->mapData[xPos][yPos] = NULL_BASE;
				xPos++;
			}
			else if (bufferChar == CHAR_RED_HQ) {
				data->mapData[xPos][yPos] = RED_HQ;
				xPos++;
			} else if (bufferChar == CHAR_RED_CITY) {
				data->mapData[xPos][yPos] = RED_CITY;
				xPos++;
			} else if (bufferChar == CHAR_RED_BASE) {
				data->mapData[xPos][yPos] = RED_BASE;
				xPos++;
			}
			else if (bufferChar == CHAR_BLUE_HQ) {
				data->mapData[xPos][yPos] = BLUE_HQ;
				xPos++;
			} else if (bufferChar == CHAR_BLUE_CITY) {
				data->mapData[xPos][yPos] = BLUE_CITY;
				xPos++;
			} else if (bufferChar == CHAR_BLUE_BASE) {
				data->mapData[xPos][yPos] = BLUE_BASE;
				xPos++;
			}
			else if (bufferChar == CHAR_GREEN_HQ) {
				data->mapData[xPos][yPos] = GREEN_HQ;
				xPos++;
			} else if (bufferChar == CHAR_GREEN_CITY) {
				data->mapData[xPos][yPos] = GREEN_CITY;
				xPos++;
			} else if (bufferChar == CHAR_GREEN_BASE) {
				data->mapData[xPos][yPos] = GREEN_BASE;
				xPos++;
			}
			else if (bufferChar == CHAR_YELLOW_HQ) {
				data->mapData[xPos][yPos] = YELLOW_HQ;
				xPos++;
			} else if (bufferChar == CHAR_YELLOW_CITY) {
				data->mapData[xPos][yPos] = YELLOW_CITY;
				xPos++;
			} else if (bufferChar == CHAR_YELLOW_BASE) {
				data->mapData[xPos][yPos] = YELLOW_BASE;
				xPos++;
			}
			else if (bufferChar == CHAR_PLAIN) {
				data->mapData[xPos][yPos] = PLAIN;
				xPos++;
			} else if (bufferChar == CHAR_ROAD) {
				data->mapData[xPos][yPos] = ROAD;
				xPos++;
			} else if (bufferChar == CHAR_SEA) {
				data->mapData[xPos][yPos] = SEA;
				xPos++;
			} else if (bufferChar == CHAR_RIVER) {
				data->mapData[xPos][yPos] = RIVER;
				xPos++;
			} else if (bufferChar == CHAR_WOOD) {
				data->mapData[xPos][yPos] = WOOD;
				xPos++;
			} else if (bufferChar == CHAR_MOUNTAIN) {
				data->mapData[xPos][yPos] = MOUNTAIN;
				xPos++;
			} else if (bufferChar == CHAR_BRIDGE) {
				data->mapData[xPos][yPos] = BRIDGE;
				xPos++;
			} else if (bufferChar == CHAR_SHOAL) {
				data->mapData[xPos][yPos] = SHOAL;
				xPos++;
			} else if (bufferChar == CHAR_REEF) {
				data->mapData[xPos][yPos] = REEF;
				xPos++;
			}
		}
		yPos++;
		xPos = 0;
	}
	
	if (bufferChar == EOF) {
		ERROR_CODE = MAP_INVALID_SIZE;
	}
}

void loadMapDefaultData (game *data) {
	// SPANN ISLAND
	unsigned char mapData[MAP_WIDTH][MAP_HEIGHT] = {
		{53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53},  
		{53, 53, 53, 51,  2, 51, 13, 13, 53, 53, 59, 53},
		{53, 53, 51, 51,  2, 51, 52, 11, 13, 53, 53, 53}, 
		{53, 53, 55, 55, 52, 52, 52, 51, 13, 53, 53, 53}, 
		{53, 53, 52, 55, 53, 53, 53, 51, 51,  2, 53, 53}, 
		{53, 53, 57, 53, 53, 53, 53, 51, 51, 56, 53, 53}, 
		{53, 53, 52, 51, 53, 53, 55, 55, 51, 55, 53, 53}, 
		{53, 53, 51,  2, 51,  2, 52, 51, 51, 51, 53, 53}, 
		{53, 53, 55, 51, 56, 56, 52, 53, 53, 57, 53, 53}, 
		{53, 53, 23, 51, 51,  2, 52, 53, 53, 51, 53, 53},
		{53, 53, 51, 21, 52, 52, 52, 57, 51,  2, 53, 53},		
		{53, 53, 23, 23, 23, 51,  2, 53, 51,  2, 53, 53},
		{53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53},
		{53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53}
	};
	int xPos = 0;
	int yPos = 0;
	while (yPos < MAP_HEIGHT) {
		while (xPos < MAP_WIDTH) {
			data->mapData[xPos][yPos] = mapData[xPos][yPos];
			xPos++;
		}
		xPos = 0;
		yPos++;
	}
}