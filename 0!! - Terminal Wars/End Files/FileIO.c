#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Defines.h"
#include "MainGame.h"
#include "FileIO.h"

void loadMapFileData (game *data, FILE *file) {
	short x = 0;
	short y = 0;
	unsigned char bufferChar;
	
	while ((y < MAP_HEIGHT) && (bufferChar != EOF)) {
		while ((x < MAP_WIDTH) && (bufferChar != EOF)) {
			bufferChar = fgetc(file);
			translateMapData(data, bufferChar, x, y);
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
			translateMapData (data, tempData[x][y], x, y);
			x++;
		}
		y++;
		x = 0;
	}
}

void translateMapData (game *data, unsigned char tile, short x, short y) {
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
		x--;
	}
}
void loadGameData (game *data, char *filename) {
	FILE *savefile;
	savefile = fopen(filename, "r");
	
	if (savefile == NULL) {
		ERROR_CODE = FILE_NOT_FOUND;
	} else {
		
		printf("Loading game properties...\n");
		
		fread(&data->turnNum, sizeof(data->turnNum), 1, savefile);
		fread(&data->numberOfPlayers, sizeof(data->numberOfPlayers), 1, savefile);
		fread(&data->whoseTurn, sizeof(data->whoseTurn), 1, savefile);
		fread(&data->cursor.x, sizeof(data->cursor.x), 1, savefile);
		fread(&data->cursor.y, sizeof(data->cursor.y), 1, savefile);
		fread(&data->interfaceMode, sizeof(data->interfaceMode), 1, savefile);
		fread(&data->drawMode, sizeof(data->drawMode), 1, savefile);
		fread(&data->attacker, sizeof(data->attacker), 1, savefile);
		
		printf("Loading map data...\n");
		
		short xPos = 0;
		short yPos = 0;
		
		while (yPos < MAP_HEIGHT) {
			while (xPos < MAP_WIDTH) {
				fread(&data->mapData[xPos][yPos], sizeof(unsigned char), 1, savefile);
				xPos++;
			}
			xPos = 0;
			yPos++;
		}
		
		printf("Loading player data...\n");
		
		fread(&data->p1.isItHuman, sizeof(data->p1.isItHuman), 1, savefile);
		fread(&data->p1.color, sizeof(data->p1.color), 1, savefile);
		fread(&data->p1.money, sizeof(data->p1.money), 1, savefile);
		fread(&data->p1.buildingsOwned, sizeof(data->p1.buildingsOwned), 1, savefile);
		fread(&data->p1.unitsOwned, sizeof(data->p1.unitsOwned), 1, savefile);
		fread(&data->p2.isItHuman, sizeof(data->p2.isItHuman), 1, savefile);
		fread(&data->p2.color, sizeof(data->p2.color), 1, savefile);
		fread(&data->p2.money, sizeof(data->p2.money), 1, savefile);
		fread(&data->p2.buildingsOwned, sizeof(data->p2.buildingsOwned), 1, savefile);
		fread(&data->p2.unitsOwned, sizeof(data->p2.unitsOwned), 1, savefile);
		fread(&data->p3.isItHuman, sizeof(data->p3.isItHuman), 1, savefile);
		fread(&data->p3.color, sizeof(data->p3.color), 1, savefile);
		fread(&data->p3.money, sizeof(data->p3.money), 1, savefile);
		fread(&data->p3.buildingsOwned, sizeof(data->p3.buildingsOwned), 1, savefile);
		fread(&data->p3.unitsOwned, sizeof(data->p3.unitsOwned), 1, savefile);
		fread(&data->p4.isItHuman, sizeof(data->p4.isItHuman), 1, savefile);
		fread(&data->p4.color, sizeof(data->p4.color), 1, savefile);
		fread(&data->p4.money, sizeof(data->p4.money), 1, savefile);
		fread(&data->p4.buildingsOwned, sizeof(data->p4.buildingsOwned), 1, savefile);
		fread(&data->p4.unitsOwned, sizeof(data->p4.unitsOwned), 1, savefile);
		
		printf("Loading unit data...\n");
		
		short arrayPos = 0;
		
		while (arrayPos < MAX_UNITS) {
			fread(&data->unitData[arrayPos].unitType, sizeof(data->unitData[arrayPos].unitType), 1, savefile);
			fread(&data->unitData[arrayPos].player, sizeof(data->unitData[arrayPos].player), 1, savefile);
			fread(&data->unitData[arrayPos].health, sizeof(data->unitData[arrayPos].health), 1, savefile);
			fread(&data->unitData[arrayPos].ammo1, sizeof(data->unitData[arrayPos].ammo1), 1, savefile);
			fread(&data->unitData[arrayPos].ammo2, sizeof(data->unitData[arrayPos].ammo2), 1, savefile);
			fread(&data->unitData[arrayPos].maxAmmo1, sizeof(data->unitData[arrayPos].maxAmmo1), 1, savefile);
			fread(&data->unitData[arrayPos].maxAmmo2, sizeof(data->unitData[arrayPos].maxAmmo2), 1, savefile);
			fread(&data->unitData[arrayPos].fuel, sizeof(data->unitData[arrayPos].fuel), 1, savefile);
			fread(&data->unitData[arrayPos].maxFuel, sizeof(data->unitData[arrayPos].maxFuel), 1, savefile);
			fread(&data->unitData[arrayPos].movement, sizeof(data->unitData[arrayPos].movement), 1, savefile);
			fread(&data->unitData[arrayPos].maxMovement, sizeof(data->unitData[arrayPos].maxMovement), 1, savefile);
			fread(&data->unitData[arrayPos].vision, sizeof(data->unitData[arrayPos].vision), 1, savefile);
			fread(&data->unitData[arrayPos].finished, sizeof(data->unitData[arrayPos].finished), 1, savefile);
			fread(&data->unitData[arrayPos].x, sizeof(data->unitData[arrayPos].x), 1, savefile);
			fread(&data->unitData[arrayPos].y, sizeof(data->unitData[arrayPos].y), 1, savefile);
			arrayPos++;
		}
		
		printf("Loading building data...\n");
		arrayPos = 0;
		while (arrayPos < MAX_BUILDINGS) {
			fread(&data->buildingData[arrayPos].buildingType, sizeof(data->buildingData[arrayPos].buildingType), 1, savefile);
			fread(&data->buildingData[arrayPos].player, sizeof(data->buildingData[arrayPos].player), 1, savefile);
			fread(&data->buildingData[arrayPos].health, sizeof(data->buildingData[arrayPos].health), 1, savefile);
			fread(&data->buildingData[arrayPos].x, sizeof(data->buildingData[arrayPos].x), 1, savefile);
			fread(&data->buildingData[arrayPos].y, sizeof(data->buildingData[arrayPos].y), 1, savefile);
			arrayPos++;
		}
		printf("Savefile successfully loaded.\n");
	}
	fclose(savefile);
	// free(filename);
}

void saveGameData (game *data) {
	FILE *savefile;
	
	char filename[100] = "savegame.twsave";
	
	printf("Type in a file name. End it with .twsave. ");
	gets(filename);
	
	savefile = fopen(filename, "wb");
	
	printf("Saving game properties...\n");
	
	fwrite(&data->turnNum, sizeof(data->turnNum), 1, savefile);
	fwrite(&data->numberOfPlayers, sizeof(data->numberOfPlayers), 1, savefile);
	fwrite(&data->whoseTurn, sizeof(data->whoseTurn), 1, savefile);
	fwrite(&data->cursor.x, sizeof(data->cursor.x), 1, savefile);
	fwrite(&data->cursor.y, sizeof(data->cursor.y), 1, savefile);
	fwrite(&data->interfaceMode, sizeof(data->interfaceMode), 1, savefile);
	fwrite(&data->drawMode, sizeof(data->drawMode), 1, savefile);
	fwrite(&data->attacker, sizeof(data->attacker), 1, savefile);
	// NO ERROR CODE, DON'T SAVE THAT
	
	printf("Saving map data...\n");
	
	short xPos = 0;
	short yPos = 0;
	
	while (yPos < MAP_HEIGHT) {
		while (xPos < MAP_WIDTH) {
			fwrite(&data->mapData[xPos][yPos], sizeof(unsigned char), 1, savefile);
			xPos++;
		}
		xPos = 0;
		yPos++;
	}
	
	printf("Saving player data...\n");
	
	fwrite(&data->p1.isItHuman, sizeof(data->p1.isItHuman), 1, savefile);
	fwrite(&data->p1.color, sizeof(data->p1.color), 1, savefile);
	fwrite(&data->p1.money, sizeof(data->p1.money), 1, savefile);
	fwrite(&data->p1.buildingsOwned, sizeof(data->p1.buildingsOwned), 1, savefile);
	fwrite(&data->p1.unitsOwned, sizeof(data->p1.unitsOwned), 1, savefile);
	fwrite(&data->p2.isItHuman, sizeof(data->p2.isItHuman), 1, savefile);
	fwrite(&data->p2.color, sizeof(data->p2.color), 1, savefile);
	fwrite(&data->p2.money, sizeof(data->p2.money), 1, savefile);
	fwrite(&data->p2.buildingsOwned, sizeof(data->p2.buildingsOwned), 1, savefile);
	fwrite(&data->p2.unitsOwned, sizeof(data->p2.unitsOwned), 1, savefile);
	fwrite(&data->p3.isItHuman, sizeof(data->p3.isItHuman), 1, savefile);
	fwrite(&data->p3.color, sizeof(data->p3.color), 1, savefile);
	fwrite(&data->p3.money, sizeof(data->p3.money), 1, savefile);
	fwrite(&data->p3.buildingsOwned, sizeof(data->p3.buildingsOwned), 1, savefile);
	fwrite(&data->p3.unitsOwned, sizeof(data->p3.unitsOwned), 1, savefile);
	fwrite(&data->p4.isItHuman, sizeof(data->p4.isItHuman), 1, savefile);
	fwrite(&data->p4.color, sizeof(data->p4.color), 1, savefile);
	fwrite(&data->p4.money, sizeof(data->p4.money), 1, savefile);
	fwrite(&data->p4.buildingsOwned, sizeof(data->p4.buildingsOwned), 1, savefile);
	fwrite(&data->p4.unitsOwned, sizeof(data->p4.unitsOwned), 1, savefile);
	
	printf("Saving unit data...\n");
	
	short arrayPos = 0;
	
	while (arrayPos < MAX_UNITS) {
		fwrite(&data->unitData[arrayPos].unitType, sizeof(data->unitData[arrayPos].unitType), 1, savefile);
		fwrite(&data->unitData[arrayPos].player, sizeof(data->unitData[arrayPos].player), 1, savefile);
		fwrite(&data->unitData[arrayPos].health, sizeof(data->unitData[arrayPos].health), 1, savefile);
		fwrite(&data->unitData[arrayPos].ammo1, sizeof(data->unitData[arrayPos].ammo1), 1, savefile);
		fwrite(&data->unitData[arrayPos].ammo2, sizeof(data->unitData[arrayPos].ammo2), 1, savefile);
		fwrite(&data->unitData[arrayPos].maxAmmo1, sizeof(data->unitData[arrayPos].maxAmmo1), 1, savefile);
		fwrite(&data->unitData[arrayPos].maxAmmo2, sizeof(data->unitData[arrayPos].maxAmmo2), 1, savefile);
		fwrite(&data->unitData[arrayPos].fuel, sizeof(data->unitData[arrayPos].fuel), 1, savefile);
		fwrite(&data->unitData[arrayPos].maxFuel, sizeof(data->unitData[arrayPos].maxFuel), 1, savefile);
		fwrite(&data->unitData[arrayPos].movement, sizeof(data->unitData[arrayPos].movement), 1, savefile);
		fwrite(&data->unitData[arrayPos].maxMovement, sizeof(data->unitData[arrayPos].maxMovement), 1, savefile);
		fwrite(&data->unitData[arrayPos].vision, sizeof(data->unitData[arrayPos].vision), 1, savefile);
		fwrite(&data->unitData[arrayPos].finished, sizeof(data->unitData[arrayPos].finished), 1, savefile);
		fwrite(&data->unitData[arrayPos].x, sizeof(data->unitData[arrayPos].x), 1, savefile);
		fwrite(&data->unitData[arrayPos].y, sizeof(data->unitData[arrayPos].y), 1, savefile);
		arrayPos++;
	}
	
	printf("Saving building data...\n");
	arrayPos = 0;
	while (arrayPos < MAX_BUILDINGS) {
		fwrite(&data->buildingData[arrayPos].buildingType, sizeof(data->buildingData[arrayPos].buildingType), 1, savefile);
		fwrite(&data->buildingData[arrayPos].player, sizeof(data->buildingData[arrayPos].player), 1, savefile);
		fwrite(&data->buildingData[arrayPos].health, sizeof(data->buildingData[arrayPos].health), 1, savefile);
		fwrite(&data->buildingData[arrayPos].x, sizeof(data->buildingData[arrayPos].x), 1, savefile);
		fwrite(&data->buildingData[arrayPos].y, sizeof(data->buildingData[arrayPos].y), 1, savefile);
		arrayPos++;
	}
	
	fclose(savefile);
	// free(filename);
	printf("Savefile successfully written to %s.\n", filename);
}