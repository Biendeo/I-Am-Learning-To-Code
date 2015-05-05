#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Defines.h"
#include "GameUI.h"
#include "MainGame.h"
#include "GameAI.h"
#include "FileIO.h"
#include "DrawingUI.h"
#include "rlutil.h"

/// This is just a splash screen for presentation.
void screenSplash() {
	setColor(GREY);
	printf("+------------------------------+\n");
	printf("|                              |\n");
	printf("|         ");
	setColor(LIGHTBLUE);
	printf("TERMINAL WARS");
	setColor(GREY);
	printf("        |\n");
	printf("|                              |\n");
	printf("+------------------------------+\n");
	printf("\n");
	printf("An attempt to recreate the game Advance Wars in C.\n");
	printf("\n");
	printf("Version \"Stage 10\"\n\n");
	
	/// This tells the user if their screen is too small.
	if (trows() < (MAP_HEIGHT + 10)) {
		printf("Your screen is too short to properly view this.\n");
		printf("Make your window taller to fit %d rows.\n\n", MAP_HEIGHT + 10);
	}
	// This magic number is just how roughly wide the screen needs to be.
	// I don't kow exactly how wide it should be.
	if ((tcols() < MAP_WIDTH) || (tcols() < 50)) {
		printf("Your screen is too thin to properly view this.\n");
		printf("Make your window wider to fit %d columns.\n\n", MAP_WIDTH + 10);
	}
	anykey();
}

void mapDraw(game *data) {
	short x = 0;
	short y = 0;
	short unitPos = 0;
	cls();
	while (y < MAP_HEIGHT) {
		while (x < MAP_WIDTH) {
			if (data->drawMode == DRAWMODE_UNITS) {
				unitPos = unitGetter(data, x, y);
				if (unitPos < MAX_UNITS && data->unitData[unitPos].player != TEAM_NONE) {
					drawUnit(data, x, y, unitPos);
				} else {
					drawField(data, x, y);
				}
			} else {
				drawField(data, x, y);
			}
			x++;
		}
		printf("\n");
		x = 0;
		y++;
	}
	setColor(GREY);
}

void drawUnit (game *data, short x, short y, short arrayPos) {
	if ((data->cursor.x == x) && (data->cursor.y == y)) {
		setColor(LIGHTMAGENTA);
	} else if (data->unitData[arrayPos].player == TEAM_RED) {
		setColor(LIGHTRED);
	} else if (data->unitData[arrayPos].player == TEAM_BLUE) {
		setColor(LIGHTBLUE);
	} else if (data->unitData[arrayPos].player == TEAM_GREEN) {
		setColor(LIGHTGREEN);
	} else if (data->unitData[arrayPos].player == TEAM_YELLOW) {
		setColor(YELLOW);
	}
	
	if (data->unitData[arrayPos].unitType == INFANTRY) {
		printf("%c", CHAR_INFANTRY);
	} else if (data->unitData[arrayPos].unitType == MECH) {
		printf("%c", CHAR_MECH);
	} else if (data->unitData[arrayPos].unitType == RECON) {
		printf("%c", CHAR_RECON);
	} else if (data->unitData[arrayPos].unitType == TANK) {
		printf("%c", CHAR_TANK);
	} else if (data->unitData[arrayPos].unitType == MD_TANK) {
		printf("%c", CHAR_MD_TANK);
	} else if (data->unitData[arrayPos].unitType == NEOTANK) {
		printf("%c", CHAR_NEOTANK);
	} else if (data->unitData[arrayPos].unitType == MEGATANK) {
		printf("%c", CHAR_MEGATANK);
	} else if (data->unitData[arrayPos].unitType == APC) {
		printf("%c", CHAR_APC);
	} else if (data->unitData[arrayPos].unitType == ARTILLERY) {
		printf("%c", CHAR_ARTILLERY);
	} else if (data->unitData[arrayPos].unitType == ROCKETS) {
		printf("%c", CHAR_ROCKETS);
	} else if (data->unitData[arrayPos].unitType == ANTI_AIR) {
		printf("%c", CHAR_ANTI_AIR);
	} else if (data->unitData[arrayPos].unitType == MISSILES) {
		printf("%c", CHAR_MISSILES);
	} else if (data->unitData[arrayPos].unitType == BATT_COP) {
		printf("%c", CHAR_BATT_COP);
	} else if (data->unitData[arrayPos].unitType == TRAN_COP) {
		printf("%c", CHAR_TRAN_COP);
	} else if (data->unitData[arrayPos].unitType == FIGHTER) {
		printf("%c", CHAR_FIGHTER);
	} else if (data->unitData[arrayPos].unitType == BOMBER) {
		printf("%c", CHAR_BOMBER);
	} else if (data->unitData[arrayPos].unitType == STEALTH) {
		printf("%c", CHAR_STEALTH);
	} else if (data->unitData[arrayPos].unitType == LANDER) {
		printf("%c", CHAR_LANDER);
	} else if (data->unitData[arrayPos].unitType == CRUISER) {
		printf("%c", CHAR_CRUISER);
	} else if (data->unitData[arrayPos].unitType == SUB) {
		printf("%c", CHAR_SUB);
	} else if (data->unitData[arrayPos].unitType == BATT_SHIP) {
		printf("%c", CHAR_BATT_SHIP);
	} else if (data->unitData[arrayPos].unitType == CARRIER) {
		printf("%c", CHAR_CARRIER);
	}
}

void drawField (game *data, short x, short y) {
	
	if ((data->cursor.x == x) && (data->cursor.y == y)) {
		setColor(LIGHTMAGENTA);
	} else if (data->mapData[x][y] == NULL_HQ) {
		setColor(WHITE);
	} else if (data->mapData[x][y] == NULL_CITY) {
		setColor(WHITE);
	} else if (data->mapData[x][y] == NULL_BASE) {
		setColor(WHITE);
	} else if (data->mapData[x][y] == NULL_AIRPORT) {
		setColor(WHITE);
	} else if (data->mapData[x][y] == NULL_PORT) {
		setColor(WHITE);
	} else if (data->mapData[x][y] == RED_HQ) {
		setColor(LIGHTRED);
	} else if (data->mapData[x][y] == RED_CITY) {
		setColor(LIGHTRED);
	} else if (data->mapData[x][y] == RED_BASE) {
		setColor(LIGHTRED);
	} else if (data->mapData[x][y] == RED_AIRPORT) {
		setColor(LIGHTRED);
	} else if (data->mapData[x][y] == RED_PORT) {
		setColor(LIGHTRED);
	} else if (data->mapData[x][y] == BLUE_HQ) {
		setColor(LIGHTBLUE);
	} else if (data->mapData[x][y] == BLUE_CITY) {
		setColor(LIGHTBLUE);
	} else if (data->mapData[x][y] == BLUE_BASE) {
		setColor(LIGHTBLUE);
	} else if (data->mapData[x][y] == BLUE_AIRPORT) {
		setColor(LIGHTBLUE);
	} else if (data->mapData[x][y] == BLUE_PORT) {
		setColor(LIGHTBLUE);
	} else if (data->mapData[x][y] == GREEN_HQ) {
		setColor(LIGHTGREEN);
	} else if (data->mapData[x][y] == GREEN_CITY) {
		setColor(LIGHTGREEN);
	} else if (data->mapData[x][y] == GREEN_BASE) {
		setColor(LIGHTGREEN);
	} else if (data->mapData[x][y] == GREEN_AIRPORT) {
		setColor(LIGHTGREEN);
	} else if (data->mapData[x][y] == GREEN_PORT) {
		setColor(LIGHTGREEN);
	} else if (data->mapData[x][y] == YELLOW_HQ) {
		setColor(YELLOW);
	} else if (data->mapData[x][y] == YELLOW_CITY) {
		setColor(YELLOW);
	} else if (data->mapData[x][y] == YELLOW_BASE) {
		setColor(YELLOW);
	} else if (data->mapData[x][y] == YELLOW_AIRPORT) {
		setColor(YELLOW);
	} else if (data->mapData[x][y] == YELLOW_PORT) {
		setColor(YELLOW);
	}
	else if (data->mapData[x][y] == PLAIN) {
		setColor(GREEN);
	} else if (data->mapData[x][y] == ROAD) {
		setColor(GREY);
	} else if (data->mapData[x][y] == SEA) {
		setColor(BLUE);
	} else if (data->mapData[x][y] == RIVER) {
		setColor(BLUE);
	} else if (data->mapData[x][y] == WOOD) {
		setColor(BROWN);
	} else if (data->mapData[x][y] == MOUNTAIN) {
		setColor(BROWN);
	} else if (data->mapData[x][y] == BRIDGE) {
		setColor(WHITE);
	} else if (data->mapData[x][y] == SHOAL) {
		setColor(BLUE);
	} else if (data->mapData[x][y] == REEF) {
		setColor(BLUE);
	}
	
	if (data->mapData[x][y] == NULL_HQ) {
		printf("%c", CHAR_MAP_HQ);
	} else if (data->mapData[x][y] == NULL_CITY) {
		printf("%c", CHAR_MAP_CITY);
	} else if (data->mapData[x][y] == NULL_BASE) {
		printf("%c", CHAR_MAP_BASE);
	} else if (data->mapData[x][y] == NULL_AIRPORT) {
		printf("%c", CHAR_MAP_AIRPORT);
	} else if (data->mapData[x][y] == NULL_PORT) {
		printf("%c", CHAR_MAP_PORT);
	} else if (data->mapData[x][y] == RED_HQ) {
		printf("%c", CHAR_MAP_HQ);
	} else if (data->mapData[x][y] == RED_CITY) {
		printf("%c", CHAR_MAP_CITY);
	} else if (data->mapData[x][y] == RED_BASE) {
		printf("%c", CHAR_MAP_BASE);
	} else if (data->mapData[x][y] == RED_AIRPORT) {
		printf("%c", CHAR_MAP_AIRPORT);
	} else if (data->mapData[x][y] == RED_PORT) {
		printf("%c", CHAR_MAP_PORT);
	} else if (data->mapData[x][y] == BLUE_HQ) {
		printf("%c", CHAR_MAP_HQ);
	} else if (data->mapData[x][y] == BLUE_CITY) {
		printf("%c", CHAR_MAP_CITY);
	} else if (data->mapData[x][y] == BLUE_BASE) {
		printf("%c", CHAR_MAP_BASE);
	} else if (data->mapData[x][y] == BLUE_AIRPORT) {
		printf("%c", CHAR_MAP_AIRPORT);
	} else if (data->mapData[x][y] == BLUE_PORT) {
		printf("%c", CHAR_MAP_PORT);
	} else if (data->mapData[x][y] == GREEN_HQ) {
		printf("%c", CHAR_MAP_HQ);
	} else if (data->mapData[x][y] == GREEN_CITY) {
		printf("%c", CHAR_MAP_CITY);
	} else if (data->mapData[x][y] == GREEN_BASE) {
		printf("%c", CHAR_MAP_BASE);
	} else if (data->mapData[x][y] == GREEN_AIRPORT) {
		printf("%c", CHAR_MAP_AIRPORT);
	} else if (data->mapData[x][y] == GREEN_PORT) {
		printf("%c", CHAR_MAP_PORT);
	} else if (data->mapData[x][y] == YELLOW_HQ) {
		printf("%c", CHAR_MAP_HQ);
	} else if (data->mapData[x][y] == YELLOW_CITY) {
		printf("%c", CHAR_MAP_CITY);
	} else if (data->mapData[x][y] == YELLOW_BASE) {
		printf("%c", CHAR_MAP_BASE);
	} else if (data->mapData[x][y] == YELLOW_AIRPORT) {
		printf("%c", CHAR_MAP_AIRPORT);
	} else if (data->mapData[x][y] == YELLOW_PORT) {
		printf("%c", CHAR_MAP_PORT);
	}
	else if (data->mapData[x][y] == PLAIN) {
		printf("%c", CHAR_MAP_PLAIN);
	} else if (data->mapData[x][y] == ROAD) {
		printf("%c", CHAR_MAP_ROAD);
	} else if (data->mapData[x][y] == SEA) {
		printf("%c", CHAR_MAP_SEA);
	} else if (data->mapData[x][y] == RIVER) {
		printf("%c", CHAR_MAP_RIVER);
	} else if (data->mapData[x][y] == WOOD) {
		printf("%c", CHAR_MAP_WOOD);
	} else if (data->mapData[x][y] == MOUNTAIN) {
		printf("%c", CHAR_MAP_MOUNTAIN);
	} else if (data->mapData[x][y] == BRIDGE) {
		printf("%c", CHAR_MAP_BRIDGE);
	} else if (data->mapData[x][y] == SHOAL) {
		printf("%c", CHAR_MAP_SHOAL);
	} else if (data->mapData[x][y] == REEF) {
		printf("%c", CHAR_MAP_REEF);
	}
}

void drawUnitUI (game *data, short x, short y) {
	short selectedUnit = unitGetter (data, x, y);
	if (data->unitData[selectedUnit].player == TEAM_NONE) {
		drawFieldUI (data, x, y);
	}
	else {
		printf("Cursor is on a ");
		drawUnitName(data, selectedUnit);
		printf("\n");
		
		printf("Health: ");
		if (data->unitData[selectedUnit].health <= 3) {
			setColor(RED);
		} else if ((data->unitData[selectedUnit].health > 3) && (data->unitData[selectedUnit].health <= 7)) {
			setColor(YELLOW);
		} else if (data->unitData[selectedUnit].health > 7) {
			setColor(GREEN);
		}
		printf("%g/10   ", data->unitData[selectedUnit].health);
		setColor(GREY);
		
		printf("Fuel: ");
		if (((float)data->unitData[selectedUnit].fuel / data->unitData[selectedUnit].maxFuel) <= 0.2) {
			setColor(RED);
		} else if ((((float)data->unitData[selectedUnit].fuel / data->unitData[selectedUnit].maxFuel) > 0.2) && (((float)data->unitData[selectedUnit].fuel / data->unitData[selectedUnit].maxFuel) <= 0.6)) {
			setColor(YELLOW);
		} else if (((float)data->unitData[selectedUnit].fuel / data->unitData[selectedUnit].maxFuel) > 0.6) {
			setColor(GREEN);
		}
		printf("%d/%d\n", data->unitData[selectedUnit].fuel, data->unitData[selectedUnit].maxFuel);
		setColor(GREY);
		
		if (data->unitData[selectedUnit].ammo1 == -1) {
			printf("Ammo1: Infinite   ");
		} else if (data->unitData[selectedUnit].maxAmmo1 == 0) {
			// Nothing.
		} else {
			printf("Ammo1: ");
			if ((((float)data->unitData[selectedUnit].ammo1 / data->unitData[selectedUnit].maxAmmo1) <= 0.1) || data->unitData[selectedUnit].ammo1 <= 2) {
				setColor(RED);
			} else if ((((float)data->unitData[selectedUnit].ammo1 / data->unitData[selectedUnit].maxAmmo1) >= 0.1) && (((float)data->unitData[selectedUnit].ammo1 / data->unitData[selectedUnit].maxAmmo1) <= 0.6)) {
				setColor(YELLOW);
			} else if (((float)data->unitData[selectedUnit].ammo1 / data->unitData[selectedUnit].maxAmmo1) > 0.6) {
				setColor(GREEN);
			}	printf("%d/%d   ", data->unitData[selectedUnit].ammo1, data->unitData[selectedUnit].maxAmmo1);
			setColor(GREY);
		}
		
		if (data->unitData[selectedUnit].ammo2 == -1) {
			printf("Ammo2: Infinite   ");
		} else if (data->unitData[selectedUnit].maxAmmo2 == 0) {
			// Nothing
		} else {
			printf("Ammo2: ");
			if ((((float)data->unitData[selectedUnit].ammo2 / data->unitData[selectedUnit].maxAmmo2) <= 0.1) || data->unitData[selectedUnit].ammo2 <= 2) {
				setColor(RED);
			} else if ((((float)data->unitData[selectedUnit].ammo2 / data->unitData[selectedUnit].maxAmmo2) >= 0.1) && (((float)data->unitData[selectedUnit].ammo2 / data->unitData[selectedUnit].maxAmmo2) <= 0.6)) {
				setColor(YELLOW);
			} else if (((float)data->unitData[selectedUnit].ammo2 / data->unitData[selectedUnit].maxAmmo2) > 0.6) {
				setColor(GREEN);
			}	printf("%d/%d   ", data->unitData[selectedUnit].ammo2, data->unitData[selectedUnit].maxAmmo2);
			setColor(GREY);
		}
		
		if (data->unitData[selectedUnit].maxAmmo1 != 0) {
			printf("(%d~%d)\n", minimumRangeGetter(data, selectedUnit), maximumRangeGetter(data, selectedUnit));
		}
		
		printf("Movement: ");
		if (data->unitData[selectedUnit].movement <= 0) {
			setColor(RED);
		} else if ((data->unitData[selectedUnit].movement <= 2) && (data->unitData[selectedUnit].movement > 0)) {
			setColor(YELLOW);
		} else if (data->unitData[selectedUnit].movement > 2) {
			setColor(GREEN);
		}
		printf("%d/%d   ", data->unitData[selectedUnit].movement, data->unitData[selectedUnit].maxMovement);
		setColor(GREY);
		
		printf("Type: ");
		if (unitMovementTypeGetter(data, selectedUnit) == MOVE_INFANTRY) {
			printf("INFANTRY\n");
		} else if (unitMovementTypeGetter(data, selectedUnit) == MOVE_MECH) {
			printf("MECH\n");
		} else if (unitMovementTypeGetter(data, selectedUnit) == MOVE_TIRES) {
			printf("TIRES\n");
		} else if (unitMovementTypeGetter(data, selectedUnit) == MOVE_TREAD) {
			printf("TREAD\n");
		} else if (unitMovementTypeGetter(data, selectedUnit) == MOVE_AIR) {
			printf("AIR\n");
		} else if (unitMovementTypeGetter(data, selectedUnit) == MOVE_SHIP) {
			printf("SHIP\n");
		} else if (unitMovementTypeGetter(data, selectedUnit) == MOVE_CARRIER) {
			printf("CARRIER\n");
		}
		
		printf("Currently on a: ");
		drawTileName(data, data->cursor.x, data->cursor.y);
		printf("\n");
		
		printf("For debugging: ID = %d, position: %d, %d\n", selectedUnit, data->cursor.x, data->cursor.y);
	}
}

void drawFieldUI (game *data, short x, short y) {
	printf("It is turn #%d. It is player ", data->turnNum);
	if (data->whoseTurn == TEAM_RED) {
		setColor(LIGHTRED);
		printf("RED");
		setColor(GREY);
	} else if (data->whoseTurn == TEAM_BLUE) {
		setColor(LIGHTBLUE);
		printf("BLUE");
		setColor(GREY);
	} else if (data->whoseTurn == TEAM_GREEN) {
		setColor(LIGHTGREEN);
		printf("GREEN");
		setColor(GREY);
	} else if (data->whoseTurn == TEAM_YELLOW) {
		setColor(YELLOW);
		printf("YELLOW");
		setColor(GREY);
	}
	printf("'s turn.\n");
	
	printf("Currently at %d, %d\n", data->cursor.x, data->cursor.y);
	
	printf("Tile: ");
	drawTileName(data, data->cursor.x, data->cursor.y);
	printf("\n");
	
	char tileDefense = tileDefenseGetter(data, x, y);
	char iterations = 0;
	printf("Defense: ");
	setColor(YELLOW);
	while (iterations < tileDefense) {
		printf("*");
		iterations++;
	}
	setColor(GREY);
	printf("\n");
}

void drawMoveUI (game *data, short x, short y) {
	short selectedUnit = unitGetter (data, x, y);
	printf("Currently moving a ");
	drawUnitName(data, selectedUnit);

	printf("Movement: ");
	if (data->unitData[selectedUnit].movement <= 0) {
		setColor(RED);
	} else if ((data->unitData[selectedUnit].movement <= 2) && (data->unitData[selectedUnit].movement > 0)) {
		setColor(YELLOW);
	} else if (data->unitData[selectedUnit].movement > 2) {
		setColor(GREEN);
	}
	printf("%d/%d\n", data->unitData[selectedUnit].movement, data->unitData[selectedUnit].maxMovement);
	setColor(GREY);

	int movementType = unitMovementTypeGetter(data, selectedUnit);
	
	printf("UP    is a ");
	drawTileName(data, x, y - 1);
	printf(" (%d)\n", tileMovementGetter(data, x, y - 1, movementType)); 
	printf("DOWN  is a ");
	drawTileName(data, x, y + 1);
	printf(" (%d)\n", tileMovementGetter(data, x, y + 1, movementType)); 
	printf("LEFT  is a ");
	drawTileName(data, x - 1, y);
	printf(" (%d)\n", tileMovementGetter(data, x - 1, y, movementType)); 
	printf("RIGHT is a ");
	drawTileName(data, x + 1, y);
	printf(" (%d)\n", tileMovementGetter(data, x + 1, y, movementType));
}

void drawAttackUI (game *data, short attacker, short x, short y) {
	// There's a lot of repetition in this function. I might split it up
	// (but it's ever so slightly different from the unit UI one).
	short defender = unitGetter(data, data->cursor.x, data->cursor.y);
	char baseDamage = 0;
	if (whichWeapon(data, attacker, defender) == PRIMARY) {
		baseDamage = baseDamageGetter(data, attacker, defender, PRIMARY);
	} else if (whichWeapon(data, attacker, defender) == SECONDARY) {
		baseDamage = baseDamageGetter(data, attacker, defender, SECONDARY);
	}
	char tileDefense = tileDefenseGetter(data, data->unitData[attacker].x, data->unitData[attacker].y);
	char iterations = 0;
	
	printf("Attacker: ");
	drawUnitName(data, attacker);
	printf(" on a ");
	drawTileName(data, data->unitData[attacker].x, data->unitData[attacker].y);
	
	printf("(");
	setColor(YELLOW);
	while (iterations < tileDefense) {
		printf("*");
		iterations++;
	}
	setColor(GREY);
	printf(")\n");
	
	printf("Health: ");
	if (data->unitData[attacker].health <= 3) {
		setColor(RED);
	} else if ((data->unitData[attacker].health > 3) && (data->unitData[attacker].health <= 7)) {
		setColor(YELLOW);
	} else if (data->unitData[attacker].health > 7) {
		setColor(GREEN);
	}
	printf("%g/10   ", data->unitData[attacker].health);
	setColor(GREY);
	
	if (data->unitData[attacker].ammo1 == -1) {
		printf("Ammo1: Infinite   ");
	} else if (data->unitData[attacker].maxAmmo1 == 0) {
		// Nothing.
	} else {
		printf("Ammo1: ");
		if ((((float)data->unitData[attacker].ammo1 / data->unitData[attacker].maxAmmo1) <= 0.1) || data->unitData[attacker].ammo1 <= 2) {
			setColor(RED);
		} else if ((((float)data->unitData[attacker].ammo1 / data->unitData[attacker].maxAmmo1) >= 0.1) && (((float)data->unitData[attacker].ammo1 / data->unitData[attacker].maxAmmo1) <= 0.6)) {
			setColor(YELLOW);
		} else if (((float)data->unitData[attacker].ammo1 / data->unitData[attacker].maxAmmo1) > 0.6) {
			setColor(GREEN);
		}	printf("%d/%d   ", data->unitData[attacker].ammo1, data->unitData[attacker].maxAmmo1);
		setColor(GREY);
	}
	
	if (data->unitData[attacker].ammo2 == -1) {
		printf("Ammo2: Infinite   ");
	} else if (data->unitData[attacker].maxAmmo2 == 0) {
		// Nothing
	} else {
		printf("Ammo2: ");
		if ((((float)data->unitData[attacker].ammo2 / data->unitData[attacker].maxAmmo2) <= 0.1) || data->unitData[attacker].ammo2 <= 2) {
			setColor(RED);
		} else if ((((float)data->unitData[attacker].ammo2 / data->unitData[attacker].maxAmmo2) >= 0.1) && (((float)data->unitData[attacker].ammo2 / data->unitData[attacker].maxAmmo2) <= 0.6)) {
			setColor(YELLOW);
		} else if (((float)data->unitData[attacker].ammo2 / data->unitData[attacker].maxAmmo2) > 0.6) {
			setColor(GREEN);
		}	printf("%d/%d\n", data->unitData[attacker].ammo2, data->unitData[attacker].maxAmmo2);
		setColor(GREY);
	}

	printf("Defender: ");
	if (defender == MAX_UNITS) {
		printf("NO TARGET\n");
	} else {
		tileDefense = tileDefenseGetter(data, data->cursor.x, data->cursor.y);
		iterations = 0;
		drawUnitName(data, defender);
		printf(" on a ");
		drawTileName(data, data->unitData[defender].x, data->unitData[defender].y);
		
		printf("(");
		setColor(YELLOW);
		while (iterations < tileDefense) {
			printf("*");
			iterations++;
		}
		setColor(GREY);
		printf(")\n");
		printf("Health: ");
		if (data->unitData[defender].health <= 3) {
			setColor(RED);
		} else if ((data->unitData[defender].health > 3) && (data->unitData[defender].health <= 7)) {
			setColor(YELLOW);
		} else if (data->unitData[defender].health > 7) {
			setColor(GREEN);
		}
		printf("%g/10   ", data->unitData[defender].health);
		setColor(GREY);
		
		if (data->unitData[defender].ammo1 == -1) {
			printf("Ammo1: Infinite   ");
		} else if (data->unitData[defender].maxAmmo1 == 0) {
			// Nothing.
		} else {
			printf("Ammo1: ");
			if ((((float)data->unitData[defender].ammo1 / data->unitData[defender].maxAmmo1) <= 0.1) || data->unitData[defender].ammo1 <= 2) {
				setColor(RED);
			} else if ((((float)data->unitData[defender].ammo1 / data->unitData[defender].maxAmmo1) >= 0.1) && (((float)data->unitData[defender].ammo1 / data->unitData[defender].maxAmmo1) <= 0.6)) {
				setColor(YELLOW);
			} else if (((float)data->unitData[defender].ammo1 / data->unitData[defender].maxAmmo1) > 0.6) {
				setColor(GREEN);
			}	printf("%d/%d   ", data->unitData[defender].ammo1, data->unitData[defender].maxAmmo1);
			setColor(GREY);
		}
		
		if (data->unitData[defender].ammo2 == -1) {
			printf("Ammo2: Infinite   ");
		} else if (data->unitData[defender].maxAmmo2 == 0) {
			// Nothing
		} else {
			printf("Ammo2: ");
			if ((((float)data->unitData[defender].ammo2 / data->unitData[defender].maxAmmo2) <= 0.1) || data->unitData[defender].ammo2 <= 2) {
				setColor(RED);
			} else if ((((float)data->unitData[defender].ammo2 / data->unitData[defender].maxAmmo2) >= 0.1) && (((float)data->unitData[defender].ammo2 / data->unitData[defender].maxAmmo2) <= 0.6)) {
				setColor(YELLOW);
			} else if (((float)data->unitData[defender].ammo2 / data->unitData[defender].maxAmmo2) > 0.6) {
				setColor(GREEN);
			}	printf("%d/%d\n", data->unitData[defender].ammo2, data->unitData[defender].maxAmmo2);
			setColor(GREY);
		}
		
		printf("Base damage: ");
		if (validAttackChecker(data, attacker, defender) == NO) {
			printf("--\%\n");
		} else {
			if (baseDamage <= 30) {
				setColor(GREEN);
			} else if (baseDamage <= 60) {
				setColor(YELLOW);
			} else {
				setColor(RED);
			}
			printf("%d", baseDamage);
			printf("\%\n");
			setColor(GREY);
		}
	}
}

void drawUnitName (game *data, short selectedUnit) {
	if (data->unitData[selectedUnit].player == TEAM_RED) {
		setColor(LIGHTRED);
		printf("RED ");
		setColor(GREY);
	} else if (data->unitData[selectedUnit].player == TEAM_BLUE) {
		setColor(LIGHTBLUE);
		printf("BLUE ");
		setColor(GREY);
	} else if (data->unitData[selectedUnit].player == TEAM_GREEN) {
		setColor(LIGHTGREEN);
		printf("GREEN ");
		setColor(GREY);
	} else if (data->unitData[selectedUnit].player == TEAM_YELLOW) {
		setColor(YELLOW);
		printf("YELLOW ");
		setColor(GREY);
	}
	
	if (data->unitData[selectedUnit].unitType == INFANTRY) {
		printf("INFANTRY");
	} else if (data->unitData[selectedUnit].unitType == MECH) {
		printf("MECH");
	} else if (data->unitData[selectedUnit].unitType == RECON) {
		printf("RECON");
	} else if (data->unitData[selectedUnit].unitType == TANK) {
		printf("TANK");
	} else if (data->unitData[selectedUnit].unitType == MD_TANK) {
		printf("MEDIUM TANK");
	} else if (data->unitData[selectedUnit].unitType == NEOTANK) {
		printf("NEOTANK");
	} else if (data->unitData[selectedUnit].unitType == MEGATANK) {
		printf("MEGATANK");
	} else if (data->unitData[selectedUnit].unitType == APC) {
		printf("APC");
	} else if (data->unitData[selectedUnit].unitType == ARTILLERY) {
		printf("ARTILLERY");
	} else if (data->unitData[selectedUnit].unitType == ROCKETS) {
		printf("ROCKET LAUNCHER");
	} else if (data->unitData[selectedUnit].unitType == ANTI_AIR) {
		printf("ANTI-AIR CANNON");
	} else if (data->unitData[selectedUnit].unitType == MISSILES) {
		printf("MISSILES");
	} else if (data->unitData[selectedUnit].unitType == BATT_COP) {
		printf("BATTLE COPTER");
	} else if (data->unitData[selectedUnit].unitType == TRAN_COP) {
		printf("TRANSPORT COPTER");
	} else if (data->unitData[selectedUnit].unitType == FIGHTER) {
		printf("FIGHTER");
	} else if (data->unitData[selectedUnit].unitType == BOMBER) {
		printf("BOMBER");
	} else if (data->unitData[selectedUnit].unitType == STEALTH) {
		printf("STEALTH");
	} else if (data->unitData[selectedUnit].unitType == LANDER) {
		printf("LANDER");
	} else if (data->unitData[selectedUnit].unitType == CRUISER) {
		printf("CRUISER");
	} else if (data->unitData[selectedUnit].unitType == SUB) {
		printf("SUBMARINE");
	} else if (data->unitData[selectedUnit].unitType == BATT_SHIP) {
		printf("BATTLESHIP");
	} else if (data->unitData[selectedUnit].unitType == CARRIER) {
		printf("CARRIER");
	}
}

void drawTileName (game *data, short x, short y) {
	char mapTile = data->mapData[x][y];
		if (mapTile == NULL_HQ) {
		setColor(WHITE);
		printf("Unoccupied ");
		setColor(GREY);
		printf("HQ");
	} else if (mapTile == NULL_CITY) {
		setColor(WHITE);
		printf("Unoccupied ");
		setColor(GREY);
		printf("city");
	} else if (mapTile == NULL_BASE) {
		setColor(WHITE);
		printf("Unoccupied ");
		setColor(GREY);
		printf("base");
	} else if (mapTile == NULL_AIRPORT) {
		setColor(WHITE);
		printf("Unoccupied ");
		setColor(GREY);
		printf("airport");
	} else if (mapTile == NULL_PORT) {
		setColor(WHITE);
		printf("Unoccupied ");
		setColor(GREY);
		printf("port");
	}
	else if (mapTile == RED_HQ) {
		setColor(LIGHTRED);
		printf("RED ");
		setColor(GREY);
		printf("HQ");
	} else if (mapTile == RED_CITY) {
		setColor(LIGHTRED);
		printf("RED ");
		setColor(GREY);
		printf("city");
	} else if (mapTile == RED_BASE) {
		setColor(LIGHTRED);
		printf("RED ");
		setColor(GREY);
		printf("base");
	} else if (mapTile == RED_AIRPORT) {
		setColor(LIGHTRED);
		printf("RED ");
		setColor(GREY);
		printf("airport");
	} else if (mapTile == RED_PORT) {
		setColor(LIGHTRED);
		printf("RED ");
		setColor(GREY);
		printf("port");
	}
	else if (mapTile == BLUE_HQ) {
		setColor(LIGHTBLUE);
		printf("BLUE ");
		setColor(GREY);
		printf("HQ");
	} else if (mapTile == BLUE_CITY) {
		setColor(LIGHTBLUE);
		printf("BLUE ");
		setColor(GREY);
		printf("city");
	} else if (mapTile == BLUE_BASE) {
		setColor(LIGHTBLUE);
		printf("BLUE ");
		setColor(GREY);
		printf("base");
	} else if (mapTile == BLUE_AIRPORT) {
		setColor(LIGHTBLUE);
		printf("BLUE ");
		setColor(GREY);
		printf("airport");
	} else if (mapTile == BLUE_PORT) {
		setColor(LIGHTBLUE);
		printf("BLUE ");
		setColor(GREY);
		printf("port");
	}
	else if (mapTile == GREEN_HQ) {
		setColor(LIGHTGREEN);
		printf("GREEN ");
		setColor(GREY);
		printf("HQ");
	} else if (mapTile == GREEN_CITY) {
		setColor(LIGHTGREEN);
		printf("GREEN ");
		setColor(GREY);
		printf("city");
	} else if (mapTile == GREEN_BASE) {
		setColor(LIGHTGREEN);
		printf("GREEN ");
		setColor(GREY);
		printf("base");
	} else if (mapTile == GREEN_AIRPORT) {
		setColor(LIGHTGREEN);
		printf("GREEN ");
		setColor(GREY);
		printf("airport");
	} else if (mapTile == GREEN_PORT) {
		setColor(LIGHTGREEN);
		printf("GREEN ");
		setColor(GREY);
		printf("port");
	}
	else if (mapTile == YELLOW_HQ) {
		setColor(YELLOW);
		printf("YELLOW ");
		setColor(GREY);
		printf("HQ");
	} else if (mapTile == YELLOW_CITY) {
		setColor(YELLOW);
		printf("YELLOW ");
		setColor(GREY);
		printf("city");
	} else if (mapTile == YELLOW_BASE) {
		setColor(YELLOW);
		printf("YELLOW ");
		setColor(GREY);
		printf("base");
	} else if (mapTile == YELLOW_AIRPORT) {
		setColor(YELLOW);
		printf("YELLOW ");
		setColor(GREY);
		printf("airport");
	} else if (mapTile == YELLOW_PORT) {
		setColor(YELLOW);
		printf("YELLOW ");
		setColor(GREY);
		printf("port");
	}
	else if (mapTile == PLAIN) {
		printf("Plain");
	} else if (mapTile == ROAD) {
		printf("Road");
	} else if (mapTile == SEA) {
		printf("Sea");
	} else if (mapTile == RIVER) {
		printf("River");
	} else if (mapTile == WOOD) {
		printf("Wood");
	} else if (mapTile == MOUNTAIN) {
		printf("Mountain");
	} else if (mapTile == BRIDGE) {
		printf("Bridge");
	} else if (mapTile == SHOAL) {
		printf("Shoal");
	} else if (mapTile == REEF) {
		printf("Reef");
	}
}

void drawBattleResult (game *data, short attacker, short defender, float damage, char mode) {
	if (mode == 0) {
		printf("The ");
		drawUnitName(data, attacker);
		printf(" attacks the ");
		drawUnitName(data, defender);
		printf("!\n");
	} else if (mode == 1) {
		printf("\nThe ");
		drawUnitName(data, attacker);
		printf(" strikes back!\n");
	}
	
	printf("The ");
	drawUnitName(data, defender);
	if (damage <= 0.5) {
		printf(" was lightly tapped for ");
	} else if (damage <= 2) {
		printf(" was hit for ");
	} else if (damage <= 4) {
		printf(" was hit hard for ");
	} else if (damage <= 6) {
		printf(" was struck for ");
	} else if (damage < 10) {
		printf(" was almost completely destroyed for ");
	} else if (damage <= 13) {
		printf(" was no match for the ");
		drawUnitName(data, attacker);
		printf(", hit for ");
	} else {
		printf(" didn't even stand a chance, hit for ");
	}
	
	if (damage <= 2) {
		setColor(LIGHTGREEN);
	} else if (damage <= 6) {
		setColor(YELLOW);
	} else {
		setColor(LIGHTRED);
	}
	printf("%g.\n", damage);
	setColor(GREY);
	
	printf("The ");
	drawUnitName(data, defender);
	if (data->unitData[defender].health <= 0) {
		printf(" was destroyed.\n");
	} else if (data->unitData[defender].health <= 2) {
		printf(" only barely held on with ");
		setColor(LIGHTRED);
		printf("%g ", data->unitData[defender].health);
		printf("health.\n");
	} else if (data->unitData[defender].health <= 6) {
		printf(" is a bit weakened with ");
		setColor(LIGHTRED);
		printf("%g ", data->unitData[defender].health);
		printf("health.\n");
	} else {
		printf(" still stood strong with ");
		setColor(LIGHTGREEN);
		printf("%g ", data->unitData[defender].health);
		printf("health.\n");
	}
	setColor(GREY);
}

void testDrawing (game *data) {
	// This is just a bit of example setup to get the game started.
	createUnit(data, 4, 3, INFANTRY, TEAM_RED);
	createUnit(data, 8, 6, MECH, TEAM_RED);
	createUnit(data, 5, 3, ARTILLERY, TEAM_BLUE);
	createUnit(data, 13, 10, MEGATANK, TEAM_BLUE);
	createUnit(data, 11, 3, TANK, TEAM_BLUE);
	createUnit(data, 1, 10, MECH, TEAM_GREEN);
	createUnit(data, 12, 6, APC, TEAM_YELLOW);
	createUnit(data, 10, 10, NEOTANK, TEAM_YELLOW);
	// This demonstrates how deleting units works.
	deleteUnit(data, 4);
	// And creating new units after that.
	createUnit(data, 2, 2, BATT_COP, TEAM_GREEN);
	
	data->cursor.x = 5;
	data->cursor.y = 4;
	data->drawMode = DRAWMODE_MAP;
	data->interfaceMode = INTERFACEMODE_MAP;
	
	/// This stores what key was last pressed.
	// Because KEY_ESCAPE = 0, it has to be set to another number.
	// Try making this an unsigned char, as the numbers don't go higher than 135.
	int keyPress = 5001;
	// keyPress is set to an arbitrary value so that it doesn't trigger
	// anything.
	
	/// This stores what unit is currently under the cursor.
	short selectedUnit = MAX_UNITS;
	
	/// If the game is told to quit, then it exits this.
	while (data->interfaceMode != INTERFACEMODE_QUIT) {
		selectedUnit = unitGetter(data, data->cursor.x, data->cursor.y);
		/// If the game is currently moving around the map...
		if (data->interfaceMode == INTERFACEMODE_MAP) {
			/// The map is drawn.
			mapDraw(data);
			/// If units are hidden, then the field data is displayed.
			if (data->drawMode == DRAWMODE_MAP) {
				drawFieldUI(data, data->cursor.x, data->cursor.y);
			/// But if the units are shown, then, if there is a unit
			/// under the cursor, it shows that data. Otherwise, it's
			/// just the field.
			} else if (data->drawMode == DRAWMODE_UNITS) {
				selectedUnit = unitGetter(data, data->cursor.x, data->cursor.y);
				if (selectedUnit != MAX_UNITS) {
					drawUnitUI(data, data->cursor.x, data->cursor.y);
				} else {
					drawFieldUI(data, data->cursor.x, data->cursor.y);
				}
			}
			/// Then the user input is stored.
			keyPress = getkey();
			/// If they just use the arrow keys, we move the cursor.
			if (keyPress == KEY_UP) {
				moveCursor(data, UP);
			} else if (keyPress == KEY_DOWN) {
				moveCursor(data, DOWN);
			} else if (keyPress == KEY_LEFT) {
				moveCursor(data, LEFT);
			} else if (keyPress == KEY_RIGHT) {
				moveCursor(data, RIGHT);
			/// But if they want to access the menu, if they're on top
			/// of a unit, it goes to the unit menu. Otherwise, it's
			/// the field menu.
			} else if (keyPress == KEY_SPACE) {
				if (selectedUnit != MAX_UNITS) {
					data->interfaceMode = INTERFACEMODE_MENU_UNIT;
					drawMenu(data);
				} else {
					data->interfaceMode = INTERFACEMODE_MENU_FIELD;
					drawMenu(data);
				}
			}
		/// If the user is "moving" units, this goes.
		} else if (data->interfaceMode == INTERFACEMODE_MOVE) {
			/// The map and UI are drawn specifically for this.
			mapDraw(data);
			drawMoveUI(data, data->cursor.x, data->cursor.y);
			
			/// Then the user's input is gotten.
			keyPress = getkey();
			/// If they use the arrow keys, we move the unit. There's
			/// a check inside to see if it's a legal move.
			if (keyPress == KEY_UP) {
				moveUnit(data, selectedUnit, UP);
			} else if (keyPress == KEY_DOWN) {
				moveUnit(data, selectedUnit, DOWN);
			} else if (keyPress == KEY_LEFT) {
				moveUnit(data, selectedUnit, LEFT);
			} else if (keyPress == KEY_RIGHT) {
				moveUnit(data, selectedUnit, RIGHT);
			/// They hit SPACE when they stop, and it goes back to the
			/// map.
			} else if (keyPress == KEY_SPACE) {
				data->interfaceMode = INTERFACEMODE_MAP;
			}
		} else if (data->interfaceMode == INTERFACEMODE_ATTACK) {
			/// The map and UI are drawn specifically for this.
			mapDraw(data);
			drawAttackUI(data, data->attacker, data->cursor.x, data->cursor.y);
			
			/// Then the user's input is gotten.
			keyPress = getkey();
			/// This is just like moving the cursor around, but the UI
			/// is different.
			if (keyPress == KEY_UP) {
				moveCursor(data, UP);
			} else if (keyPress == KEY_DOWN) {
				moveCursor(data, DOWN);
			} else if (keyPress == KEY_LEFT) {
				moveCursor(data, LEFT);
			} else if (keyPress == KEY_RIGHT) {
				moveCursor(data, RIGHT);
			/// When SPACE is hit, it computes the attack, and exits to
			/// to the map.
			} else if (keyPress == KEY_SPACE) {
				if (validAttackChecker(data, data->attacker, selectedUnit) == YES) {
					attackUnit(data, data->attacker, selectedUnit);
				}
				
				data->interfaceMode = INTERFACEMODE_MAP;
				data->attacker = MAX_UNITS;
			}
		}
		/// If the user ever hits ENTER, the draw mode switches.
		/// This can be used on any interface mode.
		if (keyPress == KEY_ENTER) {
			if (data->drawMode == DRAWMODE_MAP) {
				data->drawMode = DRAWMODE_UNITS;
			} else if (data->drawMode == DRAWMODE_UNITS) {
				data->drawMode = DRAWMODE_MAP;
			}
		}
	}
}

void drawMenu(game *data) {
	/// This variable stores what the keypress is.
	// keyPress is set to an arbitrary value so that it doesn't trigger
	// anything.
	int keyPress = 5001;
	/// This notes what menu item is selected.
	short selection = 0;
	/// This stores what unit is under the cursor.
	short selectedUnit = unitGetter (data, data->cursor.x, data->cursor.y);
	/// If the selection wasn't on a unit, it shows this.
	if (data->interfaceMode == INTERFACEMODE_MENU_FIELD) {
		/// This breaks when the user hits either ESCAPE or SPACE.
		while (keyPress != KEY_ESCAPE && keyPress != KEY_SPACE) {
			/// Firstly the map is drawn.
			mapDraw(data);
			
			/// Then the menu items are displayed. If they're
			/// highlighted, they turn yellow.
			if (selection == 0) {
				setColor(YELLOW);
			}
			printf("END TURN\n");
			setColor(GREY);
			if (selection == 1) {
				setColor(YELLOW);
			}
			printf("INFO (UNFINISHED)\n");
			setColor(GREY);
			if (selection == 2) {
				setColor(YELLOW);
			}
			printf("SAVE (UNFINISHED)\n");
			setColor(GREY);
			if (selection == 3) {
				setColor(YELLOW);
			}
			printf("QUIT\n");
			setColor(GREY);
			
			/// Then we get user input.
			keyPress = getkey();
			
			/// If they are moving up and down, we shift the selection.
			if (keyPress == KEY_UP) {
				if (selection > 0) {
					selection--;
				}
			} else if (keyPress == KEY_DOWN) {
				if (selection < 3) {
					selection++;
				}
			}
		}
	/// Similarly, if a unit is selected, a different menu comes up.
	} else if (data->interfaceMode == INTERFACEMODE_MENU_UNIT) {
		/// It breaks if the user hits ESCAPE or SPACE.
		while (keyPress != KEY_ESCAPE && keyPress != KEY_SPACE) {
			/// Map is drawn.
			mapDraw(data);
			
			/// Menu items are shown.
			if ((selection == 0) && ((data->unitData[selectedUnit].finished == YES) || (data->unitData[selectedUnit].movement == 0) || (data->unitData[selectedUnit].player != data->whoseTurn))) {
				setColor(BROWN);
			} else if (selection == 0) {
				setColor(YELLOW);
			/// If it's is finished, or can't move, grey this out.
			/// It's also greyed if it's not the user's unit.
			} else if ((data->unitData[selectedUnit].finished == YES) || (data->unitData[selectedUnit].movement == 0) || (data->unitData[selectedUnit].player != data->whoseTurn)) {
				setColor(DARKGREY);
			}
			printf("MOVE\n");
			setColor(GREY);
			if ((selection == 1) && ((data->unitData[selectedUnit].finished == YES) || (data->unitData[selectedUnit].player != data->whoseTurn))) {
				setColor(BROWN);
			} else if (selection == 1) {
				setColor(YELLOW);
			/// If it's finished, grey this out. It's also greyed if
			/// it's not the user's unit.
			} else if ((data->unitData[selectedUnit].finished == YES) || (data->unitData[selectedUnit].player != data->whoseTurn)) {
				setColor(DARKGREY);
			}
			printf("ATTACK (UNFINISHED)\n");
			setColor(GREY);
			if (selection == 2) {
				setColor(YELLOW);
			}
			printf("END TURN\n");
			setColor(GREY);
			if (selection == 3) {
				setColor(YELLOW);
			}
			printf("INFO (UNFINISHED)\n");
			setColor(GREY);
			if (selection == 4) {
				setColor(YELLOW);
			}
			printf("SAVE (UNFINISHED)\n");
			setColor(GREY);
			if (selection == 5) {
				setColor(YELLOW);
			}
			printf("QUIT\n");
			setColor(GREY);
			
			/// Input is gotten.
			keyPress = getkey();
			
			/// If they move the list up and down, then it does that.
			if (keyPress == KEY_UP) {
				if (selection > 0) {
					selection--;
				}
			} else if (keyPress == KEY_DOWN) {
				if (selection < 5) {
					selection++;
				}
			}
		}
	}
	
	/// If the user hits SPACE (selecting the option), then we change
	/// the subsequent mode.
	if (keyPress == KEY_SPACE) {
		if (data->interfaceMode == INTERFACEMODE_MENU_FIELD) {
			if (selection == 0) {
				// END TURN
				endTurn(data);
				data->interfaceMode = INTERFACEMODE_MAP;
			} else if (selection == 1) {
				// HELP
				data->interfaceMode = INTERFACEMODE_MAP;
			} else if (selection == 2) {
				// SAVE
				data->interfaceMode = INTERFACEMODE_MAP;
			} else if (selection == 3) {
				// QUIT
				data->interfaceMode = INTERFACEMODE_QUIT;
			}
		} else if (data->interfaceMode == INTERFACEMODE_MENU_UNIT) {
			if (selection == 0) {
				// MOVE
				/// If it was greyed out, it won't move it.
				if ((data->unitData[selectedUnit].finished == YES) || (data->unitData[selectedUnit].movement == 0) || (data->unitData[selectedUnit].player != data->whoseTurn)) {
					data->interfaceMode = INTERFACEMODE_MAP;
				} else {
					data->interfaceMode = INTERFACEMODE_MOVE;
				}
			} else if (selection == 1) {
				// ATTACK
				/// If it was greyed out, it won't attack.
				if ((data->unitData[selectedUnit].finished == YES) || (data->unitData[selectedUnit].player != data->whoseTurn)) {
					data->interfaceMode = INTERFACEMODE_MAP;
				} else {
					data->attacker = unitGetter(data, data->cursor.x, data->cursor.y);
					data->interfaceMode = INTERFACEMODE_ATTACK;
				}
			} else if (selection == 2) {
				// END TURN
				endTurn(data);
				data->interfaceMode = INTERFACEMODE_MAP;
			} else if (selection == 3) {
				// HELP
				data->interfaceMode = INTERFACEMODE_MAP;
			} else if (selection == 4) {
				// SAVE
				data->interfaceMode = INTERFACEMODE_MAP;
			} else if (selection == 5) {
				// QUIT
				data->interfaceMode = INTERFACEMODE_QUIT;
			}
		}
	/// If they hit ESCAPE, just leave the menu.
	} else if (keyPress == KEY_ESCAPE) {
		data->interfaceMode = INTERFACEMODE_MAP;
	}
}