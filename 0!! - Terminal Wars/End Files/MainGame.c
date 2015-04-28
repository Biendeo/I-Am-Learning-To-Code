#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// These headers are redundant when they're already called. An IFDEF
// needs to be used.
#include "Defines.h"
#include "MainGame.h"
#include "FileIO.h"

game *buildGame () {
	// I might want to separate this into another function, and call it
	// once I've gotten the map dimensions, as they might be variable
	// later on.
	game *data = malloc(sizeof(game));
	char settings[5];
	// CURRENTLY UNUSED
	//char inputChar;
	char *inputString;
	FILE *file;
	printf("Type 0 to play a new game, or 1 to load a game. ");
	settings[0] = getchar();
	
	if (settings[0] == '0') {
		printf("Enter what a map file. (or leave blank for default). ");
		// I don't know why, it'll automatically ask for the next one
		// unless I double up on this.
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
		
		printf("This map supports 2 players. How many are human? ");
		settings[1] = getchar();
		
		if (settings[1] == '0') {
			data->p1.isItHuman = BOT;
			data->p2.isItHuman = BOT;
		} else if (settings[1] == '1') {
			data->p1.isItHuman = HUMAN;
			data->p2.isItHuman = BOT;
		} else if (settings[1] == '2') {
			data->p1.isItHuman = HUMAN;
			data->p2.isItHuman = HUMAN;
		} else {
			printf("Error BAD_SETUP_INPUT\n");
			ERROR_CODE = BAD_SETUP_INPUT;
		}
		
		initialiseGame (data);
	}
	
	else if (settings[0] == '1') {
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
	}
	else {
		printf("Error BAD_SETUP_INPUT\n");
		ERROR_CODE = BAD_SETUP_INPUT;
	}
	return data;
}

void initialiseGame (game *data) {
	/// Most of the default properties are given values.
	ERROR_CODE = ALL_GOOD;
	data->turnNum = 1;
	data->numberOfPlayers = 2;
	data->whoseTurn = 1;
	data->cursor.x = 0;
	data->cursor.y = 0;
	data->drawMode = DRAWMODE_UNITS;
	
	data->p1.color = TEAM_RED;
	data->p1.money = STARTING_MONEY;
	data->p1.buildingsOwned = 0;
	data->p1.unitsOwned = 0;
	
	data->p2.color = TEAM_BLUE;
	data->p2.money = STARTING_MONEY;
	data->p2.buildingsOwned = 0;
	data->p2.unitsOwned = 0;
	
	data->p3.color = TEAM_GREEN;
	data->p3.money = STARTING_MONEY;
	data->p3.buildingsOwned = 0;
	data->p3.unitsOwned = 0;
	
	data->p4.color = TEAM_YELLOW;
	data->p4.money = STARTING_MONEY;
	data->p4.buildingsOwned = 0;
	data->p4.unitsOwned = 0;
	
	/// This will scan the map for specific data.
	scanMap (data);
	
	checkInitialiseGame (data);
}

void scanMap (game *data) {
	short x = 0;
	short y = 0;
	short arrayPos = 0;
	/// Now we flush the unit data.
	while (arrayPos < MAX_UNITS) {
		data->unitData[arrayPos].unitType = 0;
		data->unitData[arrayPos].player = 0;
		data->unitData[arrayPos].health = 0;
		data->unitData[arrayPos].ammo1 = 0;
		data->unitData[arrayPos].ammo2 = 0;
		data->unitData[arrayPos].fuel = 0;
		data->unitData[arrayPos].movement = 0;
		data->unitData[arrayPos].x = 0;
		data->unitData[arrayPos].y = 0;
		arrayPos++;
	}
	
	arrayPos = 0;
	/// We also flush the building data.
	while (arrayPos < MAX_BUILDINGS) {
		data->buildingData[arrayPos].buildingType = 0;
		data->buildingData[arrayPos].player = 0;
		data->buildingData[arrayPos].x = 0;
		data->buildingData[arrayPos].y = 0;
		arrayPos++;
	}
	
	arrayPos = 0;
	
	/// Now, the program will scan for buildings and store those.
	while (y < MAP_HEIGHT) {
		while (x < MAP_WIDTH) {
			if (data->mapData[x][y] < PLAIN) {
				data->buildingData[arrayPos].buildingType = ((data->mapData[x][y]) % 10);
				data->buildingData[arrayPos].player = ((data->mapData[x][y]) / 10);
				data->buildingData[arrayPos].x = x;
				data->buildingData[arrayPos].y = y;
				
				if (data->buildingData[arrayPos].player == TEAM_RED) {
					data->p1.buildingsOwned++;
				} else if (data->buildingData[arrayPos].player == TEAM_BLUE) {
					data->p2.buildingsOwned++;
				} else if (data->buildingData[arrayPos].player == TEAM_GREEN) {
					data->p3.buildingsOwned++;
				} else if (data->buildingData[arrayPos].player == TEAM_YELLOW) {
					data->p4.buildingsOwned++;
				}
				arrayPos++;
			}
			x++;
		}
		x = 0;
		y++;
	}

}

void attackUnit (game *data, short attacker, short defender) {
	
}

char tileMovementGetter (game *data, short x, short y, char movementType) {
	char tileType = data->mapData[x][y];
	char tileMovement = 0;
	
	if (movementType == MOVE_INFANTRY) {
		if (tileType < PLAIN) {
			if (tileType % 10 == 1) {
				tileMovement = MOVE_HQ_INFANTRY;
			} else if (tileType % 10 == 2) {
				tileMovement = MOVE_CITY_INFANTRY;
			} else if (tileType % 10 == 3) {
				tileMovement = MOVE_BASE_INFANTRY;
			} else if (tileType % 10 == 4) {
				tileMovement = MOVE_AIRPORT_INFANTRY;
			} else if (tileType % 10 == 5) {
				tileMovement = MOVE_PORT_INFANTRY;
			}
		} else if (tileType == PLAIN) {
			tileMovement = MOVE_PLAIN_INFANTRY;
		} else if (tileType == ROAD) {
			tileMovement = MOVE_ROAD_INFANTRY;
		} else if (tileType == SEA) {
			tileMovement = MOVE_SEA_INFANTRY;
		} else if (tileType == RIVER) {
			tileMovement = MOVE_RIVER_INFANTRY;
		} else if (tileType == WOOD) {
			tileMovement = MOVE_WOOD_INFANTRY;
		} else if (tileType == MOUNTAIN) {
			tileMovement = MOVE_MOUNTAIN_INFANTRY;
		} else if (tileType == BRIDGE) {
			tileMovement = MOVE_BRIDGE_INFANTRY;
		} else if (tileType == SHOAL) {
			tileMovement = MOVE_SHOAL_INFANTRY;
		} else if (tileType == REEF) {
			tileMovement = MOVE_REEF_INFANTRY;
		}
	}
	else if (movementType == MOVE_MECH) {
		if (tileType < PLAIN) {
			if (tileType % 10 == 1) {
				tileMovement = MOVE_HQ_MECH;
			} else if (tileType % 10 == 2) {
				tileMovement = MOVE_CITY_MECH;
			} else if (tileType % 10 == 3) {
				tileMovement = MOVE_BASE_MECH;
			} else if (tileType % 10 == 4) {
				tileMovement = MOVE_AIRPORT_MECH;
			} else if (tileType % 10 == 5) {
				tileMovement = MOVE_PORT_MECH;
			}
		} else if (tileType == PLAIN) {
			tileMovement = MOVE_PLAIN_MECH;
		} else if (tileType == ROAD) {
			tileMovement = MOVE_ROAD_MECH;
		} else if (tileType == SEA) {
			tileMovement = MOVE_SEA_MECH;
		} else if (tileType == RIVER) {
			tileMovement = MOVE_RIVER_MECH;
		} else if (tileType == WOOD) {
			tileMovement = MOVE_WOOD_MECH;
		} else if (tileType == MOUNTAIN) {
			tileMovement = MOVE_MOUNTAIN_MECH;
		} else if (tileType == BRIDGE) {
			tileMovement = MOVE_BRIDGE_MECH;
		} else if (tileType == SHOAL) {
			tileMovement = MOVE_SHOAL_MECH;
		} else if (tileType == REEF) {
			tileMovement = MOVE_REEF_MECH;
		}
	}
	else if (movementType == MOVE_TIRES) {
		if (tileType < PLAIN) {
			if (tileType % 10 == 1) {
				tileMovement = MOVE_HQ_TIRES;
			} else if (tileType % 10 == 2) {
				tileMovement = MOVE_CITY_TIRES;
			} else if (tileType % 10 == 3) {
				tileMovement = MOVE_BASE_TIRES;
			} else if (tileType % 10 == 4) {
				tileMovement = MOVE_AIRPORT_TIRES;
			} else if (tileType % 10 == 5) {
				tileMovement = MOVE_PORT_TIRES;
			}
		} else if (tileType == PLAIN) {
			tileMovement = MOVE_PLAIN_TIRES;
		} else if (tileType == ROAD) {
			tileMovement = MOVE_ROAD_TIRES;
		} else if (tileType == SEA) {
			tileMovement = MOVE_SEA_TIRES;
		} else if (tileType == RIVER) {
			tileMovement = MOVE_RIVER_TIRES;
		} else if (tileType == WOOD) {
			tileMovement = MOVE_WOOD_TIRES;
		} else if (tileType == MOUNTAIN) {
			tileMovement = MOVE_MOUNTAIN_TIRES;
		} else if (tileType == BRIDGE) {
			tileMovement = MOVE_BRIDGE_TIRES;
		} else if (tileType == SHOAL) {
			tileMovement = MOVE_SHOAL_TIRES;
		} else if (tileType == REEF) {
			tileMovement = MOVE_REEF_TIRES;
		}
	}
	else if (movementType == MOVE_TREAD) {
		if (tileType < PLAIN) {
			if (tileType % 10 == 1) {
				tileMovement = MOVE_HQ_TREAD;
			} else if (tileType % 10 == 2) {
				tileMovement = MOVE_CITY_TREAD;
			} else if (tileType % 10 == 3) {
				tileMovement = MOVE_BASE_TREAD;
			} else if (tileType % 10 == 4) {
				tileMovement = MOVE_AIRPORT_TREAD;
			} else if (tileType % 10 == 5) {
				tileMovement = MOVE_PORT_TREAD;
			}
		} else if (tileType == PLAIN) {
			tileMovement = MOVE_PLAIN_TREAD;
		} else if (tileType == ROAD) {
			tileMovement = MOVE_ROAD_TREAD;
		} else if (tileType == SEA) {
			tileMovement = MOVE_SEA_TREAD;
		} else if (tileType == RIVER) {
			tileMovement = MOVE_RIVER_TREAD;
		} else if (tileType == WOOD) {
			tileMovement = MOVE_WOOD_TREAD;
		} else if (tileType == MOUNTAIN) {
			tileMovement = MOVE_MOUNTAIN_TREAD;
		} else if (tileType == BRIDGE) {
			tileMovement = MOVE_BRIDGE_TREAD;
		} else if (tileType == SHOAL) {
			tileMovement = MOVE_SHOAL_TREAD;
		} else if (tileType == REEF) {
			tileMovement = MOVE_REEF_TREAD;
		}
	}
	else if (movementType == MOVE_AIR) {
		if (tileType < PLAIN) {
			if (tileType % 10 == 1) {
				tileMovement = MOVE_HQ_AIR;
			} else if (tileType % 10 == 2) {
				tileMovement = MOVE_CITY_AIR;
			} else if (tileType % 10 == 3) {
				tileMovement = MOVE_BASE_AIR;
			} else if (tileType % 10 == 4) {
				tileMovement = MOVE_AIRPORT_AIR;
			} else if (tileType % 10 == 5) {
				tileMovement = MOVE_PORT_AIR;
			}
		} else if (tileType == PLAIN) {
			tileMovement = MOVE_PLAIN_AIR;
		} else if (tileType == ROAD) {
			tileMovement = MOVE_ROAD_AIR;
		} else if (tileType == SEA) {
			tileMovement = MOVE_SEA_AIR;
		} else if (tileType == RIVER) {
			tileMovement = MOVE_RIVER_AIR;
		} else if (tileType == WOOD) {
			tileMovement = MOVE_WOOD_AIR;
		} else if (tileType == MOUNTAIN) {
			tileMovement = MOVE_MOUNTAIN_AIR;
		} else if (tileType == BRIDGE) {
			tileMovement = MOVE_BRIDGE_AIR;
		} else if (tileType == SHOAL) {
			tileMovement = MOVE_SHOAL_AIR;
		} else if (tileType == REEF) {
			tileMovement = MOVE_REEF_AIR;
		}
	}
	else if (movementType == MOVE_SHIP) {
		if (tileType < PLAIN) {
			if (tileType % 10 == 1) {
				tileMovement = MOVE_HQ_SHIP;
			} else if (tileType % 10 == 2) {
				tileMovement = MOVE_CITY_SHIP;
			} else if (tileType % 10 == 3) {
				tileMovement = MOVE_BASE_SHIP;
			} else if (tileType % 10 == 4) {
				tileMovement = MOVE_AIRPORT_SHIP;
			} else if (tileType % 10 == 5) {
				tileMovement = MOVE_PORT_SHIP;
			}
		} else if (tileType == PLAIN) {
			tileMovement = MOVE_PLAIN_SHIP;
		} else if (tileType == ROAD) {
			tileMovement = MOVE_ROAD_SHIP;
		} else if (tileType == SEA) {
			tileMovement = MOVE_SEA_SHIP;
		} else if (tileType == RIVER) {
			tileMovement = MOVE_RIVER_SHIP;
		} else if (tileType == WOOD) {
			tileMovement = MOVE_WOOD_SHIP;
		} else if (tileType == MOUNTAIN) {
			tileMovement = MOVE_MOUNTAIN_SHIP;
		} else if (tileType == BRIDGE) {
			tileMovement = MOVE_BRIDGE_SHIP;
		} else if (tileType == SHOAL) {
			tileMovement = MOVE_SHOAL_SHIP;
		} else if (tileType == REEF) {
			tileMovement = MOVE_REEF_SHIP;
		}
	}
	else if (movementType == MOVE_CARRIER) {
		if (tileType < PLAIN) {
			if (tileType % 10 == 1) {
				tileMovement = MOVE_HQ_CARRIER;
			} else if (tileType % 10 == 2) {
				tileMovement = MOVE_CITY_CARRIER;
			} else if (tileType % 10 == 3) {
				tileMovement = MOVE_BASE_CARRIER;
			} else if (tileType % 10 == 4) {
				tileMovement = MOVE_AIRPORT_CARRIER;
			} else if (tileType % 10 == 5) {
				tileMovement = MOVE_PORT_CARRIER;
			}
		} else if (tileType == PLAIN) {
			tileMovement = MOVE_PLAIN_CARRIER;
		} else if (tileType == ROAD) {
			tileMovement = MOVE_ROAD_CARRIER;
		} else if (tileType == SEA) {
			tileMovement = MOVE_SEA_CARRIER;
		} else if (tileType == RIVER) {
			tileMovement = MOVE_RIVER_CARRIER;
		} else if (tileType == WOOD) {
			tileMovement = MOVE_WOOD_CARRIER;
		} else if (tileType == MOUNTAIN) {
			tileMovement = MOVE_MOUNTAIN_CARRIER;
		} else if (tileType == BRIDGE) {
			tileMovement = MOVE_BRIDGE_CARRIER;
		} else if (tileType == SHOAL) {
			tileMovement = MOVE_SHOAL_CARRIER;
		} else if (tileType == REEF) {
			tileMovement = MOVE_REEF_CARRIER;
		}
	}
	
	return tileMovement;
}

char tileDefenseGetter (game *data, short x, short y) {
	
}

unsigned char baseDamageGetter (game *data, short attacker, short defender) {
	
}

void checkInitialiseGame (game *data) {
	// Develop this fully later.
	if (data->p1.color != TEAM_RED) {
		printf("Error TEST_FAILED data->p1.color != TEAM_RED (%d)\n", data->p1.color);
		ERROR_CODE = TEST_FAILED;
		getkey();
	}
	if (data->p1.money != STARTING_MONEY) {
		printf("Error TEST_FAILED data->p1.money != STARTING_MONEY (%d)\n", data->p1.money);
		ERROR_CODE = TEST_FAILED;
		getkey();
	}
	
	// This is a personal test to see if the data truly is correct.
	// Custom maps will probably fail this right now, but I can't check it.
	if (data->p1.buildingsOwned != 6) {
		printf("Error TEST_FAILED data->p1.buidlingsOwned != 6 (%d)\n", data->p1.buildingsOwned);
		ERROR_CODE = TEST_FAILED;
		getkey();
	}
	if (data->p2.buildingsOwned != 5) {
		printf("Error TEST_FAILED data->p2.buidlingsOwned != 5 (%d)\n", data->p2.buildingsOwned);
		ERROR_CODE = TEST_FAILED;
		getkey();
	}
	if (ERROR_CODE == ALL_GOOD) {
		printf("All tests passed. :)\n");
	}
}



void freeGame (game *data) {
	printf("Program ended in state %d\n", ERROR_CODE);
	free(data);
}