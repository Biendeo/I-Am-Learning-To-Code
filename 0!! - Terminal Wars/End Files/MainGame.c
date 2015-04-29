#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

// These headers are redundant when they're already called. An IFDEF
// needs to be used.
#include "Defines.h"
#include "MainGame.h"
#include "FileIO.h"

/// This function
game *buildGame () {
	// I might want to separate this into another function, and call it
	// once I've gotten the map dimensions, as they might be variable
	// later on.
	game *data = malloc(sizeof(game));
	
	/// CURRENTLY THIS DOESN'T WORK. NO CLUE WHY.
	/// Right now, it just sticks with the default. It does its job
	/// for now, but obviously that's not good.
	/*
	char settings[2];
	char *inputString;
	FILE *file;
	printf("Type 0 to play a new game, or 1 to load a game. ");
	settings[0] = getchar();
	
	if (settings[0] == '0') {
		printf("Enter what a map file. (or leave blank for default). ");
		// The scan stopped working, so currently it defaults to this
		// map.
		
		if (NULL == NULL) {
			file = fopen("Map Files/SpannIsland.txt", "r");
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
			// When it's ready, uncomment this.
			//loadGame (data, file);
		}
		
		fclose(file);
	}
	else {
		printf("Error BAD_SETUP_INPUT\n");
		ERROR_CODE = BAD_SETUP_INPUT;
	}*/
	loadMapDefaultData(data);
	initialiseGame(data);
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
	
	/// This will test to see if everything initialised (also great for
	/// debugging anything).
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

void modeSelect (game *data) {
	
}

void modeMove (game *data) {
	
}

void modeAttack (game *data) {
	
}

void modeMenuField (game *data) {
	
}

void modeMenuUnit (game *data) {
	
}

void freeGame (game *data) {
	printf("Program ended in state %d\n", ERROR_CODE);
	free(data);
}

void moveUnit (game *data, short mover, char direction) {
	
}

void attackUnit (game *data, short attacker, short defender) {
	char attackRandom = rand() % 10;
	
	/// The base damage and defense are grabbed.
	// I'll do an additional test for this before this function gets
	// called. If this returns 0, then I won't even enter this function.
	unsigned char baseDamage = baseDamageGetter (data, data->unitData[attacker].unitType, data->unitData[defender].unitType);
	unsigned char defenseRating = tileDefenseGetter (data, data->unitData[defender].x, data->unitData[defender].y);
	
	/// Now, the damage is calculated. The formula is a bit messy.
	/// Basically, a number 
	float endDamage;
	endDamage = roundf((baseDamage + attackRandom) / 100) * (data->unitData[attacker].health / 10) * ((100 - (defenseRating * data->unitData[defender].health)) / 100);
	
	/// The end health is applied, and the value is rounded (as health
	/// is only one decimal place).
	data->unitData[defender].health -= endDamage;
	
	/// If the opposing unit is still alive, and it can counter-attack,
	/// then it does the same calculation but accessing different stuff.
	/// Otherwise, it's dead, and we delete it.
	
	if (data->unitData[defender].health > 0) {
		// When making canItCounter, just get the values from some
		// functions, so it should be large itself.
		if (canItCounter(data, attacker, defender) == YES) {
			attackRandom = rand() % 10;
			
			baseDamage = baseDamageGetter (data, data->unitData[defender].unitType, data->unitData[attacker].unitType);
			defenseRating = tileDefenseGetter (data, data->unitData[attacker].x, data->unitData[attacker].y);
			
			endDamage = roundf((baseDamage / 100) + attackRandom) * (data->unitData[defender].health / 10) * ((100 - (defenseRating * data->unitData[attacker].health)) / 100);
			data->unitData[attacker].health -= endDamage;
			
			if (data->unitData[attacker].health < 0) {
				deleteUnit(data, attacker);
			}
		}
	} else {
		deleteUnit(data, defender);
	}
	
	/// Attacking is always the last thing a unit does each turn.
	data->unitData[attacker].finished = YES;
}

void createUnit (game *data, short x, short y, char unitType, char player) {
	
}

void deleteUnit (game *data, short unitPos) {
	
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
	char tileType = data->mapData[x][y];
	char tileDefense = 0;
	if (tileType < PLAIN) {
		if (tileType % 10 == 1) {
			tileDefense = DEFENSE_HQ;
		} else if (tileType % 10 == 2) {
			tileDefense = DEFENSE_CITY;
		} else if (tileType % 10 == 3) {
			tileDefense = DEFENSE_BASE;
		} else if (tileType % 10 == 4) {
			tileDefense = DEFENSE_AIRPORT;
		} else if (tileType % 10 == 5) {
			tileDefense = DEFENSE_PORT;
		}
	} else if (tileType == PLAIN) {
		tileDefense = DEFENSE_PLAIN;
	} else if (tileType == ROAD) {
		tileDefense = DEFENSE_ROAD;
	} else if (tileType == SEA) {
		tileDefense = DEFENSE_SEA;
	} else if (tileType == RIVER) {
		tileDefense = DEFENSE_RIVER;
	} else if (tileType == WOOD) {
		tileDefense = DEFENSE_WOOD;
	} else if (tileType == MOUNTAIN) {
		tileDefense = DEFENSE_MOUNTAIN;
	} else if (tileType == BRIDGE) {
		tileDefense = DEFENSE_BRIDGE;
	} else if (tileType == SHOAL) {
		tileDefense = DEFENSE_SHOAL;
	} else if (tileType == REEF) {
		tileDefense = DEFENSE_REEF;
	}
	return tileDefense;
}

unsigned char baseDamageGetter (game *data, short attacker, short defender) {
	unsigned char baseDamage = 0;
	
	return baseDamage;
}

char minimumRangeGetter (game *data, short unitPos) {
	char minimumRange = 0;
	/// This variable is just so that the subsequent code is a bit more concise.
	char unitType = data->unitData[unitPos].unitType;
	
	if (unitType == INFANTRY) {
		minimumRange = RANGE_MIN_INFANTRY;
	} else if (unitType == MECH) {
		minimumRange = RANGE_MIN_MECH;
	} else if (unitType == RECON) {
		minimumRange = RANGE_MIN_RECON;
	} else if (unitType == TANK) {
		minimumRange = RANGE_MIN_TANK;
	} else if (unitType == MD_TANK) {
		minimumRange = RANGE_MIN_MD_TANK;
	} else if (unitType == NEOTANK) {
		minimumRange = RANGE_MIN_NEOTANK;
	} else if (unitType == MEGATANK) {
		minimumRange = RANGE_MIN_MEGATANK;
	} else if (unitType == APC) {
		minimumRange = RANGE_MIN_APC;
	} else if (unitType == ARTILLERY) {
		minimumRange = RANGE_MIN_ARTILLERY;
	} else if (unitType == ROCKETS) {
		minimumRange = RANGE_MIN_ROCKETS;
	} else if (unitType == ANTI_AIR) {
		minimumRange = RANGE_MIN_ANTI_AIR;
	} else if (unitType == MISSILES) {
		minimumRange = RANGE_MIN_MISSILES;
	} else if (unitType == BATT_COP) {
		minimumRange = RANGE_MIN_BATT_COP;
	} else if (unitType == TRAN_COP) {
		minimumRange = RANGE_MIN_TRAN_COP;
	} else if (unitType == FIGHTER) {
		minimumRange = RANGE_MIN_FIGHTER;
	} else if (unitType == BOMBER) {
		minimumRange = RANGE_MIN_BOMBER;
	} else if (unitType == STEALTH) {
		minimumRange = RANGE_MIN_STEALTH;
	} else if (unitType == LANDER) {
		minimumRange = RANGE_MIN_LANDER;
	} else if (unitType == CRUISER) {
		minimumRange = RANGE_MIN_CRUISER;
	} else if (unitType == SUB) {
		minimumRange = RANGE_MIN_SUB;
	} else if (unitType == BATT_SHIP) {
		minimumRange = RANGE_MIN_BATT_SHIP;
	} else if (unitType == CARRIER) {
		minimumRange = RANGE_MIN_CARRIER;
	}
	
	return minimumRange;
}

char maximumRangeGetter (game *data, short unitPos) {
	char maximumRange = 0;
	/// This variable is just so that the subsequent code is a bit more concise.
	char unitType = data->unitData[unitPos].unitType;
	
	if (unitType == INFANTRY) {
		maximumRange = RANGE_MAX_INFANTRY;
	} else if (unitType == MECH) {
		maximumRange = RANGE_MAX_MECH;
	} else if (unitType == RECON) {
		maximumRange = RANGE_MAX_RECON;
	} else if (unitType == TANK) {
		maximumRange = RANGE_MAX_TANK;
	} else if (unitType == MD_TANK) {
		maximumRange = RANGE_MAX_MD_TANK;
	} else if (unitType == NEOTANK) {
		maximumRange = RANGE_MAX_NEOTANK;
	} else if (unitType == MEGATANK) {
		maximumRange = RANGE_MAX_MEGATANK;
	} else if (unitType == APC) {
		maximumRange = RANGE_MAX_APC;
	} else if (unitType == ARTILLERY) {
		maximumRange = RANGE_MAX_ARTILLERY;
	} else if (unitType == ROCKETS) {
		maximumRange = RANGE_MAX_ROCKETS;
	} else if (unitType == ANTI_AIR) {
		maximumRange = RANGE_MAX_ANTI_AIR;
	} else if (unitType == MISSILES) {
		maximumRange = RANGE_MAX_MISSILES;
	} else if (unitType == BATT_COP) {
		maximumRange = RANGE_MAX_BATT_COP;
	} else if (unitType == TRAN_COP) {
		maximumRange = RANGE_MAX_TRAN_COP;
	} else if (unitType == FIGHTER) {
		maximumRange = RANGE_MAX_FIGHTER;
	} else if (unitType == BOMBER) {
		maximumRange = RANGE_MAX_BOMBER;
	} else if (unitType == STEALTH) {
		maximumRange = RANGE_MAX_STEALTH;
	} else if (unitType == LANDER) {
		maximumRange = RANGE_MAX_LANDER;
	} else if (unitType == CRUISER) {
		maximumRange = RANGE_MAX_CRUISER;
	} else if (unitType == SUB) {
		maximumRange = RANGE_MAX_SUB;
	} else if (unitType == BATT_SHIP) {
		maximumRange = RANGE_MAX_BATT_SHIP;
	} else if (unitType == CARRIER) {
		maximumRange = RANGE_MAX_CARRIER;
	}
	
	return maximumRange;
}

char whichWeapon (game *data, short attacker, short defender) {
	/// This will only change if it CAN attack something.
	char whichWeapon = NO;
	
	return whichWeapon;
}

char canItCounter (game *data, short attacker, short defender) {
	char canItCounter = NO;
	if ((minimumRangeGetter(data, defender) == 1) && (maximumRangeGetter(data, defender) == 1)) {
		if (baseDamageGetter(data, defender, attacker) != 0) {
			canItCounter = YES;
		}
	}
	
	return canItCounter;
}

void checkInitialiseGame (game *data) {
	// Develop this fully later.
	if (data->p1.color != TEAM_RED) {
		printf("Error TEST_FAILED data->p1.color != TEAM_RED (%d)\n", data->p1.color);
		ERROR_CODE = TEST_FAILED;
		getchar();
	}
	if (data->p1.money != STARTING_MONEY) {
		printf("Error TEST_FAILED data->p1.money != STARTING_MONEY (%d)\n", data->p1.money);
		ERROR_CODE = TEST_FAILED;
		getchar();
	}
	
	// This is a personal test to see if the data truly is correct.
	// This works for the default map.
	// Custom maps will probably fail this right now, but I can't check it.
	if (data->p1.buildingsOwned != 6) {
		printf("Error TEST_FAILED data->p1.buidlingsOwned != 6 (%d)\n", data->p1.buildingsOwned);
		ERROR_CODE = TEST_FAILED;
		getchar();
	}
	if (data->p2.buildingsOwned != 5) {
		printf("Error TEST_FAILED data->p2.buidlingsOwned != 5 (%d)\n", data->p2.buildingsOwned);
		ERROR_CODE = TEST_FAILED;
		getchar();
	}
	
	if (ERROR_CODE == ALL_GOOD) {
		printf("All tests passed. :)\n");
		getchar();
	}
}