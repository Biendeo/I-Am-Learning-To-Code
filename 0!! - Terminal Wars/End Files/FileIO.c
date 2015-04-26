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
	short x = 0;
	short y = 0;
	unsigned char bufferChar;
	
	while ((y < MAP_HEIGHT) || (bufferChar != EOF)) {
		while ((x < MAP_WIDTH) || (bufferChar != EOF)) {
			bufferChar = fgetc(file);
			if (bufferChar == CHAR_NULL_HQ) {
				data->mapData[x][y] = NULL_HQ;
				x++;
			} else if (bufferChar == CHAR_NULL_CITY) {
				data->mapData[x][y] = NULL_CITY;
				x++;
			} else if (bufferChar == CHAR_NULL_BASE) {
				data->mapData[x][y] = NULL_BASE;
				x++;
			}
			else if (bufferChar == CHAR_RED_HQ) {
				data->mapData[x][y] = RED_HQ;
				x++;
			} else if (bufferChar == CHAR_RED_CITY) {
				data->mapData[x][y] = RED_CITY;
				x++;
			} else if (bufferChar == CHAR_RED_BASE) {
				data->mapData[x][y] = RED_BASE;
				x++;
			}
			else if (bufferChar == CHAR_BLUE_HQ) {
				data->mapData[x][y] = BLUE_HQ;
				x++;
			} else if (bufferChar == CHAR_BLUE_CITY) {
				data->mapData[x][y] = BLUE_CITY;
				x++;
			} else if (bufferChar == CHAR_BLUE_BASE) {
				data->mapData[x][y] = BLUE_BASE;
				x++;
			}
			else if (bufferChar == CHAR_GREEN_HQ) {
				data->mapData[x][y] = GREEN_HQ;
				x++;
			} else if (bufferChar == CHAR_GREEN_CITY) {
				data->mapData[x][y] = GREEN_CITY;
				x++;
			} else if (bufferChar == CHAR_GREEN_BASE) {
				data->mapData[x][y] = GREEN_BASE;
				x++;
			}
			else if (bufferChar == CHAR_YELLOW_HQ) {
				data->mapData[x][y] = YELLOW_HQ;
				x++;
			} else if (bufferChar == CHAR_YELLOW_CITY) {
				data->mapData[x][y] = YELLOW_CITY;
				x++;
			} else if (bufferChar == CHAR_YELLOW_BASE) {
				data->mapData[x][y] = YELLOW_BASE;
				x++;
			}
			else if (bufferChar == CHAR_PLAIN) {
				data->mapData[x][y] = PLAIN;
				x++;
			} else if (bufferChar == CHAR_ROAD) {
				data->mapData[x][y] = ROAD;
				x++;
			} else if (bufferChar == CHAR_SEA) {
				data->mapData[x][y] = SEA;
				x++;
			} else if (bufferChar == CHAR_RIVER) {
				data->mapData[x][y] = RIVER;
				x++;
			} else if (bufferChar == CHAR_WOOD) {
				data->mapData[x][y] = WOOD;
				x++;
			} else if (bufferChar == CHAR_MOUNTAIN) {
				data->mapData[x][y] = MOUNTAIN;
				x++;
			} else if (bufferChar == CHAR_BRIDGE) {
				data->mapData[x][y] = BRIDGE;
				x++;
			} else if (bufferChar == CHAR_SHOAL) {
				data->mapData[x][y] = SHOAL;
				x++;
			} else if (bufferChar == CHAR_REEF) {
				data->mapData[x][y] = REEF;
				x++;
			}
		}
		y++;
		x = 0;
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
	short x = 0;
	short y = 0;
	while (y < MAP_HEIGHT) {
		while (x < MAP_WIDTH) {
			data->mapData[x][y] = mapData[x][y];
			x++;
		}
		x = 0;
		y++;
	}
}