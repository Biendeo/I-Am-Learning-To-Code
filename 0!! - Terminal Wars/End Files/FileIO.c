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
			if (bufferChar == CHAR_NULL_HQ) {
				data->mapData[x][y] = NULL_HQ;
			} else if (bufferChar == CHAR_NULL_CITY) {
				data->mapData[x][y] = NULL_CITY;
			} else if (bufferChar == CHAR_NULL_BASE) {
				data->mapData[x][y] = NULL_BASE;
			} else if (bufferChar == CHAR_NULL_AIRPORT) {
				data->mapData[x][y] = NULL_AIRPORT;
			} else if (bufferChar == CHAR_NULL_PORT) {
				data->mapData[x][y] = NULL_PORT;
			}
			else if (bufferChar == CHAR_RED_HQ) {
				data->mapData[x][y] = RED_HQ;
			} else if (bufferChar == CHAR_RED_CITY) {
				data->mapData[x][y] = RED_CITY;
			} else if (bufferChar == CHAR_RED_BASE) {
				data->mapData[x][y] = RED_BASE;
			} else if (bufferChar == CHAR_RED_AIRPORT) {
				data->mapData[x][y] = RED_AIRPORT;
			} else if (bufferChar == CHAR_RED_PORT) {
				data->mapData[x][y] = RED_PORT;
			}
			else if (bufferChar == CHAR_BLUE_HQ) {
				data->mapData[x][y] = BLUE_HQ;
			} else if (bufferChar == CHAR_BLUE_CITY) {
				data->mapData[x][y] = BLUE_CITY;
			} else if (bufferChar == CHAR_BLUE_BASE) {
				data->mapData[x][y] = BLUE_BASE;
			} else if (bufferChar == CHAR_BLUE_AIRPORT) {
				data->mapData[x][y] = BLUE_AIRPORT;
			} else if (bufferChar == CHAR_BLUE_PORT) {
				data->mapData[x][y] = BLUE_PORT;
			}
			else if (bufferChar == CHAR_GREEN_HQ) {
				data->mapData[x][y] = GREEN_HQ;
			} else if (bufferChar == CHAR_GREEN_CITY) {
				data->mapData[x][y] = GREEN_CITY;
			} else if (bufferChar == CHAR_GREEN_BASE) {
				data->mapData[x][y] = GREEN_BASE;
			} else if (bufferChar == CHAR_GREEN_AIRPORT) {
				data->mapData[x][y] = GREEN_AIRPORT;
			} else if (bufferChar == CHAR_GREEN_PORT) {
				data->mapData[x][y] = GREEN_PORT;
			}
			else if (bufferChar == CHAR_YELLOW_HQ) {
				data->mapData[x][y] = YELLOW_HQ;
			} else if (bufferChar == CHAR_YELLOW_CITY) {
				data->mapData[x][y] = YELLOW_CITY;
			} else if (bufferChar == CHAR_YELLOW_BASE) {
				data->mapData[x][y] = YELLOW_BASE;
			} else if (bufferChar == CHAR_YELLOW_AIRPORT) {
				data->mapData[x][y] = YELLOW_AIRPORT;
			} else if (bufferChar == CHAR_YELLOW_PORT) {
				data->mapData[x][y] = YELLOW_PORT;
			}
			else if (bufferChar == CHAR_PLAIN) {
				data->mapData[x][y] = PLAIN;
			} else if (bufferChar == CHAR_ROAD) {
				data->mapData[x][y] = ROAD;
			} else if (bufferChar == CHAR_SEA) {
				data->mapData[x][y] = SEA;
			} else if (bufferChar == CHAR_RIVER) {
				data->mapData[x][y] = RIVER;
			} else if (bufferChar == CHAR_WOOD) {
				data->mapData[x][y] = WOOD;
			} else if (bufferChar == CHAR_MOUNTAIN) {
				data->mapData[x][y] = MOUNTAIN;
			} else if (bufferChar == CHAR_BRIDGE) {
				data->mapData[x][y] = BRIDGE;
			} else if (bufferChar == CHAR_SHOAL) {
				data->mapData[x][y] = SHOAL;
			} else if (bufferChar == CHAR_REEF) {
				data->mapData[x][y] = REEF;
			} else {
				x--;
			}
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
						if (tempData[x][y] == CHAR_NULL_HQ) {
				data->mapData[x][y] = NULL_HQ;
				x++;
			} else if (tempData[x][y] == CHAR_NULL_CITY) {
				data->mapData[x][y] = NULL_CITY;
				x++;
			} else if (tempData[x][y] == CHAR_NULL_BASE) {
				data->mapData[x][y] = NULL_BASE;
				x++;
			}
			else if (tempData[x][y] == CHAR_RED_HQ) {
				data->mapData[x][y] = RED_HQ;
				x++;
			} else if (tempData[x][y] == CHAR_RED_CITY) {
				data->mapData[x][y] = RED_CITY;
				x++;
			} else if (tempData[x][y] == CHAR_RED_BASE) {
				data->mapData[x][y] = RED_BASE;
				x++;
			}
			else if (tempData[x][y] == CHAR_BLUE_HQ) {
				data->mapData[x][y] = BLUE_HQ;
				x++;
			} else if (tempData[x][y] == CHAR_BLUE_CITY) {
				data->mapData[x][y] = BLUE_CITY;
				x++;
			} else if (tempData[x][y] == CHAR_BLUE_BASE) {
				data->mapData[x][y] = BLUE_BASE;
				x++;
			}
			else if (tempData[x][y] == CHAR_GREEN_HQ) {
				data->mapData[x][y] = GREEN_HQ;
				x++;
			} else if (tempData[x][y] == CHAR_GREEN_CITY) {
				data->mapData[x][y] = GREEN_CITY;
				x++;
			} else if (tempData[x][y] == CHAR_GREEN_BASE) {
				data->mapData[x][y] = GREEN_BASE;
				x++;
			}
			else if (tempData[x][y] == CHAR_YELLOW_HQ) {
				data->mapData[x][y] = YELLOW_HQ;
				x++;
			} else if (tempData[x][y] == CHAR_YELLOW_CITY) {
				data->mapData[x][y] = YELLOW_CITY;
				x++;
			} else if (tempData[x][y] == CHAR_YELLOW_BASE) {
				data->mapData[x][y] = YELLOW_BASE;
				x++;
			}
			else if (tempData[x][y] == CHAR_PLAIN) {
				data->mapData[x][y] = PLAIN;
				x++;
			} else if (tempData[x][y] == CHAR_ROAD) {
				data->mapData[x][y] = ROAD;
				x++;
			} else if (tempData[x][y] == CHAR_SEA) {
				data->mapData[x][y] = SEA;
				x++;
			} else if (tempData[x][y] == CHAR_RIVER) {
				data->mapData[x][y] = RIVER;
				x++;
			} else if (tempData[x][y] == CHAR_WOOD) {
				data->mapData[x][y] = WOOD;
				x++;
			} else if (tempData[x][y] == CHAR_MOUNTAIN) {
				data->mapData[x][y] = MOUNTAIN;
				x++;
			} else if (tempData[x][y] == CHAR_BRIDGE) {
				data->mapData[x][y] = BRIDGE;
				x++;
			} else if (tempData[x][y] == CHAR_SHOAL) {
				data->mapData[x][y] = SHOAL;
				x++;
			} else if (tempData[x][y] == CHAR_REEF) {
				data->mapData[x][y] = REEF;
				x++;
			}
		}
		y++;
		x = 0;
	}
}