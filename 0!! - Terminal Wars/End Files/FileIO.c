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
	
	while ((y < MAP_HEIGHT) && (bufferChar != EOF)) {
		while ((x < MAP_WIDTH) && (bufferChar != EOF)) {
			bufferChar = fgetc(file);
			translateMapFile(data, bufferChar);
			x++;
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
	unsigned char tempData[MAP_WIDTH][MAP_HEIGHT] = {
		{'3', '3', '3', '3', '3', '3', '3', '3', '3', '3', '3', '3'},
		{'3', '3', '3', '1', '@', '1', 'd', 'd', '3', '3', '8', '3'},
		{'3', '3', '1', '1', '@', '1', '2', 'a', 'd', '3', '3', '3'},
		{'3', '3', '5', '5', '2', '2', '2', '1', 'd', '3', '3', '3'},
		{'3', '3', '2', '2', '2', '1', 's', '1', '1', '6', '3', '3'},
		{'3', '3', '2', '5', '3', '3', '3', '1', '1', '@', '3', '3'},
		{'3', '3', '7', '4', '3', '3', '3', '1', '1', '6', '3', '3'},
		{'3', '3', '2', '1', '3', '3', '5', '5', '1', '5', '3', '3'},
		{'3', '3', '2', '2', '2', '1', '2', '5', '1', '#', '3', '3'},
		{'3', '3', '1', '@', '1', '@', '2', '1', '1', '1', '3', '3'},
		{'3', '3', '5', '1', '6', '6', '2', '3', '3', '1', '3', '3'},
		{'3', '3', 'c', '1', '1', '@', '2', '3', '3', '1', '3', '3'},
		{'3', '3', '1', 'z', '2', '2', '2', '7', '1', '@', '3', '3'},
		{'3', '3', 'c', 'c', 'c', '1', '@', '3', '1', '@', '3', '3'},
		{'3', '3', '3', '3', '3', '3', '3', '3', '3', '3', '3', '3'},
		{'3', '3', '3', '3', '3', '3', '3', '3', '3', '3', '3', '3'},
	};
	short x = 0;
	short y = 0;
	while (y < MAP_HEIGHT) {
		while (x < MAP_WIDTH) {
			translateMapData(data, tempData[x][y]);
			x++
		}
		y++;
		x = 0;
	}
}

void translateMapData (game *data, unsigned char tile) {
	if (tile == CHAR_NULL_HQ) {
		data->mapData[x][y] = NULL_HQ;
	} else if (tile == CHAR_NULL_CITY) {
		data->mapData[x][y] = NULL_CITY;
	} else if (tile == CHAR_NULL_BASE) {
		data->mapData[x][y] = NULL_BASE;
	} else if (tile == CHAR_NULL_AIRPORT) {
		data->mapData[x][y] = NULL_AIRPORT;
	} else if (tile == CHAR_NULL_PORT) {
		data->mapData[x][y] = NULL_PORT;
	}
	else if (tile == CHAR_RED_HQ) {
		data->mapData[x][y] = RED_HQ;
	} else if (tile == CHAR_RED_CITY) {
		data->mapData[x][y] = RED_CITY;
	} else if (tile == CHAR_RED_BASE) {
		data->mapData[x][y] = RED_BASE;
	} else if (tile == CHAR_RED_AIRPORT) {
		data->mapData[x][y] = RED_AIRPORT;
	} else if (tile == CHAR_RED_PORT) {
		data->mapData[x][y] = RED_PORT;
	}
	else if (tile == CHAR_BLUE_HQ) {
		data->mapData[x][y] = BLUE_HQ;
	} else if (tile == CHAR_BLUE_CITY) {
		data->mapData[x][y] = BLUE_CITY;
	} else if (tile == CHAR_BLUE_BASE) {
		data->mapData[x][y] = BLUE_BASE;
	} else if (tile == CHAR_BLUE_AIRPORT) {
		data->mapData[x][y] = BLUE_AIRPORT;
	} else if (tile == CHAR_BLUE_PORT) {
		data->mapData[x][y] = BLUE_PORT;
	}
	else if (tile == CHAR_GREEN_HQ) {
		data->mapData[x][y] = GREEN_HQ;
	} else if (tile == CHAR_GREEN_CITY) {
		data->mapData[x][y] = GREEN_CITY;
	} else if (tile == CHAR_GREEN_BASE) {
		data->mapData[x][y] = GREEN_BASE;
	} else if (tile == CHAR_GREEN_AIRPORT) {
		data->mapData[x][y] = GREEN_AIRPORT;
	} else if (tile == CHAR_GREEN_PORT) {
		data->mapData[x][y] = GREEN_PORT;
	}
	else if (tile == CHAR_YELLOW_HQ) {
		data->mapData[x][y] = YELLOW_HQ;
	} else if (tile == CHAR_YELLOW_CITY) {
		data->mapData[x][y] = YELLOW_CITY;
	} else if (tile == CHAR_YELLOW_BASE) {
		data->mapData[x][y] = YELLOW_BASE;
	} else if (tile == CHAR_YELLOW_AIRPORT) {
		data->mapData[x][y] = YELLOW_AIRPORT;
	} else if (tile == CHAR_YELLOW_PORT) {
		data->mapData[x][y] = YELLOW_PORT;
	}
	else if (tile == CHAR_PLAIN) {
		data->mapData[x][y] = PLAIN;
	} else if (tile == CHAR_ROAD) {
		data->mapData[x][y] = ROAD;
	} else if (tile == CHAR_SEA) {
		data->mapData[x][y] = SEA;
	} else if (tile == CHAR_RIVER) {
		data->mapData[x][y] = RIVER;
	} else if (tile == CHAR_WOOD) {
		data->mapData[x][y] = WOOD;
	} else if (tile == CHAR_MOUNTAIN) {
		data->mapData[x][y] = MOUNTAIN;
	} else if (tile == CHAR_BRIDGE) {
		data->mapData[x][y] = BRIDGE;
	} else if (tile == CHAR_SHOAL) {
		data->mapData[x][y] = SHOAL;
	} else if (tile == CHAR_REEF) {
		data->mapData[x][y] = REEF;
	} else {
		// For the default map data, don't do this.
		x--;
	}
}