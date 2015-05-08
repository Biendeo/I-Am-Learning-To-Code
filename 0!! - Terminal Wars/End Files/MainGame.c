#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "Defines.h"
#include "MainGame.h"
#include "FileIO.h"
#include "DrawingUI.h"

// THIS BIT IS HERE PURELY BECAUSE I CAN'T GET RLUTIL.H TO BE IN
// MULTIPLE C FILES AT THE SAME TIME.
// I'm trying to get it to work, but no luck. This is here in the
// meantime.
#define KEY_ESCAPE  0
#define KEY_ENTER   1
#define KEY_SPACE   32

#define KEY_INSERT  2
#define KEY_HOME    3
#define KEY_PGUP    4
#define KEY_DELETE  5
#define KEY_END     6
#define KEY_PGDOWN  7

#define KEY_UP      14
#define KEY_DOWN    15
#define KEY_LEFT    16
#define KEY_RIGHT   17

#define KEY_F1      18
#define KEY_F2      19
#define KEY_F3      20
#define KEY_F4      21
#define KEY_F5      22
#define KEY_F6      23
#define KEY_F7      24
#define KEY_F8      25
#define KEY_F9      26
#define KEY_F10     27
#define KEY_F11     28
#define KEY_F12     29

#define KEY_NUMDEL  30
#define KEY_NUMPAD0 31
#define KEY_NUMPAD1 127
#define KEY_NUMPAD2 128
#define KEY_NUMPAD3 129
#define KEY_NUMPAD4 130
#define KEY_NUMPAD5 131
#define KEY_NUMPAD6 132
#define KEY_NUMPAD7 133
#define KEY_NUMPAD8 134
#define KEY_NUMPAD9 135

/// This function creates the game and asks for some settings.
/// This determines what map to load, how many players are human, or
/// what save game to load.
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

/// This function gives many of the intial game values.
void initialiseGame (game *data) {
	/// Most of the default properties are given values.
	ERROR_CODE = ALL_GOOD;
	data->turnNum = 1;
	data->numberOfPlayers = 2;
	data->whoseTurn = 0;
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
	
	// This is just a bit of example setup to get the game started.
	// It's purely so that I can debug stuff right now.
	createUnit(data, 4, 3, INFANTRY, TEAM_RED);
	createUnit(data, 8, 6, MECH, TEAM_RED);
	createUnit(data, 5, 3, ARTILLERY, TEAM_BLUE);
	createUnit(data, 9, 6, MEGATANK, TEAM_BLUE);
	createUnit(data, 11, 3, TANK, TEAM_BLUE);
	createUnit(data, 1, 10, MECH, TEAM_GREEN);
	createUnit(data, 12, 6, APC, TEAM_YELLOW);
	createUnit(data, 10, 10, NEOTANK, TEAM_YELLOW);
	// This demonstrates how deleting units works.
	deleteUnit(data, 4);
	// And creating new units after that.
	createUnit(data, 2, 2, BATT_COP, TEAM_GREEN);
	
	/// Then, a new turn is performed, which moves to player 1.
	endTurn(data);
}

/// This function cleans some of the memory values and scans the map
/// for buildings, then assigns them to the player values.
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
		data->buildingData[arrayPos].health = 0;
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
				data->buildingData[arrayPos].health = 20;
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

// Merge the test game into these functions when everything is ready.
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

/// This function unallocates the game from memory, and reports an
/// error if one occurred.
void freeGame (game *data) {
	printf("Program ended in state %d\n", ERROR_CODE);
	free(data);
}

/// This function moves the cursor based on keypresses.
void moveCursor (game *data, int keyPress) {
	if ((keyPress == UP) && (data->cursor.y > 0)) {
		data->cursor.y--;
	} else if ((keyPress == DOWN) && (data->cursor.y < MAP_HEIGHT - 1)) {
		data->cursor.y++;
	} else if ((keyPress == LEFT) && (data->cursor.x > 0)) {
		data->cursor.x--;
	} else if ((keyPress == RIGHT) && (data->cursor.x < MAP_WIDTH - 1)) {
		data->cursor.x++;
	}
}

/// This function moves a unit when in move mode based on keypresses.
void moveUnit (game *data, short mover, int keyPress) {
	short x = data->cursor.x;
	short y = data->cursor.y;
	short movementType = unitMovementTypeGetter(data, mover);
	
	if (keyPress == UP) {
		if (validMoveChecker(data, mover, UP) == YES) {
			data->cursor.y--;
			data->unitData[mover].y--;
			data->unitData[mover].movement -= tileMovementGetter(data, x, y - 1, movementType);
			data->unitData[mover].fuel -= tileMovementGetter(data, x, y - 1, movementType);
		}
	} else if (keyPress == DOWN) {
		if (validMoveChecker(data, mover, DOWN) == YES) {
			data->cursor.y++;
			data->unitData[mover].y++;
			data->unitData[mover].movement -= tileMovementGetter(data, x, y + 1, movementType);
			data->unitData[mover].fuel -= tileMovementGetter(data, x, y + 1, movementType);
		}
	} else if (keyPress == LEFT) {
		if (validMoveChecker(data, mover, LEFT) == YES) {
			data->cursor.x--;
			data->unitData[mover].x--;
			data->unitData[mover].movement -= tileMovementGetter(data, x - 1, y, movementType);
			data->unitData[mover].fuel -= tileMovementGetter(data, x - 1, y, movementType);
		}
	} else if (keyPress == RIGHT) {
		if (validMoveChecker(data, mover, RIGHT) == YES) {
			data->cursor.x++;
			data->unitData[mover].x++;
			data->unitData[mover].movement -= tileMovementGetter(data, x + 1, y, movementType);
			data->unitData[mover].fuel -= tileMovementGetter(data, x + 1, y, movementType);
		}
	}
}

/// This function calculates and applies the damage from an attack
/// between two units.
void attackUnit (game *data, short attacker, short defender) {
	char attackRandom = rand() % 10;
	
	/// The base damage and defense are grabbed.
	char weapon = whichWeapon(data, attacker, defender);
	unsigned char baseDamage = baseDamageGetter (data, data->unitData[attacker].unitType, data->unitData[defender].unitType, weapon);
	unsigned char defenseRating = tileDefenseGetter (data, data->unitData[defender].x, data->unitData[defender].y);
	
	/// Now, the damage is calculated. The formula is a bit messy.
	/// Basically, a number is calculated after passing through this.
	float endDamage;
	endDamage = roundf(((baseDamage + attackRandom) / 100.0) * (data->unitData[attacker].health / 10.0) * ((100.0 - (defenseRating * data->unitData[defender].health)) / 100.0) * 100.0) / 10.0;
	
	printf("((%d + %d) / 100) * (%g / 10) * ((100 - (%d * %g)) / 100) = %g\n", baseDamage, attackRandom, data->unitData[attacker].health, defenseRating, data->unitData[defender].health, endDamage);
	
	/// The end health is applied, and the value is rounded (as health
	/// is only one decimal place).
	data->unitData[defender].health -= endDamage;

	/// Ammo is reduced for the attacker.
	if (weapon == PRIMARY) {
		if (data->unitData[attacker].ammo1 != -1) {
			data->unitData[attacker].ammo1--;
		}
	} else if (weapon == SECONDARY) {
		if (data->unitData[attacker].ammo2 != -1) {
			data->unitData[attacker].ammo2--;
		}
	}
			
	drawBattleResult(data, attacker, defender, endDamage, 0);
	
	/// If the opposing unit is still alive, and it can counter-attack,
	/// then it does the same calculation but accessing different stuff.
	/// Otherwise, it's dead, and we delete it.
	
	if (data->unitData[defender].health > 0) {
		if (canItCounter(data, attacker, defender) == YES) {
			attackRandom = rand() % 10;
			weapon = whichWeapon(data, defender, attacker);
			baseDamage = baseDamageGetter (data, data->unitData[defender].unitType, data->unitData[attacker].unitType, weapon);
			defenseRating = tileDefenseGetter (data, data->unitData[attacker].x, data->unitData[attacker].y);
			
			endDamage = roundf(((baseDamage + attackRandom) / 100.0) * (data->unitData[defender].health / 10.0) * ((100.0 - (defenseRating * data->unitData[attacker].health)) / 100.0) * 100.0) / 10.0;
	
			printf("((%d + %d) / 100) * (%g / 10) * ((100 - (%d * %g)) / 100) = %g\n", baseDamage, attackRandom, data->unitData[defender].health, defenseRating, data->unitData[attacker].health, endDamage);
			
			data->unitData[attacker].health -= endDamage;
			
			if (weapon == PRIMARY) {
				if (data->unitData[defender].ammo1 != -1) {
					data->unitData[defender].ammo1--;
				}
			} else if (weapon == SECONDARY) {
				if (data->unitData[defender].ammo2 != -1) {
					data->unitData[defender].ammo2--;
				}
			}
			
			drawBattleResult(data, defender, attacker, endDamage, 1);
			
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

/// This function creates a unit in the game based on who is building
/// it, what type of unit it is, and where it is going.
// Almost all the values are dummy values right now.
void createUnit (game *data, short x, short y, char unitType, char player) {
	short unitPos = 0;
	/// First, we find where an empty spot in the array is.
	while (data->unitData[unitPos].player != TEAM_NONE) {
		unitPos++;
	}
	
	/// Then we add the data we need.
	data->unitData[unitPos].unitType = unitType;
	data->unitData[unitPos].player = player;
	data->unitData[unitPos].ammo1 = unitAmmoGetter(data, unitPos, PRIMARY);
	data->unitData[unitPos].ammo2 =  unitAmmoGetter(data, unitPos, SECONDARY);
	data->unitData[unitPos].maxAmmo1 =  unitAmmoGetter(data, unitPos, PRIMARY);
	data->unitData[unitPos].maxAmmo2 =  unitAmmoGetter(data, unitPos, SECONDARY);
	data->unitData[unitPos].fuel = unitFuelGetter(data, unitPos);
	data->unitData[unitPos].maxFuel = unitFuelGetter(data, unitPos);
	data->unitData[unitPos].movement = unitMovementGetter(data, unitPos);
	data->unitData[unitPos].maxMovement = unitMovementGetter(data, unitPos);
	data->unitData[unitPos].vision = unitVisionGetter(data, unitPos);
	data->unitData[unitPos].health = 10;
	data->unitData[unitPos].finished = YES;
	data->unitData[unitPos].x = x;
	data->unitData[unitPos].y = y;
}

/// This function deletes a unit from the game.
void deleteUnit (game *data, short unitPos) {
	/// This de-initialises a unit. When a unit needs to be created,
	/// it'll find the lowest empty spot.
	// This was originally weighed up between sliding all the values
	// across (so the empty space is always at the end of the array),
	// and just straight deleting and finding the empty space when it
	// needs to. I went with the latter because deleting a unit may take
	// 99 times as long as before, rather than scanning for units might
	// take 3 times as long (while a more common process, it's much
	// shorter too).
	data->unitData[unitPos].unitType = 0;
	data->unitData[unitPos].player = 0;
	data->unitData[unitPos].ammo1 = 0;
	data->unitData[unitPos].ammo2 = 0;
	data->unitData[unitPos].maxAmmo1 = 0;
	data->unitData[unitPos].maxAmmo2 = 0;
	data->unitData[unitPos].fuel = 0;
	data->unitData[unitPos].maxFuel = 0;
	data->unitData[unitPos].movement = 0;
	data->unitData[unitPos].maxMovement = 0;
	data->unitData[unitPos].vision = 0;
	data->unitData[unitPos].health = 0;
	data->unitData[unitPos].finished = 0;
	data->unitData[unitPos].x = 0;
	data->unitData[unitPos].y = 0;
}

/// This function ends the turn, resets values, and passes control.
void endTurn(game *data) {
	/// This runs through every unit in play, and resets its movement
	/// amount.
	short arrayPos = 0;
	while (arrayPos < MAX_UNITS) {
		if (data->unitData[arrayPos].player != TEAM_NONE) {
			data->unitData[arrayPos].movement = data->unitData[arrayPos].maxMovement;
			data->unitData[arrayPos].finished = NO;
		}
		arrayPos++;
	}
	
	/// The game passes whose turn it is to the next player.
	data->whoseTurn++;
	/// If it's being passed to one too many players, we move it back
	/// to the first player, and increment the turn number.
	if (data->whoseTurn > data->numberOfPlayers) {
		data->whoseTurn = TEAM_RED;
		data->turnNum++;
	}
}

/// This checks if an asked move is valid.
char validMoveChecker(game *data, short mover, char direction) {
	char validMove = NO;
	
	/// If it moves in a certain direction...
	if (direction == UP) {
		/// If it isn't hitting the map edge...
		if (data->unitData[mover].y > 0) {
			/// If it isn't hitting another unit...
			if (unitGetter(data, data->unitData[mover].x, data->unitData[mover].y - 1) == MAX_UNITS) {
				/// If it's still got the movement left to go onto that
				/// tile...
				if (data->unitData[mover].movement >= tileMovementGetter(data, data->unitData[mover].x, data->unitData[mover].y - 1, unitMovementTypeGetter(data, mover))) {
					/// If it even can go on that tile...
					if (tileMovementGetter(data, data->unitData[mover].x, data->unitData[mover].y - 1, unitMovementTypeGetter(data, mover)) != 0) {
						/// Then it can move there.
						validMove = YES;
					}
				}
			}
		}
	} else if (direction == DOWN) {
		if (data->unitData[mover].y < MAP_HEIGHT - 1) {
			if (unitGetter(data, data->unitData[mover].x, data->unitData[mover].y + 1) == MAX_UNITS) {
				if (data->unitData[mover].movement >= tileMovementGetter(data, data->unitData[mover].x, data->unitData[mover].y + 1, unitMovementTypeGetter(data, mover))) {
					if (tileMovementGetter(data, data->unitData[mover].x, data->unitData[mover].y + 1, unitMovementTypeGetter(data, mover)) != 0) {
						validMove = YES;
					}
				}
			}
		}
	} else if (direction == LEFT) {
		if (data->unitData[mover].x > 0) {
			if (unitGetter(data, data->unitData[mover].x - 1, data->unitData[mover].y) == MAX_UNITS) {
				if (data->unitData[mover].movement >= tileMovementGetter(data, data->unitData[mover].x - 1, data->unitData[mover].y, unitMovementTypeGetter(data, mover))) {
					if (tileMovementGetter(data, data->unitData[mover].x - 1, data->unitData[mover].y, unitMovementTypeGetter(data, mover)) != 0) {
						validMove = YES;
					}
				}
			}
		}
	} else if (direction == RIGHT) {
		if (data->unitData[mover].y < MAP_WIDTH - 1) {
			if (unitGetter(data, data->unitData[mover].x + 1, data->unitData[mover].y) == MAX_UNITS) {
				if (data->unitData[mover].movement >= tileMovementGetter(data, data->unitData[mover].x + 1, data->unitData[mover].y, unitMovementTypeGetter(data, mover))) {
					if (tileMovementGetter(data, data->unitData[mover].x + 1, data->unitData[mover].y, unitMovementTypeGetter(data, mover)) != 0) {
						validMove = YES;
					}
				}
			}
		}
	}
	
	return validMove;
}

/// This function tests to see if a unit can hit another unit.
/// It returns YES (1) if true and NO (0) if false.
char validAttackChecker(game *data, short attacker, short defender) {
	char validAttack = NO;
	/// These determine how many tiles a unit is away from the attacker.
	char xDiff = data->unitData[attacker].x - data->unitData[defender].x;
	char yDiff = data->unitData[attacker].y - data->unitData[defender].y;
	if (xDiff < 0) {
		xDiff = xDiff * -1;
	}
	if (yDiff < 0) {
		yDiff = yDiff * -1;
	}
	
	/// If the target isn't on the same team as the attacker...
	if (data->unitData[attacker].player != data->unitData[defender].player) {
		/// If the target can even shoot the opponent...
		/// (this considers the attacker's ammo as well)
		if (whichWeapon(data, attacker, defender) != NONE) {
			/// If the unit is within range...
			if ((xDiff + yDiff) >= minimumRangeGetter(data, attacker)) {
				if ((xDiff + yDiff) <= maximumRangeGetter(data, attacker)) {
					validAttack = YES;
				}
			}
		}
	}
	
	return validAttack;
}

/// This function gets a unit's ID based on a position.
short unitGetter (game *data, short x, short y) {
	short unitPos = 0;
	while (unitPos < MAX_UNITS) {
		if ((data->unitData[unitPos].x == x) &&
			(data->unitData[unitPos].y == y)) {
			break;
		}
		unitPos++;
	}
	
	return unitPos;
}

/// This function gets a unit's max movement per turn.
char unitMovementGetter(game *data, short unitPos) {
	char unitMovement = 0;
	char unitType = data->unitData[unitPos].unitType;
	
	if (unitType == INFANTRY) {
		unitMovement = MOVESPEED_INFANTRY;
	} else if (unitType == MECH) {
		unitMovement = MOVESPEED_MECH;
	} else if (unitType == RECON) {
		unitMovement = MOVESPEED_RECON;
	} else if (unitType == TANK) {
		unitMovement = MOVESPEED_TANK;
	} else if (unitType == MD_TANK) {
		unitMovement = MOVESPEED_MD_TANK;
	} else if (unitType == NEOTANK) {
		unitMovement = MOVESPEED_NEOTANK;
	} else if (unitType == MEGATANK) {
		unitMovement = MOVESPEED_MEGATANK;
	} else if (unitType == APC) {
		unitMovement = MOVESPEED_APC;
	} else if (unitType == ARTILLERY) {
		unitMovement = MOVESPEED_ARTILLERY;
	} else if (unitType == ROCKETS) {
		unitMovement = MOVESPEED_ROCKETS;
	} else if (unitType == ANTI_AIR) {
		unitMovement = MOVESPEED_ANTI_AIR;
	} else if (unitType == MISSILES) {
		unitMovement = MOVESPEED_MISSILES;
	} else if (unitType == BATT_COP) {
		unitMovement = MOVESPEED_BATT_COP;
	} else if (unitType == TRAN_COP) {
		unitMovement = MOVESPEED_TRAN_COP;
	} else if (unitType == FIGHTER) {
		unitMovement = MOVESPEED_FIGHTER;
	} else if (unitType == BOMBER) {
		unitMovement = MOVESPEED_BOMBER;
	} else if (unitType == STEALTH) {
		unitMovement = MOVESPEED_STEALTH;
	} else if (unitType == LANDER) {
		unitMovement = MOVESPEED_LANDER;
	} else if (unitType == CRUISER) {
		unitMovement = MOVESPEED_CRUISER;
	} else if (unitType == SUB) {
		unitMovement = MOVESPEED_SUB;
	} else if (unitType == BATT_SHIP) {
		unitMovement = MOVESPEED_BATT_SHIP;
	} else if (unitType == CARRIER) {
		unitMovement = MOVESPEED_CARRIER;
	}
	return unitMovement;
}

/// This function gets the movement type of a given unit.
char unitMovementTypeGetter(game *data, short unitPos) {
	char unitMovementType = 0;
	if (data->unitData[unitPos].unitType == INFANTRY) {
		unitMovementType = MOVETYPE_INFANTRY;
	} else if (data->unitData[unitPos].unitType == MECH) {
		unitMovementType = MOVETYPE_MECH;
	} else if (data->unitData[unitPos].unitType == RECON) {
		unitMovementType = MOVETYPE_RECON;
	} else if (data->unitData[unitPos].unitType == TANK) {
		unitMovementType = MOVETYPE_TANK;
	} else if (data->unitData[unitPos].unitType == MD_TANK) {
		unitMovementType = MOVETYPE_MD_TANK;
	} else if (data->unitData[unitPos].unitType == NEOTANK) {
		unitMovementType = MOVETYPE_NEOTANK;
	} else if (data->unitData[unitPos].unitType == MEGATANK) {
		unitMovementType = MOVETYPE_MEGATANK;
	} else if (data->unitData[unitPos].unitType == APC) {
		unitMovementType = MOVETYPE_APC;
	} else if (data->unitData[unitPos].unitType == ARTILLERY) {
		unitMovementType = MOVETYPE_ARTILLERY;
	} else if (data->unitData[unitPos].unitType == ROCKETS) {
		unitMovementType = MOVETYPE_ROCKETS;
	} else if (data->unitData[unitPos].unitType == ANTI_AIR) {
		unitMovementType = MOVETYPE_ANTI_AIR;
	} else if (data->unitData[unitPos].unitType == MISSILES) {
		unitMovementType = MOVETYPE_MISSILES;
	} else if (data->unitData[unitPos].unitType == BATT_COP) {
		unitMovementType = MOVETYPE_BATT_COP;
	} else if (data->unitData[unitPos].unitType == TRAN_COP) {
		unitMovementType = MOVETYPE_TRAN_COP;
	} else if (data->unitData[unitPos].unitType == FIGHTER) {
		unitMovementType = MOVETYPE_FIGHTER;
	} else if (data->unitData[unitPos].unitType == BOMBER) {
		unitMovementType = MOVETYPE_BOMBER;
	} else if (data->unitData[unitPos].unitType == STEALTH) {
		unitMovementType = MOVETYPE_STEALTH;
	} else if (data->unitData[unitPos].unitType == LANDER) {
		unitMovementType = MOVETYPE_LANDER;
	} else if (data->unitData[unitPos].unitType == CRUISER) {
		unitMovementType = MOVETYPE_CRUISER;
	} else if (data->unitData[unitPos].unitType == SUB) {
		unitMovementType = MOVETYPE_SUB;
	} else if (data->unitData[unitPos].unitType == BATT_SHIP) {
		unitMovementType = MOVETYPE_BATT_SHIP;
	} else if (data->unitData[unitPos].unitType == CARRIER) {
		unitMovementType = MOVETYPE_CARRIER;
	}
	return unitMovementType;
}

/// This function gets a unit's max ammo for a specific weapon.
char unitAmmoGetter (game *data, short unitPos, char weapon) {
	char unitAmmo = 0;
	char unitType = data->unitData[unitPos].unitType;
	
	if (weapon == PRIMARY) {
		if (unitType == INFANTRY) {
			unitAmmo = MAXAMMO_INFANTRY_1;
		} else if (unitType == MECH) {
			unitAmmo = MAXAMMO_MECH_1;
		} else if (unitType == RECON) {
			unitAmmo = MAXAMMO_RECON_1;
		} else if (unitType == TANK) {
			unitAmmo = MAXAMMO_TANK_1;
		} else if (unitType == MD_TANK) {
			unitAmmo = MAXAMMO_MD_TANK_1;
		} else if (unitType == NEOTANK) {
			unitAmmo = MAXAMMO_NEOTANK_1;
		} else if (unitType == MEGATANK) {
			unitAmmo = MAXAMMO_MEGATANK_1;
		} else if (unitType == APC) {
			unitAmmo = MAXAMMO_APC_1;
		} else if (unitType == ARTILLERY) {
			unitAmmo = MAXAMMO_ARTILLERY_1;
		} else if (unitType == ROCKETS) {
			unitAmmo = MAXAMMO_ROCKETS_1;
		} else if (unitType == ANTI_AIR) {
			unitAmmo = MAXAMMO_ANTI_AIR_1;
		} else if (unitType == MISSILES) {
			unitAmmo = MAXAMMO_MISSILES_1;
		} else if (unitType == BATT_COP) {
			unitAmmo = MAXAMMO_BATT_COP_1;
		} else if (unitType == TRAN_COP) {
			unitAmmo = MAXAMMO_TRAN_COP_1;
		} else if (unitType == FIGHTER) {
			unitAmmo = MAXAMMO_FIGHTER_1;
		} else if (unitType == BOMBER) {
			unitAmmo = MAXAMMO_BOMBER_1;
		} else if (unitType == STEALTH) {
			unitAmmo = MAXAMMO_STEALTH_1;
		} else if (unitType == LANDER) {
			unitAmmo = MAXAMMO_LANDER_1;
		} else if (unitType == CRUISER) {
			unitAmmo = MAXAMMO_CRUISER_1;
		} else if (unitType == SUB) {
			unitAmmo = MAXAMMO_SUB_1;
		} else if (unitType == BATT_SHIP) {
			unitAmmo = MAXAMMO_BATT_SHIP_1;
		} else if (unitType == CARRIER) {
			unitAmmo = MAXAMMO_CARRIER_1;
		}
	} else if (weapon == SECONDARY) {
		if (unitType == INFANTRY) {
			unitAmmo = MAXAMMO_INFANTRY_2;
		} else if (unitType == MECH) {
			unitAmmo = MAXAMMO_MECH_2;
		} else if (unitType == RECON) {
			unitAmmo = MAXAMMO_RECON_2;
		} else if (unitType == TANK) {
			unitAmmo = MAXAMMO_TANK_2;
		} else if (unitType == MD_TANK) {
			unitAmmo = MAXAMMO_MD_TANK_2;
		} else if (unitType == NEOTANK) {
			unitAmmo = MAXAMMO_NEOTANK_2;
		} else if (unitType == MEGATANK) {
			unitAmmo = MAXAMMO_MEGATANK_2;
		} else if (unitType == APC) {
			unitAmmo = MAXAMMO_APC_2;
		} else if (unitType == ARTILLERY) {
			unitAmmo = MAXAMMO_ARTILLERY_2;
		} else if (unitType == ROCKETS) {
			unitAmmo = MAXAMMO_ROCKETS_2;
		} else if (unitType == ANTI_AIR) {
			unitAmmo = MAXAMMO_ANTI_AIR_2;
		} else if (unitType == MISSILES) {
			unitAmmo = MAXAMMO_MISSILES_2;
		} else if (unitType == BATT_COP) {
			unitAmmo = MAXAMMO_BATT_COP_2;
		} else if (unitType == TRAN_COP) {
			unitAmmo = MAXAMMO_TRAN_COP_2;
		} else if (unitType == FIGHTER) {
			unitAmmo = MAXAMMO_FIGHTER_2;
		} else if (unitType == BOMBER) {
			unitAmmo = MAXAMMO_BOMBER_2;
		} else if (unitType == STEALTH) {
			unitAmmo = MAXAMMO_STEALTH_2;
		} else if (unitType == LANDER) {
			unitAmmo = MAXAMMO_LANDER_2;
		} else if (unitType == CRUISER) {
			unitAmmo = MAXAMMO_CRUISER_2;
		} else if (unitType == SUB) {
			unitAmmo = MAXAMMO_SUB_2;
		} else if (unitType == BATT_SHIP) {
			unitAmmo = MAXAMMO_BATT_SHIP_2;
		} else if (unitType == CARRIER) {
			unitAmmo = MAXAMMO_CARRIER_2;
		}
	}
	return unitAmmo;
}

/// This function gets a unit's max fuel capacity.
char unitFuelGetter (game *data, short unitPos) {
	char unitFuel = 0;
	char unitType = data->unitData[unitPos].unitType;
	
	if (unitType == INFANTRY) {
		unitFuel = MAXFUEL_INFANTRY;
	} else if (unitType == MECH) {
		unitFuel = MAXFUEL_MECH;
	} else if (unitType == RECON) {
		unitFuel = MAXFUEL_RECON;
	} else if (unitType == TANK) {
		unitFuel = MAXFUEL_TANK;
	} else if (unitType == MD_TANK) {
		unitFuel = MAXFUEL_MD_TANK;
	} else if (unitType == NEOTANK) {
		unitFuel = MAXFUEL_NEOTANK;
	} else if (unitType == MEGATANK) {
		unitFuel = MAXFUEL_MEGATANK;
	} else if (unitType == APC) {
		unitFuel = MAXFUEL_APC;
	} else if (unitType == ARTILLERY) {
		unitFuel = MAXFUEL_ARTILLERY;
	} else if (unitType == ROCKETS) {
		unitFuel = MAXFUEL_ROCKETS;
	} else if (unitType == ANTI_AIR) {
		unitFuel = MAXFUEL_ANTI_AIR;
	} else if (unitType == MISSILES) {
		unitFuel = MAXFUEL_MISSILES;
	} else if (unitType == BATT_COP) {
		unitFuel = MAXFUEL_BATT_COP;
	} else if (unitType == TRAN_COP) {
		unitFuel = MAXFUEL_TRAN_COP;
	} else if (unitType == FIGHTER) {
		unitFuel = MAXFUEL_FIGHTER;
	} else if (unitType == BOMBER) {
		unitFuel = MAXFUEL_BOMBER;
	} else if (unitType == STEALTH) {
		unitFuel = MAXFUEL_STEALTH;
	} else if (unitType == LANDER) {
		unitFuel = MAXFUEL_LANDER;
	} else if (unitType == CRUISER) {
		unitFuel = MAXFUEL_CRUISER;
	} else if (unitType == SUB) {
		unitFuel = MAXFUEL_SUB;
	} else if (unitType == BATT_SHIP) {
		unitFuel = MAXFUEL_BATT_SHIP;
	} else if (unitType == CARRIER) {
		unitFuel = MAXFUEL_CARRIER;
	}
	
	return unitFuel;
}

/// This function gets a unit's vision.
char unitVisionGetter (game *data, short unitPos) {
	char unitVision = 0;
	char unitType = data->unitData[unitPos].unitType;
	
	if (unitType == INFANTRY) {
		unitVision = VISION_INFANTRY;
	} else if (unitType == MECH) {
		unitVision = VISION_MECH;
	} else if (unitType == RECON) {
		unitVision = VISION_RECON;
	} else if (unitType == TANK) {
		unitVision = VISION_TANK;
	} else if (unitType == MD_TANK) {
		unitVision = VISION_MD_TANK;
	} else if (unitType == NEOTANK) {
		unitVision = VISION_NEOTANK;
	} else if (unitType == MEGATANK) {
		unitVision = VISION_MEGATANK;
	} else if (unitType == APC) {
		unitVision = VISION_APC;
	} else if (unitType == ARTILLERY) {
		unitVision = VISION_ARTILLERY;
	} else if (unitType == ROCKETS) {
		unitVision = VISION_ROCKETS;
	} else if (unitType == ANTI_AIR) {
		unitVision = VISION_ANTI_AIR;
	} else if (unitType == MISSILES) {
		unitVision = VISION_MISSILES;
	} else if (unitType == BATT_COP) {
		unitVision = VISION_BATT_COP;
	} else if (unitType == TRAN_COP) {
		unitVision = VISION_TRAN_COP;
	} else if (unitType == FIGHTER) {
		unitVision = VISION_FIGHTER;
	} else if (unitType == BOMBER) {
		unitVision = VISION_BOMBER;
	} else if (unitType == STEALTH) {
		unitVision = VISION_STEALTH;
	} else if (unitType == LANDER) {
		unitVision = VISION_LANDER;
	} else if (unitType == CRUISER) {
		unitVision = VISION_CRUISER;
	} else if (unitType == SUB) {
		unitVision = VISION_SUB;
	} else if (unitType == BATT_SHIP) {
		unitVision = VISION_BATT_SHIP;
	} else if (unitType == CARRIER) {
		unitVision = VISION_CARRIER;
	}
	
	return unitVision;
}

/// This function gets the movement cost for a certain tile based on
/// the movement type provided.
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

/// This fuunction gets the defense value of a given co-ordinate.
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
	}
	else if (tileType == RIVER) {
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

/// This function gets the base damage a unit has against another unit.
unsigned char baseDamageGetter (game *data, short attacker, short defender, char weapon) {
	unsigned char baseDamage = 0;
	char unitTypeAttacker = data->unitData[attacker].unitType;
	char unitTypeDefender = data->unitData[defender].unitType;
	
	if (weapon == PRIMARY) {
		if (unitTypeAttacker == INFANTRY) {
			if (unitTypeDefender == INFANTRY) {
				baseDamage = DAMAGE_INFANTRY_INFANTRY;
			} else if (unitTypeDefender == MECH) {
				baseDamage = DAMAGE_INFANTRY_MECH;
			} else if (unitTypeDefender == RECON) {
				baseDamage = DAMAGE_INFANTRY_RECON;
			} else if (unitTypeDefender == TANK) {
				baseDamage = DAMAGE_INFANTRY_TANK;
			} else if (unitTypeDefender == MD_TANK) {
				baseDamage = DAMAGE_INFANTRY_MD_TANK;
			} else if (unitTypeDefender == NEOTANK) {
				baseDamage = DAMAGE_INFANTRY_NEOTANK;
			} else if (unitTypeDefender == MEGATANK) {
				baseDamage = DAMAGE_INFANTRY_MEGATANK;
			} else if (unitTypeDefender == APC) {
				baseDamage = DAMAGE_INFANTRY_APC;
			} else if (unitTypeDefender == ARTILLERY) {
				baseDamage = DAMAGE_INFANTRY_ARTILLERY;
			} else if (unitTypeDefender == ROCKETS) {
				baseDamage = DAMAGE_INFANTRY_ROCKETS;
			} else if (unitTypeDefender == ANTI_AIR) {
				baseDamage = DAMAGE_INFANTRY_ANTI_AIR;
			} else if (unitTypeDefender == MISSILES) {
				baseDamage = DAMAGE_INFANTRY_MISSILES;
			} else if (unitTypeDefender == BATT_COP) {
				baseDamage = DAMAGE_INFANTRY_BATT_COP;
			} else if (unitTypeDefender == TRAN_COP) {
				baseDamage = DAMAGE_INFANTRY_TRAN_COP;
			} else if (unitTypeDefender == FIGHTER) {
				baseDamage = DAMAGE_INFANTRY_FIGHTER;
			} else if (unitTypeDefender == BOMBER) {
				baseDamage = DAMAGE_INFANTRY_BOMBER;
			} else if (unitTypeDefender == STEALTH) {
				baseDamage = DAMAGE_INFANTRY_STEALTH;
			} else if (unitTypeDefender == LANDER) {
				baseDamage = DAMAGE_INFANTRY_LANDER;
			} else if (unitTypeDefender == CRUISER) {
				baseDamage = DAMAGE_INFANTRY_CRUISER;
			} else if (unitTypeDefender == SUB) {
				baseDamage = DAMAGE_INFANTRY_SUB;
			} else if (unitTypeDefender == BATT_SHIP) {
				baseDamage = DAMAGE_INFANTRY_BATT_SHIP;
			} else if (unitTypeDefender == CARRIER) {
				baseDamage = DAMAGE_INFANTRY_CARRIER;
			}
		} else if (unitTypeAttacker == MECH) {
			if (unitTypeDefender == INFANTRY) {
				baseDamage = DAMAGE_MECH_INFANTRY_1;
			} else if (unitTypeDefender == MECH) {
				baseDamage = DAMAGE_MECH_MECH_1;
			} else if (unitTypeDefender == RECON) {
				baseDamage = DAMAGE_MECH_RECON_1;
			} else if (unitTypeDefender == TANK) {
				baseDamage = DAMAGE_MECH_TANK_1;
			} else if (unitTypeDefender == MD_TANK) {
				baseDamage = DAMAGE_MECH_MD_TANK_1;
			} else if (unitTypeDefender == NEOTANK) {
				baseDamage = DAMAGE_MECH_NEOTANK_1;
			} else if (unitTypeDefender == MEGATANK) {
				baseDamage = DAMAGE_MECH_MEGATANK_1;
			} else if (unitTypeDefender == APC) {
				baseDamage = DAMAGE_MECH_APC_1;
			} else if (unitTypeDefender == ARTILLERY) {
				baseDamage = DAMAGE_MECH_ARTILLERY_1;
			} else if (unitTypeDefender == ROCKETS) {
				baseDamage = DAMAGE_MECH_ROCKETS_1;
			} else if (unitTypeDefender == ANTI_AIR) {
				baseDamage = DAMAGE_MECH_ANTI_AIR_1;
			} else if (unitTypeDefender == MISSILES) {
				baseDamage = DAMAGE_MECH_MISSILES_1;
			} else if (unitTypeDefender == BATT_COP) {
				baseDamage = DAMAGE_MECH_BATT_COP_1;
			} else if (unitTypeDefender == TRAN_COP) {
				baseDamage = DAMAGE_MECH_TRAN_COP_1;
			} else if (unitTypeDefender == FIGHTER) {
				baseDamage = DAMAGE_MECH_FIGHTER_1;
			} else if (unitTypeDefender == BOMBER) {
				baseDamage = DAMAGE_MECH_BOMBER_1;
			} else if (unitTypeDefender == STEALTH) {
				baseDamage = DAMAGE_MECH_STEALTH_1;
			} else if (unitTypeDefender == LANDER) {
				baseDamage = DAMAGE_MECH_LANDER_1;
			} else if (unitTypeDefender == CRUISER) {
				baseDamage = DAMAGE_MECH_CRUISER_1;
			} else if (unitTypeDefender == SUB) {
				baseDamage = DAMAGE_MECH_SUB_1;
			} else if (unitTypeDefender == BATT_SHIP) {
				baseDamage = DAMAGE_MECH_BATT_SHIP_1;
			} else if (unitTypeDefender == CARRIER) {
				baseDamage = DAMAGE_MECH_CARRIER_1;
			}
		} else if (unitTypeAttacker == RECON) {
			if (unitTypeDefender == INFANTRY) {
				baseDamage = DAMAGE_RECON_INFANTRY;
			} else if (unitTypeDefender == MECH) {
				baseDamage = DAMAGE_RECON_MECH;
			} else if (unitTypeDefender == RECON) {
				baseDamage = DAMAGE_RECON_RECON;
			} else if (unitTypeDefender == TANK) {
				baseDamage = DAMAGE_RECON_TANK;
			} else if (unitTypeDefender == MD_TANK) {
				baseDamage = DAMAGE_RECON_MD_TANK;
			} else if (unitTypeDefender == NEOTANK) {
				baseDamage = DAMAGE_RECON_NEOTANK;
			} else if (unitTypeDefender == MEGATANK) {
				baseDamage = DAMAGE_RECON_MEGATANK;
			} else if (unitTypeDefender == APC) {
				baseDamage = DAMAGE_RECON_APC;
			} else if (unitTypeDefender == ARTILLERY) {
				baseDamage = DAMAGE_RECON_ARTILLERY;
			} else if (unitTypeDefender == ROCKETS) {
				baseDamage = DAMAGE_RECON_ROCKETS;
			} else if (unitTypeDefender == ANTI_AIR) {
				baseDamage = DAMAGE_RECON_ANTI_AIR;
			} else if (unitTypeDefender == MISSILES) {
				baseDamage = DAMAGE_RECON_MISSILES;
			} else if (unitTypeDefender == BATT_COP) {
				baseDamage = DAMAGE_RECON_BATT_COP;
			} else if (unitTypeDefender == TRAN_COP) {
				baseDamage = DAMAGE_RECON_TRAN_COP;
			} else if (unitTypeDefender == FIGHTER) {
				baseDamage = DAMAGE_RECON_FIGHTER;
			} else if (unitTypeDefender == BOMBER) {
				baseDamage = DAMAGE_RECON_BOMBER;
			} else if (unitTypeDefender == STEALTH) {
				baseDamage = DAMAGE_RECON_STEALTH;
			} else if (unitTypeDefender == LANDER) {
				baseDamage = DAMAGE_RECON_LANDER;
			} else if (unitTypeDefender == CRUISER) {
				baseDamage = DAMAGE_RECON_CRUISER;
			} else if (unitTypeDefender == SUB) {
				baseDamage = DAMAGE_RECON_SUB;
			} else if (unitTypeDefender == BATT_SHIP) {
				baseDamage = DAMAGE_RECON_BATT_SHIP;
			} else if (unitTypeDefender == CARRIER) {
				baseDamage = DAMAGE_RECON_CARRIER;
			}
		} else if (unitTypeAttacker == TANK) {
			if (unitTypeDefender == INFANTRY) {
				baseDamage = DAMAGE_TANK_INFANTRY_1;
			} else if (unitTypeDefender == MECH) {
				baseDamage = DAMAGE_TANK_MECH_1;
			} else if (unitTypeDefender == RECON) {
				baseDamage = DAMAGE_TANK_RECON_1;
			} else if (unitTypeDefender == TANK) {
				baseDamage = DAMAGE_TANK_TANK_1;
			} else if (unitTypeDefender == MD_TANK) {
				baseDamage = DAMAGE_TANK_MD_TANK_1;
			} else if (unitTypeDefender == NEOTANK) {
				baseDamage = DAMAGE_TANK_NEOTANK_1;
			} else if (unitTypeDefender == MEGATANK) {
				baseDamage = DAMAGE_TANK_MEGATANK_1;
			} else if (unitTypeDefender == APC) {
				baseDamage = DAMAGE_TANK_APC_1;
			} else if (unitTypeDefender == ARTILLERY) {
				baseDamage = DAMAGE_TANK_ARTILLERY_1;
			} else if (unitTypeDefender == ROCKETS) {
				baseDamage = DAMAGE_TANK_ROCKETS_1;
			} else if (unitTypeDefender == ANTI_AIR) {
				baseDamage = DAMAGE_TANK_ANTI_AIR_1;
			} else if (unitTypeDefender == MISSILES) {
				baseDamage = DAMAGE_TANK_MISSILES_1;
			} else if (unitTypeDefender == BATT_COP) {
				baseDamage = DAMAGE_TANK_BATT_COP_1;
			} else if (unitTypeDefender == TRAN_COP) {
				baseDamage = DAMAGE_TANK_TRAN_COP_1;
			} else if (unitTypeDefender == FIGHTER) {
				baseDamage = DAMAGE_TANK_FIGHTER_1;
			} else if (unitTypeDefender == BOMBER) {
				baseDamage = DAMAGE_TANK_BOMBER_1;
			} else if (unitTypeDefender == STEALTH) {
				baseDamage = DAMAGE_TANK_STEALTH_1;
			} else if (unitTypeDefender == LANDER) {
				baseDamage = DAMAGE_TANK_LANDER_1;
			} else if (unitTypeDefender == CRUISER) {
				baseDamage = DAMAGE_TANK_CRUISER_1;
			} else if (unitTypeDefender == SUB) {
				baseDamage = DAMAGE_TANK_SUB_1;
			} else if (unitTypeDefender == BATT_SHIP) {
				baseDamage = DAMAGE_TANK_BATT_SHIP_1;
			} else if (unitTypeDefender == CARRIER) {
				baseDamage = DAMAGE_TANK_CARRIER_1;
			}
		} else if (unitTypeAttacker == MD_TANK) {
			if (unitTypeDefender == INFANTRY) {
				baseDamage = DAMAGE_MD_TANK_INFANTRY_1;
			} else if (unitTypeDefender == MECH) {
				baseDamage = DAMAGE_MD_TANK_MECH_1;
			} else if (unitTypeDefender == RECON) {
				baseDamage = DAMAGE_MD_TANK_RECON_1;
			} else if (unitTypeDefender == TANK) {
				baseDamage = DAMAGE_MD_TANK_TANK_1;
			} else if (unitTypeDefender == MD_TANK) {
				baseDamage = DAMAGE_MD_TANK_MD_TANK_1;
			} else if (unitTypeDefender == NEOTANK) {
				baseDamage = DAMAGE_MD_TANK_NEOTANK_1;
			} else if (unitTypeDefender == MEGATANK) {
				baseDamage = DAMAGE_MD_TANK_MEGATANK_1;
			} else if (unitTypeDefender == APC) {
				baseDamage = DAMAGE_MD_TANK_APC_1;
			} else if (unitTypeDefender == ARTILLERY) {
				baseDamage = DAMAGE_MD_TANK_ARTILLERY_1;
			} else if (unitTypeDefender == ROCKETS) {
				baseDamage = DAMAGE_MD_TANK_ROCKETS_1;
			} else if (unitTypeDefender == ANTI_AIR) {
				baseDamage = DAMAGE_MD_TANK_ANTI_AIR_1;
			} else if (unitTypeDefender == MISSILES) {
				baseDamage = DAMAGE_MD_TANK_MISSILES_1;
			} else if (unitTypeDefender == BATT_COP) {
				baseDamage = DAMAGE_MD_TANK_BATT_COP_1;
			} else if (unitTypeDefender == TRAN_COP) {
				baseDamage = DAMAGE_MD_TANK_TRAN_COP_1;
			} else if (unitTypeDefender == FIGHTER) {
				baseDamage = DAMAGE_MD_TANK_FIGHTER_1;
			} else if (unitTypeDefender == BOMBER) {
				baseDamage = DAMAGE_MD_TANK_BOMBER_1;
			} else if (unitTypeDefender == STEALTH) {
				baseDamage = DAMAGE_MD_TANK_STEALTH_1;
			} else if (unitTypeDefender == LANDER) {
				baseDamage = DAMAGE_MD_TANK_LANDER_1;
			} else if (unitTypeDefender == CRUISER) {
				baseDamage = DAMAGE_MD_TANK_CRUISER_1;
			} else if (unitTypeDefender == SUB) {
				baseDamage = DAMAGE_MD_TANK_SUB_1;
			} else if (unitTypeDefender == BATT_SHIP) {
				baseDamage = DAMAGE_MD_TANK_BATT_SHIP_1;
			} else if (unitTypeDefender == CARRIER) {
				baseDamage = DAMAGE_MD_TANK_CARRIER_1;
			}
		} else if (unitTypeAttacker == NEOTANK) {
			if (unitTypeDefender == INFANTRY) {
				baseDamage = DAMAGE_NEOTANK_INFANTRY_1;
			} else if (unitTypeDefender == MECH) {
				baseDamage = DAMAGE_NEOTANK_MECH_1;
			} else if (unitTypeDefender == RECON) {
				baseDamage = DAMAGE_NEOTANK_RECON_1;
			} else if (unitTypeDefender == TANK) {
				baseDamage = DAMAGE_NEOTANK_TANK_1;
			} else if (unitTypeDefender == MD_TANK) {
				baseDamage = DAMAGE_NEOTANK_MD_TANK_1;
			} else if (unitTypeDefender == NEOTANK) {
				baseDamage = DAMAGE_NEOTANK_NEOTANK_1;
			} else if (unitTypeDefender == MEGATANK) {
				baseDamage = DAMAGE_NEOTANK_MEGATANK_1;
			} else if (unitTypeDefender == APC) {
				baseDamage = DAMAGE_NEOTANK_APC_1;
			} else if (unitTypeDefender == ARTILLERY) {
				baseDamage = DAMAGE_NEOTANK_ARTILLERY_1;
			} else if (unitTypeDefender == ROCKETS) {
				baseDamage = DAMAGE_NEOTANK_ROCKETS_1;
			} else if (unitTypeDefender == ANTI_AIR) {
				baseDamage = DAMAGE_NEOTANK_ANTI_AIR_1;
			} else if (unitTypeDefender == MISSILES) {
				baseDamage = DAMAGE_NEOTANK_MISSILES_1;
			} else if (unitTypeDefender == BATT_COP) {
				baseDamage = DAMAGE_NEOTANK_BATT_COP_1;
			} else if (unitTypeDefender == TRAN_COP) {
				baseDamage = DAMAGE_NEOTANK_TRAN_COP_1;
			} else if (unitTypeDefender == FIGHTER) {
				baseDamage = DAMAGE_NEOTANK_FIGHTER_1;
			} else if (unitTypeDefender == BOMBER) {
				baseDamage = DAMAGE_NEOTANK_BOMBER_1;
			} else if (unitTypeDefender == STEALTH) {
				baseDamage = DAMAGE_NEOTANK_STEALTH_1;
			} else if (unitTypeDefender == LANDER) {
				baseDamage = DAMAGE_NEOTANK_LANDER_1;
			} else if (unitTypeDefender == CRUISER) {
				baseDamage = DAMAGE_NEOTANK_CRUISER_1;
			} else if (unitTypeDefender == SUB) {
				baseDamage = DAMAGE_NEOTANK_SUB_1;
			} else if (unitTypeDefender == BATT_SHIP) {
				baseDamage = DAMAGE_NEOTANK_BATT_SHIP_1;
			} else if (unitTypeDefender == CARRIER) {
				baseDamage = DAMAGE_NEOTANK_CARRIER_1;
			}
		} else if (unitTypeAttacker == MEGATANK) {
			if (unitTypeDefender == INFANTRY) {
				baseDamage = DAMAGE_MEGATANK_INFANTRY_1;
			} else if (unitTypeDefender == MECH) {
				baseDamage = DAMAGE_MEGATANK_MECH_1;
			} else if (unitTypeDefender == RECON) {
				baseDamage = DAMAGE_MEGATANK_RECON_1;
			} else if (unitTypeDefender == TANK) {
				baseDamage = DAMAGE_MEGATANK_TANK_1;
			} else if (unitTypeDefender == MD_TANK) {
				baseDamage = DAMAGE_MEGATANK_MD_TANK_1;
			} else if (unitTypeDefender == NEOTANK) {
				baseDamage = DAMAGE_MEGATANK_NEOTANK_1;
			} else if (unitTypeDefender == MEGATANK) {
				baseDamage = DAMAGE_MEGATANK_MEGATANK_1;
			} else if (unitTypeDefender == APC) {
				baseDamage = DAMAGE_MEGATANK_APC_1;
			} else if (unitTypeDefender == ARTILLERY) {
				baseDamage = DAMAGE_MEGATANK_ARTILLERY_1;
			} else if (unitTypeDefender == ROCKETS) {
				baseDamage = DAMAGE_MEGATANK_ROCKETS_1;
			} else if (unitTypeDefender == ANTI_AIR) {
				baseDamage = DAMAGE_MEGATANK_ANTI_AIR_1;
			} else if (unitTypeDefender == MISSILES) {
				baseDamage = DAMAGE_MEGATANK_MISSILES_1;
			} else if (unitTypeDefender == BATT_COP) {
				baseDamage = DAMAGE_MEGATANK_BATT_COP_1;
			} else if (unitTypeDefender == TRAN_COP) {
				baseDamage = DAMAGE_MEGATANK_TRAN_COP_1;
			} else if (unitTypeDefender == FIGHTER) {
				baseDamage = DAMAGE_MEGATANK_FIGHTER_1;
			} else if (unitTypeDefender == BOMBER) {
				baseDamage = DAMAGE_MEGATANK_BOMBER_1;
			} else if (unitTypeDefender == STEALTH) {
				baseDamage = DAMAGE_MEGATANK_STEALTH_1;
			} else if (unitTypeDefender == LANDER) {
				baseDamage = DAMAGE_MEGATANK_LANDER_1;
			} else if (unitTypeDefender == CRUISER) {
				baseDamage = DAMAGE_MEGATANK_CRUISER_1;
			} else if (unitTypeDefender == SUB) {
				baseDamage = DAMAGE_MEGATANK_SUB_1;
			} else if (unitTypeDefender == BATT_SHIP) {
				baseDamage = DAMAGE_MEGATANK_BATT_SHIP_1;
			} else if (unitTypeDefender == CARRIER) {
				baseDamage = DAMAGE_MEGATANK_CARRIER_1;
			}
		} else if (unitTypeAttacker == ARTILLERY) {
			if (unitTypeDefender == INFANTRY) {
				baseDamage = DAMAGE_ARTILLERY_INFANTRY;
			} else if (unitTypeDefender == MECH) {
				baseDamage = DAMAGE_ARTILLERY_MECH;
			} else if (unitTypeDefender == RECON) {
				baseDamage = DAMAGE_ARTILLERY_RECON;
			} else if (unitTypeDefender == TANK) {
				baseDamage = DAMAGE_ARTILLERY_TANK;
			} else if (unitTypeDefender == MD_TANK) {
				baseDamage = DAMAGE_ARTILLERY_MD_TANK;
			} else if (unitTypeDefender == NEOTANK) {
				baseDamage = DAMAGE_ARTILLERY_NEOTANK;
			} else if (unitTypeDefender == MEGATANK) {
				baseDamage = DAMAGE_ARTILLERY_MEGATANK;
			} else if (unitTypeDefender == APC) {
				baseDamage = DAMAGE_ARTILLERY_APC;
			} else if (unitTypeDefender == ARTILLERY) {
				baseDamage = DAMAGE_ARTILLERY_ARTILLERY;
			} else if (unitTypeDefender == ROCKETS) {
				baseDamage = DAMAGE_ARTILLERY_ROCKETS;
			} else if (unitTypeDefender == ANTI_AIR) {
				baseDamage = DAMAGE_ARTILLERY_ANTI_AIR;
			} else if (unitTypeDefender == MISSILES) {
				baseDamage = DAMAGE_ARTILLERY_MISSILES;
			} else if (unitTypeDefender == BATT_COP) {
				baseDamage = DAMAGE_ARTILLERY_BATT_COP;
			} else if (unitTypeDefender == TRAN_COP) {
				baseDamage = DAMAGE_ARTILLERY_TRAN_COP;
			} else if (unitTypeDefender == FIGHTER) {
				baseDamage = DAMAGE_ARTILLERY_FIGHTER;
			} else if (unitTypeDefender == BOMBER) {
				baseDamage = DAMAGE_ARTILLERY_BOMBER;
			} else if (unitTypeDefender == STEALTH) {
				baseDamage = DAMAGE_ARTILLERY_STEALTH;
			} else if (unitTypeDefender == LANDER) {
				baseDamage = DAMAGE_ARTILLERY_LANDER;
			} else if (unitTypeDefender == CRUISER) {
				baseDamage = DAMAGE_ARTILLERY_CRUISER;
			} else if (unitTypeDefender == SUB) {
				baseDamage = DAMAGE_ARTILLERY_SUB;
			} else if (unitTypeDefender == BATT_SHIP) {
				baseDamage = DAMAGE_ARTILLERY_BATT_SHIP;
			} else if (unitTypeDefender == CARRIER) {
				baseDamage = DAMAGE_ARTILLERY_CARRIER;
			}
		} else if (unitTypeAttacker == ROCKETS) {
			if (unitTypeDefender == INFANTRY) {
				baseDamage = DAMAGE_ROCKETS_INFANTRY;
			} else if (unitTypeDefender == MECH) {
				baseDamage = DAMAGE_ROCKETS_MECH;
			} else if (unitTypeDefender == RECON) {
				baseDamage = DAMAGE_ROCKETS_RECON;
			} else if (unitTypeDefender == TANK) {
				baseDamage = DAMAGE_ROCKETS_TANK;
			} else if (unitTypeDefender == MD_TANK) {
				baseDamage = DAMAGE_ROCKETS_MD_TANK;
			} else if (unitTypeDefender == NEOTANK) {
				baseDamage = DAMAGE_ROCKETS_NEOTANK;
			} else if (unitTypeDefender == MEGATANK) {
				baseDamage = DAMAGE_ROCKETS_MEGATANK;
			} else if (unitTypeDefender == APC) {
				baseDamage = DAMAGE_ROCKETS_APC;
			} else if (unitTypeDefender == ARTILLERY) {
				baseDamage = DAMAGE_ROCKETS_ARTILLERY;
			} else if (unitTypeDefender == ROCKETS) {
				baseDamage = DAMAGE_ROCKETS_ROCKETS;
			} else if (unitTypeDefender == ANTI_AIR) {
				baseDamage = DAMAGE_ROCKETS_ANTI_AIR;
			} else if (unitTypeDefender == MISSILES) {
				baseDamage = DAMAGE_ROCKETS_MISSILES;
			} else if (unitTypeDefender == BATT_COP) {
				baseDamage = DAMAGE_ROCKETS_BATT_COP;
			} else if (unitTypeDefender == TRAN_COP) {
				baseDamage = DAMAGE_ROCKETS_TRAN_COP;
			} else if (unitTypeDefender == FIGHTER) {
				baseDamage = DAMAGE_ROCKETS_FIGHTER;
			} else if (unitTypeDefender == BOMBER) {
				baseDamage = DAMAGE_ROCKETS_BOMBER;
			} else if (unitTypeDefender == STEALTH) {
				baseDamage = DAMAGE_ROCKETS_STEALTH;
			} else if (unitTypeDefender == LANDER) {
				baseDamage = DAMAGE_ROCKETS_LANDER;
			} else if (unitTypeDefender == CRUISER) {
				baseDamage = DAMAGE_ROCKETS_CRUISER;
			} else if (unitTypeDefender == SUB) {
				baseDamage = DAMAGE_ROCKETS_SUB;
			} else if (unitTypeDefender == BATT_SHIP) {
				baseDamage = DAMAGE_ROCKETS_BATT_SHIP;
			} else if (unitTypeDefender == CARRIER) {
				baseDamage = DAMAGE_ROCKETS_CARRIER;
			}
		} else if (unitTypeAttacker == ANTI_AIR) {
			if (unitTypeDefender == INFANTRY) {
				baseDamage = DAMAGE_ANTI_AIR_INFANTRY;
			} else if (unitTypeDefender == MECH) {
				baseDamage = DAMAGE_ANTI_AIR_MECH;
			} else if (unitTypeDefender == RECON) {
				baseDamage = DAMAGE_ANTI_AIR_RECON;
			} else if (unitTypeDefender == TANK) {
				baseDamage = DAMAGE_ANTI_AIR_TANK;
			} else if (unitTypeDefender == MD_TANK) {
				baseDamage = DAMAGE_ANTI_AIR_MD_TANK;
			} else if (unitTypeDefender == NEOTANK) {
				baseDamage = DAMAGE_ANTI_AIR_NEOTANK;
			} else if (unitTypeDefender == MEGATANK) {
				baseDamage = DAMAGE_ANTI_AIR_MEGATANK;
			} else if (unitTypeDefender == APC) {
				baseDamage = DAMAGE_ANTI_AIR_APC;
			} else if (unitTypeDefender == ARTILLERY) {
				baseDamage = DAMAGE_ANTI_AIR_ARTILLERY;
			} else if (unitTypeDefender == ROCKETS) {
				baseDamage = DAMAGE_ANTI_AIR_ROCKETS;
			} else if (unitTypeDefender == ANTI_AIR) {
				baseDamage = DAMAGE_ANTI_AIR_ANTI_AIR;
			} else if (unitTypeDefender == MISSILES) {
				baseDamage = DAMAGE_ANTI_AIR_MISSILES;
			} else if (unitTypeDefender == BATT_COP) {
				baseDamage = DAMAGE_ANTI_AIR_BATT_COP;
			} else if (unitTypeDefender == TRAN_COP) {
				baseDamage = DAMAGE_ANTI_AIR_TRAN_COP;
			} else if (unitTypeDefender == FIGHTER) {
				baseDamage = DAMAGE_ANTI_AIR_FIGHTER;
			} else if (unitTypeDefender == BOMBER) {
				baseDamage = DAMAGE_ANTI_AIR_BOMBER;
			} else if (unitTypeDefender == STEALTH) {
				baseDamage = DAMAGE_ANTI_AIR_STEALTH;
			} else if (unitTypeDefender == LANDER) {
				baseDamage = DAMAGE_ANTI_AIR_LANDER;
			} else if (unitTypeDefender == CRUISER) {
				baseDamage = DAMAGE_ANTI_AIR_CRUISER;
			} else if (unitTypeDefender == SUB) {
				baseDamage = DAMAGE_ANTI_AIR_SUB;
			} else if (unitTypeDefender == BATT_SHIP) {
				baseDamage = DAMAGE_ANTI_AIR_BATT_SHIP;
			} else if (unitTypeDefender == CARRIER) {
				baseDamage = DAMAGE_ANTI_AIR_CARRIER;
			}
		} else if (unitTypeAttacker == MISSILES) {
			if (unitTypeDefender == INFANTRY) {
				baseDamage = DAMAGE_MISSILES_INFANTRY;
			} else if (unitTypeDefender == MECH) {
				baseDamage = DAMAGE_MISSILES_MECH;
			} else if (unitTypeDefender == RECON) {
				baseDamage = DAMAGE_MISSILES_RECON;
			} else if (unitTypeDefender == TANK) {
				baseDamage = DAMAGE_MISSILES_TANK;
			} else if (unitTypeDefender == MD_TANK) {
				baseDamage = DAMAGE_MISSILES_MD_TANK;
			} else if (unitTypeDefender == NEOTANK) {
				baseDamage = DAMAGE_MISSILES_NEOTANK;
			} else if (unitTypeDefender == MEGATANK) {
				baseDamage = DAMAGE_MISSILES_MEGATANK;
			} else if (unitTypeDefender == APC) {
				baseDamage = DAMAGE_MISSILES_APC;
			} else if (unitTypeDefender == ARTILLERY) {
				baseDamage = DAMAGE_MISSILES_ARTILLERY;
			} else if (unitTypeDefender == ROCKETS) {
				baseDamage = DAMAGE_MISSILES_ROCKETS;
			} else if (unitTypeDefender == ANTI_AIR) {
				baseDamage = DAMAGE_MISSILES_ANTI_AIR;
			} else if (unitTypeDefender == MISSILES) {
				baseDamage = DAMAGE_MISSILES_MISSILES;
			} else if (unitTypeDefender == BATT_COP) {
				baseDamage = DAMAGE_MISSILES_BATT_COP;
			} else if (unitTypeDefender == TRAN_COP) {
				baseDamage = DAMAGE_MISSILES_TRAN_COP;
			} else if (unitTypeDefender == FIGHTER) {
				baseDamage = DAMAGE_MISSILES_FIGHTER;
			} else if (unitTypeDefender == BOMBER) {
				baseDamage = DAMAGE_MISSILES_BOMBER;
			} else if (unitTypeDefender == STEALTH) {
				baseDamage = DAMAGE_MISSILES_STEALTH;
			} else if (unitTypeDefender == LANDER) {
				baseDamage = DAMAGE_MISSILES_LANDER;
			} else if (unitTypeDefender == CRUISER) {
				baseDamage = DAMAGE_MISSILES_CRUISER;
			} else if (unitTypeDefender == SUB) {
				baseDamage = DAMAGE_MISSILES_SUB;
			} else if (unitTypeDefender == BATT_SHIP) {
				baseDamage = DAMAGE_MISSILES_BATT_SHIP;
			} else if (unitTypeDefender == CARRIER) {
				baseDamage = DAMAGE_MISSILES_CARRIER;
			}
		} else if (unitTypeAttacker == BATT_COP) {
			if (unitTypeDefender == INFANTRY) {
				baseDamage = DAMAGE_BATT_COP_INFANTRY;
			} else if (unitTypeDefender == MECH) {
				baseDamage = DAMAGE_BATT_COP_MECH;
			} else if (unitTypeDefender == RECON) {
				baseDamage = DAMAGE_BATT_COP_RECON;
			} else if (unitTypeDefender == TANK) {
				baseDamage = DAMAGE_BATT_COP_TANK;
			} else if (unitTypeDefender == MD_TANK) {
				baseDamage = DAMAGE_BATT_COP_MD_TANK;
			} else if (unitTypeDefender == NEOTANK) {
				baseDamage = DAMAGE_BATT_COP_NEOTANK;
			} else if (unitTypeDefender == MEGATANK) {
				baseDamage = DAMAGE_BATT_COP_MEGATANK;
			} else if (unitTypeDefender == APC) {
				baseDamage = DAMAGE_BATT_COP_APC;
			} else if (unitTypeDefender == ARTILLERY) {
				baseDamage = DAMAGE_BATT_COP_ARTILLERY;
			} else if (unitTypeDefender == ROCKETS) {
				baseDamage = DAMAGE_BATT_COP_ROCKETS;
			} else if (unitTypeDefender == ANTI_AIR) {
				baseDamage = DAMAGE_BATT_COP_ANTI_AIR;
			} else if (unitTypeDefender == MISSILES) {
				baseDamage = DAMAGE_BATT_COP_MISSILES;
			} else if (unitTypeDefender == BATT_COP) {
				baseDamage = DAMAGE_BATT_COP_BATT_COP;
			} else if (unitTypeDefender == TRAN_COP) {
				baseDamage = DAMAGE_BATT_COP_TRAN_COP;
			} else if (unitTypeDefender == FIGHTER) {
				baseDamage = DAMAGE_BATT_COP_FIGHTER;
			} else if (unitTypeDefender == BOMBER) {
				baseDamage = DAMAGE_BATT_COP_BOMBER;
			} else if (unitTypeDefender == STEALTH) {
				baseDamage = DAMAGE_BATT_COP_STEALTH;
			} else if (unitTypeDefender == LANDER) {
				baseDamage = DAMAGE_BATT_COP_LANDER;
			} else if (unitTypeDefender == CRUISER) {
				baseDamage = DAMAGE_BATT_COP_CRUISER;
			} else if (unitTypeDefender == SUB) {
				baseDamage = DAMAGE_BATT_COP_SUB;
			} else if (unitTypeDefender == BATT_SHIP) {
				baseDamage = DAMAGE_BATT_COP_BATT_SHIP;
			} else if (unitTypeDefender == CARRIER) {
				baseDamage = DAMAGE_BATT_COP_CARRIER;
			}
		} else if (unitTypeAttacker == FIGHTER) {
			if (unitTypeDefender == INFANTRY) {
				baseDamage = DAMAGE_FIGHTER_INFANTRY;
			} else if (unitTypeDefender == MECH) {
				baseDamage = DAMAGE_FIGHTER_MECH;
			} else if (unitTypeDefender == RECON) {
				baseDamage = DAMAGE_FIGHTER_RECON;
			} else if (unitTypeDefender == TANK) {
				baseDamage = DAMAGE_FIGHTER_TANK;
			} else if (unitTypeDefender == MD_TANK) {
				baseDamage = DAMAGE_FIGHTER_MD_TANK;
			} else if (unitTypeDefender == NEOTANK) {
				baseDamage = DAMAGE_FIGHTER_NEOTANK;
			} else if (unitTypeDefender == MEGATANK) {
				baseDamage = DAMAGE_FIGHTER_MEGATANK;
			} else if (unitTypeDefender == APC) {
				baseDamage = DAMAGE_FIGHTER_APC;
			} else if (unitTypeDefender == ARTILLERY) {
				baseDamage = DAMAGE_FIGHTER_ARTILLERY;
			} else if (unitTypeDefender == ROCKETS) {
				baseDamage = DAMAGE_FIGHTER_ROCKETS;
			} else if (unitTypeDefender == ANTI_AIR) {
				baseDamage = DAMAGE_FIGHTER_ANTI_AIR;
			} else if (unitTypeDefender == MISSILES) {
				baseDamage = DAMAGE_FIGHTER_MISSILES;
			} else if (unitTypeDefender == BATT_COP) {
				baseDamage = DAMAGE_FIGHTER_BATT_COP;
			} else if (unitTypeDefender == TRAN_COP) {
				baseDamage = DAMAGE_FIGHTER_TRAN_COP;
			} else if (unitTypeDefender == FIGHTER) {
				baseDamage = DAMAGE_FIGHTER_FIGHTER;
			} else if (unitTypeDefender == BOMBER) {
				baseDamage = DAMAGE_FIGHTER_BOMBER;
			} else if (unitTypeDefender == STEALTH) {
				baseDamage = DAMAGE_FIGHTER_STEALTH;
			} else if (unitTypeDefender == LANDER) {
				baseDamage = DAMAGE_FIGHTER_LANDER;
			} else if (unitTypeDefender == CRUISER) {
				baseDamage = DAMAGE_FIGHTER_CRUISER;
			} else if (unitTypeDefender == SUB) {
				baseDamage = DAMAGE_FIGHTER_SUB;
			} else if (unitTypeDefender == BATT_SHIP) {
				baseDamage = DAMAGE_FIGHTER_BATT_SHIP;
			} else if (unitTypeDefender == CARRIER) {
				baseDamage = DAMAGE_FIGHTER_CARRIER;
			}
		} else if (unitTypeAttacker == BOMBER) {
			if (unitTypeDefender == INFANTRY) {
				baseDamage = DAMAGE_BOMBER_INFANTRY;
			} else if (unitTypeDefender == MECH) {
				baseDamage = DAMAGE_BOMBER_MECH;
			} else if (unitTypeDefender == RECON) {
				baseDamage = DAMAGE_BOMBER_RECON;
			} else if (unitTypeDefender == TANK) {
				baseDamage = DAMAGE_BOMBER_TANK;
			} else if (unitTypeDefender == MD_TANK) {
				baseDamage = DAMAGE_BOMBER_MD_TANK;
			} else if (unitTypeDefender == NEOTANK) {
				baseDamage = DAMAGE_BOMBER_NEOTANK;
			} else if (unitTypeDefender == MEGATANK) {
				baseDamage = DAMAGE_BOMBER_MEGATANK;
			} else if (unitTypeDefender == APC) {
				baseDamage = DAMAGE_BOMBER_APC;
			} else if (unitTypeDefender == ARTILLERY) {
				baseDamage = DAMAGE_BOMBER_ARTILLERY;
			} else if (unitTypeDefender == ROCKETS) {
				baseDamage = DAMAGE_BOMBER_ROCKETS;
			} else if (unitTypeDefender == ANTI_AIR) {
				baseDamage = DAMAGE_BOMBER_ANTI_AIR;
			} else if (unitTypeDefender == MISSILES) {
				baseDamage = DAMAGE_BOMBER_MISSILES;
			} else if (unitTypeDefender == BATT_COP) {
				baseDamage = DAMAGE_BOMBER_BATT_COP;
			} else if (unitTypeDefender == TRAN_COP) {
				baseDamage = DAMAGE_BOMBER_TRAN_COP;
			} else if (unitTypeDefender == FIGHTER) {
				baseDamage = DAMAGE_BOMBER_FIGHTER;
			} else if (unitTypeDefender == BOMBER) {
				baseDamage = DAMAGE_BOMBER_BOMBER;
			} else if (unitTypeDefender == STEALTH) {
				baseDamage = DAMAGE_BOMBER_STEALTH;
			} else if (unitTypeDefender == LANDER) {
				baseDamage = DAMAGE_BOMBER_LANDER;
			} else if (unitTypeDefender == CRUISER) {
				baseDamage = DAMAGE_BOMBER_CRUISER;
			} else if (unitTypeDefender == SUB) {
				baseDamage = DAMAGE_BOMBER_SUB;
			} else if (unitTypeDefender == BATT_SHIP) {
				baseDamage = DAMAGE_BOMBER_BATT_SHIP;
			} else if (unitTypeDefender == CARRIER) {
				baseDamage = DAMAGE_BOMBER_CARRIER;
			}
		} else if (unitTypeAttacker == STEALTH) {
			if (unitTypeDefender == INFANTRY) {
				baseDamage = DAMAGE_STEALTH_INFANTRY;
			} else if (unitTypeDefender == MECH) {
				baseDamage = DAMAGE_STEALTH_MECH;
			} else if (unitTypeDefender == RECON) {
				baseDamage = DAMAGE_STEALTH_RECON;
			} else if (unitTypeDefender == TANK) {
				baseDamage = DAMAGE_STEALTH_TANK;
			} else if (unitTypeDefender == MD_TANK) {
				baseDamage = DAMAGE_STEALTH_MD_TANK;
			} else if (unitTypeDefender == NEOTANK) {
				baseDamage = DAMAGE_STEALTH_NEOTANK;
			} else if (unitTypeDefender == MEGATANK) {
				baseDamage = DAMAGE_STEALTH_MEGATANK;
			} else if (unitTypeDefender == APC) {
				baseDamage = DAMAGE_STEALTH_APC;
			} else if (unitTypeDefender == ARTILLERY) {
				baseDamage = DAMAGE_STEALTH_ARTILLERY;
			} else if (unitTypeDefender == ROCKETS) {
				baseDamage = DAMAGE_STEALTH_ROCKETS;
			} else if (unitTypeDefender == ANTI_AIR) {
				baseDamage = DAMAGE_STEALTH_ANTI_AIR;
			} else if (unitTypeDefender == MISSILES) {
				baseDamage = DAMAGE_STEALTH_MISSILES;
			} else if (unitTypeDefender == BATT_COP) {
				baseDamage = DAMAGE_STEALTH_BATT_COP;
			} else if (unitTypeDefender == TRAN_COP) {
				baseDamage = DAMAGE_STEALTH_TRAN_COP;
			} else if (unitTypeDefender == FIGHTER) {
				baseDamage = DAMAGE_STEALTH_FIGHTER;
			} else if (unitTypeDefender == BOMBER) {
				baseDamage = DAMAGE_STEALTH_BOMBER;
			} else if (unitTypeDefender == STEALTH) {
				baseDamage = DAMAGE_STEALTH_STEALTH;
			} else if (unitTypeDefender == LANDER) {
				baseDamage = DAMAGE_STEALTH_LANDER;
			} else if (unitTypeDefender == CRUISER) {
				baseDamage = DAMAGE_STEALTH_CRUISER;
			} else if (unitTypeDefender == SUB) {
				baseDamage = DAMAGE_STEALTH_SUB;
			} else if (unitTypeDefender == BATT_SHIP) {
				baseDamage = DAMAGE_STEALTH_BATT_SHIP;
			} else if (unitTypeDefender == CARRIER) {
				baseDamage = DAMAGE_STEALTH_CARRIER;
			}
		} else if (unitTypeAttacker == CRUISER) {
			if (unitTypeDefender == INFANTRY) {
				baseDamage = DAMAGE_CRUISER_INFANTRY;
			} else if (unitTypeDefender == MECH) {
				baseDamage = DAMAGE_CRUISER_MECH;
			} else if (unitTypeDefender == RECON) {
				baseDamage = DAMAGE_CRUISER_RECON;
			} else if (unitTypeDefender == TANK) {
				baseDamage = DAMAGE_CRUISER_TANK;
			} else if (unitTypeDefender == MD_TANK) {
				baseDamage = DAMAGE_CRUISER_MD_TANK;
			} else if (unitTypeDefender == NEOTANK) {
				baseDamage = DAMAGE_CRUISER_NEOTANK;
			} else if (unitTypeDefender == MEGATANK) {
				baseDamage = DAMAGE_CRUISER_MEGATANK;
			} else if (unitTypeDefender == APC) {
				baseDamage = DAMAGE_CRUISER_APC;
			} else if (unitTypeDefender == ARTILLERY) {
				baseDamage = DAMAGE_CRUISER_ARTILLERY;
			} else if (unitTypeDefender == ROCKETS) {
				baseDamage = DAMAGE_CRUISER_ROCKETS;
			} else if (unitTypeDefender == ANTI_AIR) {
				baseDamage = DAMAGE_CRUISER_ANTI_AIR;
			} else if (unitTypeDefender == MISSILES) {
				baseDamage = DAMAGE_CRUISER_MISSILES;
			} else if (unitTypeDefender == BATT_COP) {
				baseDamage = DAMAGE_CRUISER_BATT_COP;
			} else if (unitTypeDefender == TRAN_COP) {
				baseDamage = DAMAGE_CRUISER_TRAN_COP;
			} else if (unitTypeDefender == FIGHTER) {
				baseDamage = DAMAGE_CRUISER_FIGHTER;
			} else if (unitTypeDefender == BOMBER) {
				baseDamage = DAMAGE_CRUISER_BOMBER;
			} else if (unitTypeDefender == STEALTH) {
				baseDamage = DAMAGE_CRUISER_STEALTH;
			} else if (unitTypeDefender == LANDER) {
				baseDamage = DAMAGE_CRUISER_LANDER;
			} else if (unitTypeDefender == CRUISER) {
				baseDamage = DAMAGE_CRUISER_CRUISER;
			} else if (unitTypeDefender == SUB) {
				baseDamage = DAMAGE_CRUISER_SUB;
			} else if (unitTypeDefender == BATT_SHIP) {
				baseDamage = DAMAGE_CRUISER_BATT_SHIP;
			} else if (unitTypeDefender == CARRIER) {
				baseDamage = DAMAGE_CRUISER_CARRIER;
			}
		} else if (unitTypeAttacker == SUB) {
			if (unitTypeDefender == INFANTRY) {
				baseDamage = DAMAGE_SUB_INFANTRY;
			} else if (unitTypeDefender == MECH) {
				baseDamage = DAMAGE_SUB_MECH;
			} else if (unitTypeDefender == RECON) {
				baseDamage = DAMAGE_SUB_RECON;
			} else if (unitTypeDefender == TANK) {
				baseDamage = DAMAGE_SUB_TANK;
			} else if (unitTypeDefender == MD_TANK) {
				baseDamage = DAMAGE_SUB_MD_TANK;
			} else if (unitTypeDefender == NEOTANK) {
				baseDamage = DAMAGE_SUB_NEOTANK;
			} else if (unitTypeDefender == MEGATANK) {
				baseDamage = DAMAGE_SUB_MEGATANK;
			} else if (unitTypeDefender == APC) {
				baseDamage = DAMAGE_SUB_APC;
			} else if (unitTypeDefender == ARTILLERY) {
				baseDamage = DAMAGE_SUB_ARTILLERY;
			} else if (unitTypeDefender == ROCKETS) {
				baseDamage = DAMAGE_SUB_ROCKETS;
			} else if (unitTypeDefender == ANTI_AIR) {
				baseDamage = DAMAGE_SUB_ANTI_AIR;
			} else if (unitTypeDefender == MISSILES) {
				baseDamage = DAMAGE_SUB_MISSILES;
			} else if (unitTypeDefender == BATT_COP) {
				baseDamage = DAMAGE_SUB_BATT_COP;
			} else if (unitTypeDefender == TRAN_COP) {
				baseDamage = DAMAGE_SUB_TRAN_COP;
			} else if (unitTypeDefender == FIGHTER) {
				baseDamage = DAMAGE_SUB_FIGHTER;
			} else if (unitTypeDefender == BOMBER) {
				baseDamage = DAMAGE_SUB_BOMBER;
			} else if (unitTypeDefender == STEALTH) {
				baseDamage = DAMAGE_SUB_STEALTH;
			} else if (unitTypeDefender == LANDER) {
				baseDamage = DAMAGE_SUB_LANDER;
			} else if (unitTypeDefender == CRUISER) {
				baseDamage = DAMAGE_SUB_CRUISER;
			} else if (unitTypeDefender == SUB) {
				baseDamage = DAMAGE_SUB_SUB;
			} else if (unitTypeDefender == BATT_SHIP) {
				baseDamage = DAMAGE_SUB_BATT_SHIP;
			} else if (unitTypeDefender == CARRIER) {
				baseDamage = DAMAGE_SUB_CARRIER;
			}
		} else if (unitTypeAttacker == BATT_SHIP) {
			if (unitTypeDefender == INFANTRY) {
				baseDamage = DAMAGE_BATT_SHIP_INFANTRY;
			} else if (unitTypeDefender == MECH) {
				baseDamage = DAMAGE_BATT_SHIP_MECH;
			} else if (unitTypeDefender == RECON) {
				baseDamage = DAMAGE_BATT_SHIP_RECON;
			} else if (unitTypeDefender == TANK) {
				baseDamage = DAMAGE_BATT_SHIP_TANK;
			} else if (unitTypeDefender == MD_TANK) {
				baseDamage = DAMAGE_BATT_SHIP_MD_TANK;
			} else if (unitTypeDefender == NEOTANK) {
				baseDamage = DAMAGE_BATT_SHIP_NEOTANK;
			} else if (unitTypeDefender == MEGATANK) {
				baseDamage = DAMAGE_BATT_SHIP_MEGATANK;
			} else if (unitTypeDefender == APC) {
				baseDamage = DAMAGE_BATT_SHIP_APC;
			} else if (unitTypeDefender == ARTILLERY) {
				baseDamage = DAMAGE_BATT_SHIP_ARTILLERY;
			} else if (unitTypeDefender == ROCKETS) {
				baseDamage = DAMAGE_BATT_SHIP_ROCKETS;
			} else if (unitTypeDefender == ANTI_AIR) {
				baseDamage = DAMAGE_BATT_SHIP_ANTI_AIR;
			} else if (unitTypeDefender == MISSILES) {
				baseDamage = DAMAGE_BATT_SHIP_MISSILES;
			} else if (unitTypeDefender == BATT_COP) {
				baseDamage = DAMAGE_BATT_SHIP_BATT_COP;
			} else if (unitTypeDefender == TRAN_COP) {
				baseDamage = DAMAGE_BATT_SHIP_TRAN_COP;
			} else if (unitTypeDefender == FIGHTER) {
				baseDamage = DAMAGE_BATT_SHIP_FIGHTER;
			} else if (unitTypeDefender == BOMBER) {
				baseDamage = DAMAGE_BATT_SHIP_BOMBER;
			} else if (unitTypeDefender == STEALTH) {
				baseDamage = DAMAGE_BATT_SHIP_STEALTH;
			} else if (unitTypeDefender == LANDER) {
				baseDamage = DAMAGE_BATT_SHIP_LANDER;
			} else if (unitTypeDefender == CRUISER) {
				baseDamage = DAMAGE_BATT_SHIP_CRUISER;
			} else if (unitTypeDefender == SUB) {
				baseDamage = DAMAGE_BATT_SHIP_SUB;
			} else if (unitTypeDefender == BATT_SHIP) {
				baseDamage = DAMAGE_BATT_SHIP_BATT_SHIP;
			} else if (unitTypeDefender == CARRIER) {
				baseDamage = DAMAGE_BATT_SHIP_CARRIER;
			}
		} else if (unitTypeAttacker == CARRIER) {
			if (unitTypeDefender == INFANTRY) {
				baseDamage = DAMAGE_CARRIER_INFANTRY;
			} else if (unitTypeDefender == MECH) {
				baseDamage = DAMAGE_CARRIER_MECH;
			} else if (unitTypeDefender == RECON) {
				baseDamage = DAMAGE_CARRIER_RECON;
			} else if (unitTypeDefender == TANK) {
				baseDamage = DAMAGE_CARRIER_TANK;
			} else if (unitTypeDefender == MD_TANK) {
				baseDamage = DAMAGE_CARRIER_MD_TANK;
			} else if (unitTypeDefender == NEOTANK) {
				baseDamage = DAMAGE_CARRIER_NEOTANK;
			} else if (unitTypeDefender == MEGATANK) {
				baseDamage = DAMAGE_CARRIER_MEGATANK;
			} else if (unitTypeDefender == APC) {
				baseDamage = DAMAGE_CARRIER_APC;
			} else if (unitTypeDefender == ARTILLERY) {
				baseDamage = DAMAGE_CARRIER_ARTILLERY;
			} else if (unitTypeDefender == ROCKETS) {
				baseDamage = DAMAGE_CARRIER_ROCKETS;
			} else if (unitTypeDefender == ANTI_AIR) {
				baseDamage = DAMAGE_CARRIER_ANTI_AIR;
			} else if (unitTypeDefender == MISSILES) {
				baseDamage = DAMAGE_CARRIER_MISSILES;
			} else if (unitTypeDefender == BATT_COP) {
				baseDamage = DAMAGE_CARRIER_BATT_COP;
			} else if (unitTypeDefender == TRAN_COP) {
				baseDamage = DAMAGE_CARRIER_TRAN_COP;
			} else if (unitTypeDefender == FIGHTER) {
				baseDamage = DAMAGE_CARRIER_FIGHTER;
			} else if (unitTypeDefender == BOMBER) {
				baseDamage = DAMAGE_CARRIER_BOMBER;
			} else if (unitTypeDefender == STEALTH) {
				baseDamage = DAMAGE_CARRIER_STEALTH;
			} else if (unitTypeDefender == LANDER) {
				baseDamage = DAMAGE_CARRIER_LANDER;
			} else if (unitTypeDefender == CRUISER) {
				baseDamage = DAMAGE_CARRIER_CRUISER;
			} else if (unitTypeDefender == SUB) {
				baseDamage = DAMAGE_CARRIER_SUB;
			} else if (unitTypeDefender == BATT_SHIP) {
				baseDamage = DAMAGE_CARRIER_BATT_SHIP;
			} else if (unitTypeDefender == CARRIER) {
				baseDamage = DAMAGE_CARRIER_CARRIER;
			}
		}
	} else if (weapon == SECONDARY) {
		if (unitTypeAttacker == MECH) {
			if (unitTypeDefender == INFANTRY) {
				baseDamage = DAMAGE_MECH_INFANTRY_2;
			} else if (unitTypeDefender == MECH) {
				baseDamage = DAMAGE_MECH_MECH_2;
			} else if (unitTypeDefender == RECON) {
				baseDamage = DAMAGE_MECH_RECON_2;
			} else if (unitTypeDefender == TANK) {
				baseDamage = DAMAGE_MECH_TANK_2;
			} else if (unitTypeDefender == MD_TANK) {
				baseDamage = DAMAGE_MECH_MD_TANK_2;
			} else if (unitTypeDefender == NEOTANK) {
				baseDamage = DAMAGE_MECH_NEOTANK_2;
			} else if (unitTypeDefender == MEGATANK) {
				baseDamage = DAMAGE_MECH_MEGATANK_2;
			} else if (unitTypeDefender == APC) {
				baseDamage = DAMAGE_MECH_APC_2;
			} else if (unitTypeDefender == ARTILLERY) {
				baseDamage = DAMAGE_MECH_ARTILLERY_2;
			} else if (unitTypeDefender == ROCKETS) {
				baseDamage = DAMAGE_MECH_ROCKETS_2;
			} else if (unitTypeDefender == ANTI_AIR) {
				baseDamage = DAMAGE_MECH_ANTI_AIR_2;
			} else if (unitTypeDefender == MISSILES) {
				baseDamage = DAMAGE_MECH_MISSILES_2;
			} else if (unitTypeDefender == BATT_COP) {
				baseDamage = DAMAGE_MECH_BATT_COP_2;
			} else if (unitTypeDefender == TRAN_COP) {
				baseDamage = DAMAGE_MECH_TRAN_COP_2;
			} else if (unitTypeDefender == FIGHTER) {
				baseDamage = DAMAGE_MECH_FIGHTER_2;
			} else if (unitTypeDefender == BOMBER) {
				baseDamage = DAMAGE_MECH_BOMBER_2;
			} else if (unitTypeDefender == STEALTH) {
				baseDamage = DAMAGE_MECH_STEALTH_2;
			} else if (unitTypeDefender == LANDER) {
				baseDamage = DAMAGE_MECH_LANDER_2;
			} else if (unitTypeDefender == CRUISER) {
				baseDamage = DAMAGE_MECH_CRUISER_2;
			} else if (unitTypeDefender == SUB) {
				baseDamage = DAMAGE_MECH_SUB_2;
			} else if (unitTypeDefender == BATT_SHIP) {
				baseDamage = DAMAGE_MECH_BATT_SHIP_2;
			} else if (unitTypeDefender == CARRIER) {
				baseDamage = DAMAGE_MECH_CARRIER_2;
			}
		} else if (unitTypeAttacker == TANK) {
			if (unitTypeDefender == INFANTRY) {
				baseDamage = DAMAGE_TANK_INFANTRY_2;
			} else if (unitTypeDefender == MECH) {
				baseDamage = DAMAGE_TANK_MECH_2;
			} else if (unitTypeDefender == RECON) {
				baseDamage = DAMAGE_TANK_RECON_2;
			} else if (unitTypeDefender == TANK) {
				baseDamage = DAMAGE_TANK_TANK_2;
			} else if (unitTypeDefender == MD_TANK) {
				baseDamage = DAMAGE_TANK_MD_TANK_2;
			} else if (unitTypeDefender == NEOTANK) {
				baseDamage = DAMAGE_TANK_NEOTANK_2;
			} else if (unitTypeDefender == MEGATANK) {
				baseDamage = DAMAGE_TANK_MEGATANK_2;
			} else if (unitTypeDefender == APC) {
				baseDamage = DAMAGE_TANK_APC_2;
			} else if (unitTypeDefender == ARTILLERY) {
				baseDamage = DAMAGE_TANK_ARTILLERY_2;
			} else if (unitTypeDefender == ROCKETS) {
				baseDamage = DAMAGE_TANK_ROCKETS_2;
			} else if (unitTypeDefender == ANTI_AIR) {
				baseDamage = DAMAGE_TANK_ANTI_AIR_2;
			} else if (unitTypeDefender == MISSILES) {
				baseDamage = DAMAGE_TANK_MISSILES_2;
			} else if (unitTypeDefender == BATT_COP) {
				baseDamage = DAMAGE_TANK_BATT_COP_2;
			} else if (unitTypeDefender == TRAN_COP) {
				baseDamage = DAMAGE_TANK_TRAN_COP_2;
			} else if (unitTypeDefender == FIGHTER) {
				baseDamage = DAMAGE_TANK_FIGHTER_2;
			} else if (unitTypeDefender == BOMBER) {
				baseDamage = DAMAGE_TANK_BOMBER_2;
			} else if (unitTypeDefender == STEALTH) {
				baseDamage = DAMAGE_TANK_STEALTH_2;
			} else if (unitTypeDefender == LANDER) {
				baseDamage = DAMAGE_TANK_LANDER_2;
			} else if (unitTypeDefender == CRUISER) {
				baseDamage = DAMAGE_TANK_CRUISER_2;
			} else if (unitTypeDefender == SUB) {
				baseDamage = DAMAGE_TANK_SUB_2;
			} else if (unitTypeDefender == BATT_SHIP) {
				baseDamage = DAMAGE_TANK_BATT_SHIP_2;
			} else if (unitTypeDefender == CARRIER) {
				baseDamage = DAMAGE_TANK_CARRIER_2;
			}
		} else if (unitTypeAttacker == MD_TANK) {
			if (unitTypeDefender == INFANTRY) {
				baseDamage = DAMAGE_MD_TANK_INFANTRY_2;
			} else if (unitTypeDefender == MECH) {
				baseDamage = DAMAGE_MD_TANK_MECH_2;
			} else if (unitTypeDefender == RECON) {
				baseDamage = DAMAGE_MD_TANK_RECON_2;
			} else if (unitTypeDefender == TANK) {
				baseDamage = DAMAGE_MD_TANK_TANK_2;
			} else if (unitTypeDefender == MD_TANK) {
				baseDamage = DAMAGE_MD_TANK_MD_TANK_2;
			} else if (unitTypeDefender == NEOTANK) {
				baseDamage = DAMAGE_MD_TANK_NEOTANK_2;
			} else if (unitTypeDefender == MEGATANK) {
				baseDamage = DAMAGE_MD_TANK_MEGATANK_2;
			} else if (unitTypeDefender == APC) {
				baseDamage = DAMAGE_MD_TANK_APC_2;
			} else if (unitTypeDefender == ARTILLERY) {
				baseDamage = DAMAGE_MD_TANK_ARTILLERY_2;
			} else if (unitTypeDefender == ROCKETS) {
				baseDamage = DAMAGE_MD_TANK_ROCKETS_2;
			} else if (unitTypeDefender == ANTI_AIR) {
				baseDamage = DAMAGE_MD_TANK_ANTI_AIR_2;
			} else if (unitTypeDefender == MISSILES) {
				baseDamage = DAMAGE_MD_TANK_MISSILES_2;
			} else if (unitTypeDefender == BATT_COP) {
				baseDamage = DAMAGE_MD_TANK_BATT_COP_2;
			} else if (unitTypeDefender == TRAN_COP) {
				baseDamage = DAMAGE_MD_TANK_TRAN_COP_2;
			} else if (unitTypeDefender == FIGHTER) {
				baseDamage = DAMAGE_MD_TANK_FIGHTER_2;
			} else if (unitTypeDefender == BOMBER) {
				baseDamage = DAMAGE_MD_TANK_BOMBER_2;
			} else if (unitTypeDefender == STEALTH) {
				baseDamage = DAMAGE_MD_TANK_STEALTH_2;
			} else if (unitTypeDefender == LANDER) {
				baseDamage = DAMAGE_MD_TANK_LANDER_2;
			} else if (unitTypeDefender == CRUISER) {
				baseDamage = DAMAGE_MD_TANK_CRUISER_2;
			} else if (unitTypeDefender == SUB) {
				baseDamage = DAMAGE_MD_TANK_SUB_2;
			} else if (unitTypeDefender == BATT_SHIP) {
				baseDamage = DAMAGE_MD_TANK_BATT_SHIP_2;
			} else if (unitTypeDefender == CARRIER) {
				baseDamage = DAMAGE_MD_TANK_CARRIER_2;
			}
		} else if (unitTypeAttacker == NEOTANK) {
			if (unitTypeDefender == INFANTRY) {
				baseDamage = DAMAGE_NEOTANK_INFANTRY_2;
			} else if (unitTypeDefender == MECH) {
				baseDamage = DAMAGE_NEOTANK_MECH_2;
			} else if (unitTypeDefender == RECON) {
				baseDamage = DAMAGE_NEOTANK_RECON_2;
			} else if (unitTypeDefender == TANK) {
				baseDamage = DAMAGE_NEOTANK_TANK_2;
			} else if (unitTypeDefender == MD_TANK) {
				baseDamage = DAMAGE_NEOTANK_MD_TANK_2;
			} else if (unitTypeDefender == NEOTANK) {
				baseDamage = DAMAGE_NEOTANK_NEOTANK_2;
			} else if (unitTypeDefender == MEGATANK) {
				baseDamage = DAMAGE_NEOTANK_MEGATANK_2;
			} else if (unitTypeDefender == APC) {
				baseDamage = DAMAGE_NEOTANK_APC_2;
			} else if (unitTypeDefender == ARTILLERY) {
				baseDamage = DAMAGE_NEOTANK_ARTILLERY_2;
			} else if (unitTypeDefender == ROCKETS) {
				baseDamage = DAMAGE_NEOTANK_ROCKETS_2;
			} else if (unitTypeDefender == ANTI_AIR) {
				baseDamage = DAMAGE_NEOTANK_ANTI_AIR_2;
			} else if (unitTypeDefender == MISSILES) {
				baseDamage = DAMAGE_NEOTANK_MISSILES_2;
			} else if (unitTypeDefender == BATT_COP) {
				baseDamage = DAMAGE_NEOTANK_BATT_COP_2;
			} else if (unitTypeDefender == TRAN_COP) {
				baseDamage = DAMAGE_NEOTANK_TRAN_COP_2;
			} else if (unitTypeDefender == FIGHTER) {
				baseDamage = DAMAGE_NEOTANK_FIGHTER_2;
			} else if (unitTypeDefender == BOMBER) {
				baseDamage = DAMAGE_NEOTANK_BOMBER_2;
			} else if (unitTypeDefender == STEALTH) {
				baseDamage = DAMAGE_NEOTANK_STEALTH_2;
			} else if (unitTypeDefender == LANDER) {
				baseDamage = DAMAGE_NEOTANK_LANDER_2;
			} else if (unitTypeDefender == CRUISER) {
				baseDamage = DAMAGE_NEOTANK_CRUISER_2;
			} else if (unitTypeDefender == SUB) {
				baseDamage = DAMAGE_NEOTANK_SUB_2;
			} else if (unitTypeDefender == BATT_SHIP) {
				baseDamage = DAMAGE_NEOTANK_BATT_SHIP_2;
			} else if (unitTypeDefender == CARRIER) {
				baseDamage = DAMAGE_NEOTANK_CARRIER_2;
			}
		} else if (unitTypeAttacker == MEGATANK) {
			if (unitTypeDefender == INFANTRY) {
				baseDamage = DAMAGE_MEGATANK_INFANTRY_2;
			} else if (unitTypeDefender == MECH) {
				baseDamage = DAMAGE_MEGATANK_MECH_2;
			} else if (unitTypeDefender == RECON) {
				baseDamage = DAMAGE_MEGATANK_RECON_2;
			} else if (unitTypeDefender == TANK) {
				baseDamage = DAMAGE_MEGATANK_TANK_2;
			} else if (unitTypeDefender == MD_TANK) {
				baseDamage = DAMAGE_MEGATANK_MD_TANK_2;
			} else if (unitTypeDefender == NEOTANK) {
				baseDamage = DAMAGE_MEGATANK_NEOTANK_2;
			} else if (unitTypeDefender == MEGATANK) {
				baseDamage = DAMAGE_MEGATANK_MEGATANK_2;
			} else if (unitTypeDefender == APC) {
				baseDamage = DAMAGE_MEGATANK_APC_2;
			} else if (unitTypeDefender == ARTILLERY) {
				baseDamage = DAMAGE_MEGATANK_ARTILLERY_2;
			} else if (unitTypeDefender == ROCKETS) {
				baseDamage = DAMAGE_MEGATANK_ROCKETS_2;
			} else if (unitTypeDefender == ANTI_AIR) {
				baseDamage = DAMAGE_MEGATANK_ANTI_AIR_2;
			} else if (unitTypeDefender == MISSILES) {
				baseDamage = DAMAGE_MEGATANK_MISSILES_2;
			} else if (unitTypeDefender == BATT_COP) {
				baseDamage = DAMAGE_MEGATANK_BATT_COP_2;
			} else if (unitTypeDefender == TRAN_COP) {
				baseDamage = DAMAGE_MEGATANK_TRAN_COP_2;
			} else if (unitTypeDefender == FIGHTER) {
				baseDamage = DAMAGE_MEGATANK_FIGHTER_2;
			} else if (unitTypeDefender == BOMBER) {
				baseDamage = DAMAGE_MEGATANK_BOMBER_2;
			} else if (unitTypeDefender == STEALTH) {
				baseDamage = DAMAGE_MEGATANK_STEALTH_2;
			} else if (unitTypeDefender == LANDER) {
				baseDamage = DAMAGE_MEGATANK_LANDER_2;
			} else if (unitTypeDefender == CRUISER) {
				baseDamage = DAMAGE_MEGATANK_CRUISER_2;
			} else if (unitTypeDefender == SUB) {
				baseDamage = DAMAGE_MEGATANK_SUB_2;
			} else if (unitTypeDefender == BATT_SHIP) {
				baseDamage = DAMAGE_MEGATANK_BATT_SHIP_2;
			} else if (unitTypeDefender == CARRIER) {
				baseDamage = DAMAGE_MEGATANK_CARRIER_2;
			}
		}
	}
	
	return baseDamage;
}

/// This function returns the minimum range a unit can attack.
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

/// This function returns the maximum range a unit can attack.
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

/// This function returns what weapon a unit will use to attack an
/// opponent based on how much ammo it has, and whether that unit can
/// be damaged with that weapon.
char whichWeapon (game *data, short attacker, short defender) {
	/// This will only change if it CAN attack something.
	char whichWeapon = NONE;
	if ((baseDamageGetter(data, attacker, defender, PRIMARY) > 0) && ((data->unitData[attacker].ammo1 > 0) || (data->unitData[attacker].ammo1 == -1)) {
		whichWeapon = PRIMARY;
	} else if ((baseDamageGetter(data, attacker, defender, SECONDARY) > 0) && ((data->unitData[attacker].ammo2 > 0) || (data->unitData[attacker].ammo2 == -1))
		whichWeapon = SECONDARY;
	}
	
	return whichWeapon;
}

/// This function returns YES (1) if a unit is able to counter an
/// opponent, or NO (0) if it can't.
/// This function does not get called if the unit is destroyed.
char canItCounter (game *data, short attacker, short defender) {
	char canItCounter = NO;
	if ((minimumRangeGetter(data, defender) == 1) && (maximumRangeGetter(data, defender) == 1)) {
		if (validAttackChecker(data, defender, attacker) == YES) {
			canItCounter = YES;
		}
	}
	
	return canItCounter;
}

/// This function just double-checks the initialise values.
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