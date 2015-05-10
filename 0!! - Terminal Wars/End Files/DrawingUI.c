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
	setColor(LIGHTMAGENTA);
	printf("TERMINAL WARS");
	setColor(GREY);
	printf("        |\n");
	printf("|                              |\n");
	printf("+------------------------------+\n");
	printf("\n");
	printf("An attempt to recreate the game Advance Wars in C.\n");
	printf("\n");
	printf("Version \"Stage 12\"\n\n");
	
	/// This tells the user if their screen is too small.
	if (trows() < (MAP_HEIGHT + 14)) {
		printf("Your screen is too short to properly view this.\n");
		printf("Make your window taller to fit %d rows.\n\n", MAP_HEIGHT + 14);
	}
	// This magic number is just how roughly wide the screen needs to be.
	// I don't kow exactly how wide it should be.
	if ((tcols() < MAP_WIDTH) || (tcols() < 50)) {
		printf("Your screen is too thin to properly view this.\n");
		printf("Make your window wider to fit %d columns.\n\n", MAP_WIDTH);
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
	
	printf("You currently have $");
	if (data->whoseTurn == TEAM_RED) {
		printf("%d.\n", data->p1.money);
	} else if (data->whoseTurn == TEAM_BLUE) {
		printf("%d.\n", data->p2.money);
	} else if (data->whoseTurn == TEAM_GREEN) {
		printf("%d.\n", data->p3.money);
	} else if (data->whoseTurn == TEAM_YELLOW) {
		printf("%d.\n", data->p4.money);
	}
	
	printf("You own ");
	if (data->whoseTurn == TEAM_RED) {
		printf("%d", data->p1.buildingsOwned);
	} else if (data->whoseTurn == TEAM_BLUE) {
		printf("%d", data->p2.buildingsOwned);
	} else if (data->whoseTurn == TEAM_GREEN) {
		printf("%d", data->p3.buildingsOwned);
	} else if (data->whoseTurn == TEAM_YELLOW) {
		printf("%d", data->p4.buildingsOwned);
	}	
	printf(" buildings and ");
	if (data->whoseTurn == TEAM_RED) {
		printf("%d", data->p1.unitsOwned);
	} else if (data->whoseTurn == TEAM_BLUE) {
		printf("%d", data->p2.unitsOwned);
	} else if (data->whoseTurn == TEAM_GREEN) {
		printf("%d", data->p3.unitsOwned);
	} else if (data->whoseTurn == TEAM_YELLOW) {
		printf("%d", data->p4.unitsOwned);
	}
	printf(" units.\n");
	
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
	printf("\n");
	
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
	
	printf(" (");
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
		printf("Ammo2: Infinite");
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
		}	printf("%d/%d", data->unitData[attacker].ammo2, data->unitData[attacker].maxAmmo2);
		setColor(GREY);
	}
	printf("\n");

	printf("Defender: ");
	if (defender == MAX_UNITS) {
		printf("NO TARGET\n");
	} else {
		tileDefense = tileDefenseGetter(data, data->cursor.x, data->cursor.y);
		iterations = 0;
		drawUnitName(data, defender);
		printf(" on a ");
		drawTileName(data, data->unitData[defender].x, data->unitData[defender].y);
		
		printf(" (");
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
			printf("Ammo2: Infinite");
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
			}	printf("%d/%d", data->unitData[defender].ammo2, data->unitData[defender].maxAmmo2);
			setColor(GREY);
		}
		printf("\n");
		
		printf("Base damage: ");
		if (validAttackChecker(data, attacker, defender) == NO) {
			printf("--%%\n");
		} else {
			if (baseDamage <= 30) {
				setColor(GREEN);
			} else if (baseDamage <= 60) {
				setColor(YELLOW);
			} else {
				setColor(RED);
			}
			printf("%d", baseDamage);
			printf("%%\n");
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
	} else if (damage <= 2.5) {
		printf(" was hit for ");
	} else if (damage <= 5) {
		printf(" was hit hard for ");
	} else if (damage <= 7.5) {
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
	
	if (damage <= 3) {
		setColor(LIGHTGREEN);
	} else if (damage <= 6) {
		setColor(YELLOW);
	} else {
		setColor(LIGHTRED);
	}
	printf("%g", damage);
	setColor(GREY);
	printf(".\n");
	
	printf("The ");
	drawUnitName(data, defender);
	if (data->unitData[defender].health <= 0) {
		printf(" was destroyed.\n");
	} else {
		if (data->unitData[defender].health <= 2) {
			printf(" only barely held on with ");
			setColor(LIGHTRED);
			printf("%g ", data->unitData[defender].health);
		} else if (data->unitData[defender].health <= 6) {
			printf(" is a bit weakened with ");
			setColor(YELLOW);
			printf("%g ", data->unitData[defender].health);
		} else {
			printf(" still stood strong with ");
			setColor(LIGHTGREEN);
			printf("%g ", data->unitData[defender].health);
		}
		setColor(GREY);
		printf("health.\n");
	}
}

void testDrawing (game *data) {
	// This is just a default place to put the cursor.
	data->cursor.x = 5;
	data->cursor.y = 4;
	data->drawMode = DRAWMODE_UNITS;
	data->interfaceMode = INTERFACEMODE_MAP;
	
	/// This stores what key was last pressed.
	// Because KEY_ESCAPE = 0, it has to be set to another number.
	// Try making this an unsigned char, as the numbers don't go higher than 135.
	int keyPress = 5001;
	// keyPress is set to an arbitrary value so that it doesn't trigger
	// anything.
	
	/// This stores what unit is currently under the cursor.
	short selectedUnit = MAX_UNITS;
	
	/// This is for storing the cursor position in buy menus.
	short selection = 0;
	
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
			} else if (keyPress == KEY_SPACE || keyPress == KEY_ESCAPE) {
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
					anykey();
				}
				
				data->interfaceMode = INTERFACEMODE_MAP;
				data->attacker = MAX_UNITS;
			} else if (keyPress == KEY_ESCAPE) {
				data->interfaceMode = INTERFACEMODE_MAP;
				data->attacker = MAX_UNITS;
			}
		} else if (data->interfaceMode == INTERFACEMODE_BUY_LAND) {
			keyPress = 5001;
			selection = 0;
			while (keyPress != KEY_ESCAPE && keyPress != KEY_SPACE) {
				mapDraw(data);
				
					if (data->numberOfPlayers >= 1) {
						setColor(LIGHTRED);
						printf("$%d   ", data->p1.money);
					}
					if (data->numberOfPlayers >= 2) {
						setColor(LIGHTBLUE);
						printf("$%d   ", data->p2.money);
					}
					if (data->numberOfPlayers >= 3) {
						setColor(LIGHTGREEN);
						printf("$%d   ", data->p3.money);
					}
					if (data->numberOfPlayers >= 4) {
						setColor(YELLOW);
						printf("$%d", data->p4.money);
					}
					printf("\n");
					setColor(GREY);
				
				if (selection == 0) {
					if (((data->whoseTurn == TEAM_RED) && (data->p1.money < COST_INFANTRY)) || ((data->whoseTurn == TEAM_BLUE) && (data->p2.money < COST_INFANTRY)) || ((data->whoseTurn == TEAM_GREEN) && (data->p3.money < COST_INFANTRY)) || ((data->whoseTurn == TEAM_YELLOW) && (data->p4.money < COST_INFANTRY))) {
						if (data->p1.money < COST_INFANTRY) {
							setColor(BROWN);
						}
					} else {
						setColor(YELLOW);
					}
				} else if (((data->whoseTurn == TEAM_RED) && (data->p1.money < COST_INFANTRY)) || ((data->whoseTurn == TEAM_BLUE) && (data->p2.money < COST_INFANTRY)) || ((data->whoseTurn == TEAM_GREEN) && (data->p3.money < COST_INFANTRY)) || ((data->whoseTurn == TEAM_YELLOW) && (data->p4.money < COST_INFANTRY))) {
					setColor(DARKGREY);
				}
				printf("INFANTRY        - $%d\n", COST_INFANTRY);
				setColor(GREY);
				if (selection == 1) {
					if (((data->whoseTurn == TEAM_RED) && (data->p1.money < COST_MECH)) || ((data->whoseTurn == TEAM_BLUE) && (data->p2.money < COST_MECH)) || ((data->whoseTurn == TEAM_GREEN) && (data->p3.money < COST_MECH)) || ((data->whoseTurn == TEAM_YELLOW) && (data->p4.money < COST_MECH))) {
						if (data->p1.money < COST_MECH) {
							setColor(BROWN);
						}
					} else {
						setColor(YELLOW);
					}
				} else if (((data->whoseTurn == TEAM_RED) && (data->p1.money < COST_MECH)) || ((data->whoseTurn == TEAM_BLUE) && (data->p2.money < COST_MECH)) || ((data->whoseTurn == TEAM_GREEN) && (data->p3.money < COST_MECH)) || ((data->whoseTurn == TEAM_YELLOW) && (data->p4.money < COST_MECH))) {
					setColor(DARKGREY);
				}
				printf("MECH            - $%d\n", COST_MECH);
				setColor(GREY);
				if (selection == 2) {
					if (((data->whoseTurn == TEAM_RED) && (data->p1.money < COST_RECON)) || ((data->whoseTurn == TEAM_BLUE) && (data->p2.money < COST_RECON)) || ((data->whoseTurn == TEAM_GREEN) && (data->p3.money < COST_RECON)) || ((data->whoseTurn == TEAM_YELLOW) && (data->p4.money < COST_RECON))) {
						if (data->p1.money < COST_RECON) {
							setColor(BROWN);
						}
					} else {
						setColor(YELLOW);
					}
				} else if (((data->whoseTurn == TEAM_RED) && (data->p1.money < COST_RECON)) || ((data->whoseTurn == TEAM_BLUE) && (data->p2.money < COST_RECON)) || ((data->whoseTurn == TEAM_GREEN) && (data->p3.money < COST_RECON)) || ((data->whoseTurn == TEAM_YELLOW) && (data->p4.money < COST_RECON))) {
					setColor(DARKGREY);
				}
				printf("RECON           - $%d\n", COST_RECON);
				setColor(GREY);
				if (selection == 3) {
					if (((data->whoseTurn == TEAM_RED) && (data->p1.money < COST_TANK)) || ((data->whoseTurn == TEAM_BLUE) && (data->p2.money < COST_TANK)) || ((data->whoseTurn == TEAM_GREEN) && (data->p3.money < COST_TANK)) || ((data->whoseTurn == TEAM_YELLOW) && (data->p4.money < COST_TANK))) {
						if (data->p1.money < COST_TANK) {
							setColor(BROWN);
						}
					} else {
						setColor(YELLOW);
					}
				} else if (((data->whoseTurn == TEAM_RED) && (data->p1.money < COST_TANK)) || ((data->whoseTurn == TEAM_BLUE) && (data->p2.money < COST_TANK)) || ((data->whoseTurn == TEAM_GREEN) && (data->p3.money < COST_TANK)) || ((data->whoseTurn == TEAM_YELLOW) && (data->p4.money < COST_TANK))) {
					setColor(DARKGREY);
				}
				printf("TANK            - $%d\n", COST_TANK);
				setColor(GREY);
				if (selection == 4) {
					if (((data->whoseTurn == TEAM_RED) && (data->p1.money < COST_MD_TANK)) || ((data->whoseTurn == TEAM_BLUE) && (data->p2.money < COST_MD_TANK)) || ((data->whoseTurn == TEAM_GREEN) && (data->p3.money < COST_MD_TANK)) || ((data->whoseTurn == TEAM_YELLOW) && (data->p4.money < COST_MD_TANK))) {
						if (data->p1.money < COST_MD_TANK) {
							setColor(BROWN);
						}
					} else {
						setColor(YELLOW);
					}
				} else if (((data->whoseTurn == TEAM_RED) && (data->p1.money < COST_MD_TANK)) || ((data->whoseTurn == TEAM_BLUE) && (data->p2.money < COST_MD_TANK)) || ((data->whoseTurn == TEAM_GREEN) && (data->p3.money < COST_MD_TANK)) || ((data->whoseTurn == TEAM_YELLOW) && (data->p4.money < COST_MD_TANK))) {
					setColor(DARKGREY);
				}
				printf("MEDIUM TANK     - $%d\n", COST_MD_TANK);
				setColor(GREY);
				if (selection == 5) {
					if (((data->whoseTurn == TEAM_RED) && (data->p1.money < COST_NEOTANK)) || ((data->whoseTurn == TEAM_BLUE) && (data->p2.money < COST_NEOTANK)) || ((data->whoseTurn == TEAM_GREEN) && (data->p3.money < COST_NEOTANK)) || ((data->whoseTurn == TEAM_YELLOW) && (data->p4.money < COST_NEOTANK))) {
						if (data->p1.money < COST_NEOTANK) {
							setColor(BROWN);
						}
					} else {
						setColor(YELLOW);
					}
				} else if (((data->whoseTurn == TEAM_RED) && (data->p1.money < COST_NEOTANK)) || ((data->whoseTurn == TEAM_BLUE) && (data->p2.money < COST_NEOTANK)) || ((data->whoseTurn == TEAM_GREEN) && (data->p3.money < COST_NEOTANK)) || ((data->whoseTurn == TEAM_YELLOW) && (data->p4.money < COST_NEOTANK))) {
					setColor(DARKGREY);
				}
				printf("NEOTANK         - $%d\n", COST_NEOTANK);
				setColor(GREY);
				if (selection == 6) {
					if (((data->whoseTurn == TEAM_RED) && (data->p1.money < COST_MEGATANK)) || ((data->whoseTurn == TEAM_BLUE) && (data->p2.money < COST_MEGATANK)) || ((data->whoseTurn == TEAM_GREEN) && (data->p3.money < COST_MEGATANK)) || ((data->whoseTurn == TEAM_YELLOW) && (data->p4.money < COST_MEGATANK))) {
						if (data->p1.money < COST_MEGATANK) {
							setColor(BROWN);
						}
					} else {
						setColor(YELLOW);
					}
				} else if (((data->whoseTurn == TEAM_RED) && (data->p1.money < COST_MEGATANK)) || ((data->whoseTurn == TEAM_BLUE) && (data->p2.money < COST_MEGATANK)) || ((data->whoseTurn == TEAM_GREEN) && (data->p3.money < COST_MEGATANK)) || ((data->whoseTurn == TEAM_YELLOW) && (data->p4.money < COST_MEGATANK))) {
					setColor(DARKGREY);
				}
				printf("MEGATANK        - $%d\n", COST_MEGATANK);
				setColor(GREY);
				if (selection == 7) {
					if (((data->whoseTurn == TEAM_RED) && (data->p1.money < COST_APC)) || ((data->whoseTurn == TEAM_BLUE) && (data->p2.money < COST_APC)) || ((data->whoseTurn == TEAM_GREEN) && (data->p3.money < COST_APC)) || ((data->whoseTurn == TEAM_YELLOW) && (data->p4.money < COST_APC))) {
						if (data->p1.money < COST_APC) {
							setColor(BROWN);
						}
					} else {
						setColor(YELLOW);
					}
				} else if (((data->whoseTurn == TEAM_RED) && (data->p1.money < COST_APC)) || ((data->whoseTurn == TEAM_BLUE) && (data->p2.money < COST_APC)) || ((data->whoseTurn == TEAM_GREEN) && (data->p3.money < COST_APC)) || ((data->whoseTurn == TEAM_YELLOW) && (data->p4.money < COST_APC))) {
					setColor(DARKGREY);
				}
				printf("APC             - $%d\n", COST_APC);
				setColor(GREY);
				if (selection == 8) {
					if (((data->whoseTurn == TEAM_RED) && (data->p1.money < COST_ARTILLERY)) || ((data->whoseTurn == TEAM_BLUE) && (data->p2.money < COST_ARTILLERY)) || ((data->whoseTurn == TEAM_GREEN) && (data->p3.money < COST_ARTILLERY)) || ((data->whoseTurn == TEAM_YELLOW) && (data->p4.money < COST_ARTILLERY))) {
						if (data->p1.money < COST_ARTILLERY) {
							setColor(BROWN);
						}
					} else {
						setColor(YELLOW);
					}
				} else if (((data->whoseTurn == TEAM_RED) && (data->p1.money < COST_ARTILLERY)) || ((data->whoseTurn == TEAM_BLUE) && (data->p2.money < COST_ARTILLERY)) || ((data->whoseTurn == TEAM_GREEN) && (data->p3.money < COST_ARTILLERY)) || ((data->whoseTurn == TEAM_YELLOW) && (data->p4.money < COST_ARTILLERY))) {
					setColor(DARKGREY);
				}
				printf("ARTILLERY       - $%d\n", COST_ARTILLERY);
				setColor(GREY);
				if (selection == 9) {
					if (((data->whoseTurn == TEAM_RED) && (data->p1.money < COST_ROCKETS)) || ((data->whoseTurn == TEAM_BLUE) && (data->p2.money < COST_ROCKETS)) || ((data->whoseTurn == TEAM_GREEN) && (data->p3.money < COST_ROCKETS)) || ((data->whoseTurn == TEAM_YELLOW) && (data->p4.money < COST_ROCKETS))) {
						if (data->p1.money < COST_ROCKETS) {
							setColor(BROWN);
						}
					} else {
						setColor(YELLOW);
					}
				} else if (((data->whoseTurn == TEAM_RED) && (data->p1.money < COST_ROCKETS)) || ((data->whoseTurn == TEAM_BLUE) && (data->p2.money < COST_ROCKETS)) || ((data->whoseTurn == TEAM_GREEN) && (data->p3.money < COST_ROCKETS)) || ((data->whoseTurn == TEAM_YELLOW) && (data->p4.money < COST_ROCKETS))) {
					setColor(DARKGREY);
				}
				printf("ROCKET LAUNCHER - $%d\n", COST_ROCKETS);
				setColor(GREY);
				if (selection == 10) {
					if (((data->whoseTurn == TEAM_RED) && (data->p1.money < COST_ANTI_AIR)) || ((data->whoseTurn == TEAM_BLUE) && (data->p2.money < COST_ANTI_AIR)) || ((data->whoseTurn == TEAM_GREEN) && (data->p3.money < COST_ANTI_AIR)) || ((data->whoseTurn == TEAM_YELLOW) && (data->p4.money < COST_ANTI_AIR))) {
						if (data->p1.money < COST_ANTI_AIR) {
							setColor(BROWN);
						}
					} else {
						setColor(YELLOW);
					}
				} else if (((data->whoseTurn == TEAM_RED) && (data->p1.money < COST_ANTI_AIR)) || ((data->whoseTurn == TEAM_BLUE) && (data->p2.money < COST_ANTI_AIR)) || ((data->whoseTurn == TEAM_GREEN) && (data->p3.money < COST_ANTI_AIR)) || ((data->whoseTurn == TEAM_YELLOW) && (data->p4.money < COST_ANTI_AIR))) {
					setColor(DARKGREY);
				}
				printf("ANTI-AIR CANNON - $%d\n", COST_ANTI_AIR);
				setColor(GREY);
				if (selection == 11) {
					if (((data->whoseTurn == TEAM_RED) && (data->p1.money < COST_MISSILES)) || ((data->whoseTurn == TEAM_BLUE) && (data->p2.money < COST_MISSILES)) || ((data->whoseTurn == TEAM_GREEN) && (data->p3.money < COST_MISSILES)) || ((data->whoseTurn == TEAM_YELLOW) && (data->p4.money < COST_MISSILES))) {
						if (data->p1.money < COST_MISSILES) {
							setColor(BROWN);
						}
					} else {
						setColor(YELLOW);
					}
				} else if (((data->whoseTurn == TEAM_RED) && (data->p1.money < COST_MISSILES)) || ((data->whoseTurn == TEAM_BLUE) && (data->p2.money < COST_MISSILES)) || ((data->whoseTurn == TEAM_GREEN) && (data->p3.money < COST_MISSILES)) || ((data->whoseTurn == TEAM_YELLOW) && (data->p4.money < COST_MISSILES))) {
					setColor(DARKGREY);
				}
				printf("MISSILES        - $%d\n", COST_MISSILES);
				setColor(GREY);
				
				keyPress = getkey();
				
				if (keyPress == KEY_UP) {
					if (selection > 0) {
						selection--;
					}
				} else if (keyPress == KEY_DOWN) {
					if (selection < 11) {
						selection++;
					}
				}
			}
			if (keyPress == KEY_ESCAPE) {
				data->interfaceMode = INTERFACEMODE_MAP;
			} else if (keyPress == KEY_SPACE) {
				if (selection == 0) {
					// INFANTRY
					if (data->whoseTurn == TEAM_RED) {
						if (data->p1.money >= COST_INFANTRY) {
							createUnit(data, data->cursor.x, data->cursor.y, INFANTRY, TEAM_RED);
							data->p1.money -= COST_INFANTRY;
						}
					} else if (data->whoseTurn == TEAM_BLUE) {
						if (data->p2.money >= COST_INFANTRY) {
							createUnit(data, data->cursor.x, data->cursor.y, INFANTRY, TEAM_BLUE);
							data->p2.money -= COST_INFANTRY;
						}
					} else if (data->whoseTurn == TEAM_GREEN) {
						if (data->p3.money >= COST_INFANTRY) {
							createUnit(data, data->cursor.x, data->cursor.y, INFANTRY, TEAM_GREEN);
							data->p3.money -= COST_INFANTRY;
						}
					} else if (data->whoseTurn == TEAM_YELLOW) {
						if (data->p4.money >= COST_INFANTRY) {
							createUnit(data, data->cursor.x, data->cursor.y, INFANTRY, TEAM_YELLOW);
							data->p4.money -= COST_INFANTRY;
						}
					}
				} else if (selection == 1) {
					// MECH
					if (data->whoseTurn == TEAM_RED) {
						if (data->p1.money >= COST_MECH) {
							createUnit(data, data->cursor.x, data->cursor.y, MECH, TEAM_RED);
							data->p1.money -= COST_MECH;
						}
					} else if (data->whoseTurn == TEAM_BLUE) {
						if (data->p2.money >= COST_MECH) {
							createUnit(data, data->cursor.x, data->cursor.y, MECH, TEAM_BLUE);
							data->p2.money -= COST_MECH;
						}
					} else if (data->whoseTurn == TEAM_GREEN) {
						if (data->p3.money >= COST_MECH) {
							createUnit(data, data->cursor.x, data->cursor.y, MECH, TEAM_GREEN);
							data->p3.money -= COST_MECH;
						}
					} else if (data->whoseTurn == TEAM_YELLOW) {
						if (data->p4.money >= COST_MECH) {
							createUnit(data, data->cursor.x, data->cursor.y, MECH, TEAM_YELLOW);
							data->p4.money -= COST_MECH;
						}
					}
				} else if (selection == 2) {
					// RECON
					if (data->whoseTurn == TEAM_RED) {
						if (data->p1.money >= COST_RECON) {
							createUnit(data, data->cursor.x, data->cursor.y, RECON, TEAM_RED);
							data->p1.money -= COST_RECON;
						}
					} else if (data->whoseTurn == TEAM_BLUE) {
						if (data->p2.money >= COST_RECON) {
							createUnit(data, data->cursor.x, data->cursor.y, RECON, TEAM_BLUE);
							data->p2.money -= COST_RECON;
						}
					} else if (data->whoseTurn == TEAM_GREEN) {
						if (data->p3.money >= COST_RECON) {
							createUnit(data, data->cursor.x, data->cursor.y, RECON, TEAM_GREEN);
							data->p3.money -= COST_RECON;
						}
					} else if (data->whoseTurn == TEAM_YELLOW) {
						if (data->p4.money >= COST_RECON) {
							createUnit(data, data->cursor.x, data->cursor.y, RECON, TEAM_YELLOW);
							data->p4.money -= COST_RECON;
						}
					}
				} else if (selection == 3) {
					// TANK
					if (data->whoseTurn == TEAM_RED) {
						if (data->p1.money >= COST_TANK) {
							createUnit(data, data->cursor.x, data->cursor.y, TANK, TEAM_RED);
							data->p1.money -= COST_TANK;
						}
					} else if (data->whoseTurn == TEAM_BLUE) {
						if (data->p2.money >= COST_TANK) {
							createUnit(data, data->cursor.x, data->cursor.y, TANK, TEAM_BLUE);
							data->p2.money -= COST_TANK;
						}
					} else if (data->whoseTurn == TEAM_GREEN) {
						if (data->p3.money >= COST_TANK) {
							createUnit(data, data->cursor.x, data->cursor.y, TANK, TEAM_GREEN);
							data->p3.money -= COST_TANK;
						}
					} else if (data->whoseTurn == TEAM_YELLOW) {
						if (data->p4.money >= COST_TANK) {
							createUnit(data, data->cursor.x, data->cursor.y, TANK, TEAM_YELLOW);
							data->p4.money -= COST_TANK;
						}
					}
				} else if (selection == 4) {
					// MD_TANK
					if (data->whoseTurn == TEAM_RED) {
						if (data->p1.money >= COST_MD_TANK) {
							createUnit(data, data->cursor.x, data->cursor.y, MD_TANK, TEAM_RED);
							data->p1.money -= COST_MD_TANK;
						}
					} else if (data->whoseTurn == TEAM_BLUE) {
						if (data->p2.money >= COST_MD_TANK) {
							createUnit(data, data->cursor.x, data->cursor.y, MD_TANK, TEAM_BLUE);
							data->p2.money -= COST_MD_TANK;
						}
					} else if (data->whoseTurn == TEAM_GREEN) {
						if (data->p3.money >= COST_MD_TANK) {
							createUnit(data, data->cursor.x, data->cursor.y, MD_TANK, TEAM_GREEN);
							data->p3.money -= COST_MD_TANK;
						}
					} else if (data->whoseTurn == TEAM_YELLOW) {
						if (data->p4.money >= COST_MD_TANK) {
							createUnit(data, data->cursor.x, data->cursor.y, MD_TANK, TEAM_YELLOW);
							data->p4.money -= COST_MD_TANK;
						}
					}
				} else if (selection == 5) {
					// NEOTANK
					if (data->whoseTurn == TEAM_RED) {
						if (data->p1.money >= COST_NEOTANK) {
							createUnit(data, data->cursor.x, data->cursor.y, NEOTANK, TEAM_RED);
							data->p1.money -= COST_NEOTANK;
						}
					} else if (data->whoseTurn == TEAM_BLUE) {
						if (data->p2.money >= COST_NEOTANK) {
							createUnit(data, data->cursor.x, data->cursor.y, NEOTANK, TEAM_BLUE);
							data->p2.money -= COST_NEOTANK;
						}
					} else if (data->whoseTurn == TEAM_GREEN) {
						if (data->p3.money >= COST_NEOTANK) {
							createUnit(data, data->cursor.x, data->cursor.y, NEOTANK, TEAM_GREEN);
							data->p3.money -= COST_NEOTANK;
						}
					} else if (data->whoseTurn == TEAM_YELLOW) {
						if (data->p4.money >= COST_NEOTANK) {
							createUnit(data, data->cursor.x, data->cursor.y, NEOTANK, TEAM_YELLOW);
							data->p4.money -= COST_NEOTANK;
						}
					}
				} else if (selection == 6) {
					// MEGATANK
					if (data->whoseTurn == TEAM_RED) {
						if (data->p1.money >= COST_MEGATANK) {
							createUnit(data, data->cursor.x, data->cursor.y, MEGATANK, TEAM_RED);
							data->p1.money -= COST_MEGATANK;
						}
					} else if (data->whoseTurn == TEAM_BLUE) {
						if (data->p2.money >= COST_MEGATANK) {
							createUnit(data, data->cursor.x, data->cursor.y, MEGATANK, TEAM_BLUE);
							data->p2.money -= COST_MEGATANK;
						}
					} else if (data->whoseTurn == TEAM_GREEN) {
						if (data->p3.money >= COST_MEGATANK) {
							createUnit(data, data->cursor.x, data->cursor.y, MEGATANK, TEAM_GREEN);
							data->p3.money -= COST_MEGATANK;
						}
					} else if (data->whoseTurn == TEAM_YELLOW) {
						if (data->p4.money >= COST_MEGATANK) {
							createUnit(data, data->cursor.x, data->cursor.y, MEGATANK, TEAM_YELLOW);
							data->p4.money -= COST_MEGATANK;
						}
					}
				} else if (selection == 7) {
					// APC
					if (data->whoseTurn == TEAM_RED) {
						if (data->p1.money >= COST_APC) {
							createUnit(data, data->cursor.x, data->cursor.y, APC, TEAM_RED);
							data->p1.money -= COST_APC;
						}
					} else if (data->whoseTurn == TEAM_BLUE) {
						if (data->p2.money >= COST_APC) {
							createUnit(data, data->cursor.x, data->cursor.y, APC, TEAM_BLUE);
							data->p2.money -= COST_APC;
						}
					} else if (data->whoseTurn == TEAM_GREEN) {
						if (data->p3.money >= COST_APC) {
							createUnit(data, data->cursor.x, data->cursor.y, APC, TEAM_GREEN);
							data->p3.money -= COST_APC;
						}
					} else if (data->whoseTurn == TEAM_YELLOW) {
						if (data->p4.money >= COST_APC) {
							createUnit(data, data->cursor.x, data->cursor.y, APC, TEAM_YELLOW);
							data->p4.money -= COST_APC;
						}
					}
				} else if (selection == 8) {
					// ARTILLERY
					if (data->whoseTurn == TEAM_RED) {
						if (data->p1.money >= COST_ARTILLERY) {
							createUnit(data, data->cursor.x, data->cursor.y, ARTILLERY, TEAM_RED);
							data->p1.money -= COST_ARTILLERY;
						}
					} else if (data->whoseTurn == TEAM_BLUE) {
						if (data->p2.money >= COST_ARTILLERY) {
							createUnit(data, data->cursor.x, data->cursor.y, ARTILLERY, TEAM_BLUE);
							data->p2.money -= COST_ARTILLERY;
						}
					} else if (data->whoseTurn == TEAM_GREEN) {
						if (data->p3.money >= COST_ARTILLERY) {
							createUnit(data, data->cursor.x, data->cursor.y, ARTILLERY, TEAM_GREEN);
							data->p3.money -= COST_ARTILLERY;
						}
					} else if (data->whoseTurn == TEAM_YELLOW) {
						if (data->p4.money >= COST_ARTILLERY) {
							createUnit(data, data->cursor.x, data->cursor.y, ARTILLERY, TEAM_YELLOW);
							data->p4.money -= COST_ARTILLERY;
						}
					}
				} else if (selection == 9) {
					// ROCKETS
					if (data->whoseTurn == TEAM_RED) {
						if (data->p1.money >= COST_ROCKETS) {
							createUnit(data, data->cursor.x, data->cursor.y, ROCKETS, TEAM_RED);
							data->p1.money -= COST_ROCKETS;
						}
					} else if (data->whoseTurn == TEAM_BLUE) {
						if (data->p2.money >= COST_ROCKETS) {
							createUnit(data, data->cursor.x, data->cursor.y, ROCKETS, TEAM_BLUE);
							data->p2.money -= COST_ROCKETS;
						}
					} else if (data->whoseTurn == TEAM_GREEN) {
						if (data->p3.money >= COST_ROCKETS) {
							createUnit(data, data->cursor.x, data->cursor.y, ROCKETS, TEAM_GREEN);
							data->p3.money -= COST_ROCKETS;
						}
					} else if (data->whoseTurn == TEAM_YELLOW) {
						if (data->p4.money >= COST_ROCKETS) {
							createUnit(data, data->cursor.x, data->cursor.y, ROCKETS, TEAM_YELLOW);
							data->p4.money -= COST_ROCKETS;
						}
					}
				} else if (selection == 10) {
					// ANTI_AIR
					if (data->whoseTurn == TEAM_RED) {
						if (data->p1.money >= COST_ANTI_AIR) {
							createUnit(data, data->cursor.x, data->cursor.y, ANTI_AIR, TEAM_RED);
							data->p1.money -= COST_ANTI_AIR;
						}
					} else if (data->whoseTurn == TEAM_BLUE) {
						if (data->p2.money >= COST_ANTI_AIR) {
							createUnit(data, data->cursor.x, data->cursor.y, ANTI_AIR, TEAM_BLUE);
							data->p2.money -= COST_ANTI_AIR;
						}
					} else if (data->whoseTurn == TEAM_GREEN) {
						if (data->p3.money >= COST_ANTI_AIR) {
							createUnit(data, data->cursor.x, data->cursor.y, ANTI_AIR, TEAM_GREEN);
							data->p3.money -= COST_ANTI_AIR;
						}
					} else if (data->whoseTurn == TEAM_YELLOW) {
						if (data->p4.money >= COST_ANTI_AIR) {
							createUnit(data, data->cursor.x, data->cursor.y, ANTI_AIR, TEAM_YELLOW);
							data->p4.money -= COST_ANTI_AIR;
						}
					}
				} else if (selection == 11) {
					// MISSILES
					if (data->whoseTurn == TEAM_RED) {
						if (data->p1.money >= COST_MISSILES) {
							createUnit(data, data->cursor.x, data->cursor.y, MISSILES, TEAM_RED);
							data->p1.money -= COST_MISSILES;
						}
					} else if (data->whoseTurn == TEAM_BLUE) {
						if (data->p2.money >= COST_MISSILES) {
							createUnit(data, data->cursor.x, data->cursor.y, MISSILES, TEAM_BLUE);
							data->p2.money -= COST_MISSILES;
						}
					} else if (data->whoseTurn == TEAM_GREEN) {
						if (data->p3.money >= COST_MISSILES) {
							createUnit(data, data->cursor.x, data->cursor.y, MISSILES, TEAM_GREEN);
							data->p3.money -= COST_MISSILES;
						}
					} else if (data->whoseTurn == TEAM_YELLOW) {
						if (data->p4.money >= COST_MISSILES) {
							createUnit(data, data->cursor.x, data->cursor.y, MISSILES, TEAM_YELLOW);
							data->p4.money -= COST_MISSILES;
						}
					}
				}
				data->interfaceMode = INTERFACEMODE_MAP;
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
	/// This determines which UI to draw.
	short ui = 0;
	// This is unclean and is going to win no points in neatness.
	if (data->interfaceMode == INTERFACEMODE_MENU_UNIT) {
		ui = 5;
	} else if ((data->whoseTurn == (data->mapData[data->cursor.x][data->cursor.y] / 10)) && ((data->mapData[data->cursor.x][data->cursor.y] % 10) == 3)) {
		ui = 1;
	} else if ((data->whoseTurn == (data->mapData[data->cursor.x][data->cursor.y] / 10)) && ((data->mapData[data->cursor.x][data->cursor.y] % 10) == 4)) {
		ui = 2;
	} else if ((data->whoseTurn == (data->mapData[data->cursor.x][data->cursor.y] / 10)) && ((data->mapData[data->cursor.x][data->cursor.y] % 10) == 5)) {
		ui = 3;
	} else if (data->interfaceMode == INTERFACEMODE_MENU_FIELD) {
		ui = 4;
	}
	/// If the selection was on a base, airport, or port, this comes up.
	if ((ui == 1) || (ui == 2) || (ui == 3)) {
		/// This breaks when the user hits either ESCAPE or SPACE.
		while (keyPress != KEY_ESCAPE && keyPress != KEY_SPACE) {
			/// Firstly the map is drawn.
			mapDraw(data);
			
			/// Then the menu items are displayed. If they're
			/// highlighted, they turn yellow.
			if (selection == 0) {
				setColor(YELLOW);
			}
			printf("BUY UNIT\n");
			setColor(GREY);
			if (selection == 1) {
				setColor(YELLOW);
			}
			printf("END TURN\n");
			setColor(GREY);
			if (selection == 2) {
				setColor(YELLOW);
			}
			printf("INFO (UNFINISHED)\n");
			setColor(GREY);
			if (selection == 3) {
				setColor(YELLOW);
			}
			printf("SAVE (UNFINISHED)\n");
			setColor(GREY);
			if (selection == 4) {
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
				if (selection < 4) {
					selection++;
				}
			}
		}
	/// Similarly, if the field is selected...
	} else if (ui == 4) {
		while (keyPress != KEY_ESCAPE && keyPress != KEY_SPACE) {
			mapDraw(data);
			
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
			
			keyPress = getkey();
			
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
	} else if (ui == 5) {
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
			printf("ATTACK\n");
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
		if (ui == 1) {
			if (selection == 0) {
				// BUY UNIT
				data->interfaceMode = INTERFACEMODE_BUY_LAND;
			} else if (selection == 1) {
				// END TURN
				endTurn(data);
				data->interfaceMode = INTERFACEMODE_MAP;
			} else if (selection == 2) {
				// HELP
				data->interfaceMode = INTERFACEMODE_MAP;
			} else if (selection == 3) {
				// SAVE
				data->interfaceMode = INTERFACEMODE_MAP;
			} else if (selection == 4) {
				// QUIT
				data->interfaceMode = INTERFACEMODE_QUIT;
			}
		} else if (ui == 2) {
			if (selection == 0) {
				// BUY UNIT
				data->interfaceMode = INTERFACEMODE_BUY_AIR;
			} else if (selection == 1) {
				// END TURN
				endTurn(data);
				data->interfaceMode = INTERFACEMODE_MAP;
			} else if (selection == 2) {
				// HELP
				data->interfaceMode = INTERFACEMODE_MAP;
			} else if (selection == 3) {
				// SAVE
				data->interfaceMode = INTERFACEMODE_MAP;
			} else if (selection == 4) {
				// QUIT
				data->interfaceMode = INTERFACEMODE_QUIT;
			}
		} else if (ui == 3) {
			if (selection == 0) {
				// BUY UNIT
				data->interfaceMode = INTERFACEMODE_BUY_SEA;
			} else if (selection == 1) {
				// END TURN
				endTurn(data);
				data->interfaceMode = INTERFACEMODE_MAP;
			} else if (selection == 2) {
				// HELP
				data->interfaceMode = INTERFACEMODE_MAP;
			} else if (selection == 3) {
				// SAVE
				data->interfaceMode = INTERFACEMODE_MAP;
			} else if (selection == 4) {
				// QUIT
				data->interfaceMode = INTERFACEMODE_QUIT;
			}
		} else if (ui == 4) {
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
		} else if (ui == 5) {
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