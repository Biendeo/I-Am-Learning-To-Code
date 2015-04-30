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
	setColor(LIGHTGREEN);
	printf("TERMINAL WARS");
	setColor(GREY);
	printf("        |\n");
	printf("|                              |\n");
	printf("+------------------------------+\n");
	printf("\n");
	printf("An attempt to recreate the game Advance Wars in C.\n");
	printf("\n");
	printf("Version \"Stage 8\"\n\n");
	
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
				if (unitPos < MAX_UNITS) {
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
	// Before you do this, store all the necessary data at first.
}

void drawFieldUI (game *data, short x, short y) {
	
}

void testDrawing (game *data) {
	createUnit(data, 4, 3, INFANTRY, TEAM_RED);
	createUnit(data, 8, 6, MECH, TEAM_RED);
	createUnit(data, 5, 3, ARTILLERY, TEAM_BLUE);
	createUnit(data, 13, 10, MEGATANK, TEAM_BLUE);
	createUnit(data, 11, 3, TANK, TEAM_BLUE);
	createUnit(data, 1, 10, MECH, TEAM_GREEN);
	createUnit(data, 12, 6, APC, TEAM_YELLOW);
	createUnit(data, 10, 10, NEOTANK, TEAM_YELLOW);
	
	deleteUnit(data, 4);
	
	createUnit(data, 2, 2, BATT_COP, TEAM_GREEN);
	
	data->cursor.x = 5;
	data->cursor.y = 4;
	data->drawMode = DRAWMODE_MAP;
	data->interfaceMode = INTERFACEMODE_MAP;
	
	// Because KEY_ESCAPE = 0, it has to be set to another number.
	// Try making this an unsigned char, as the numbers don't go higher than 135.
	int keyPress = 1;
	short selectedUnit = 0;
	while (keyPress != KEY_ESCAPE) {
		if (data->interfaceMode == INTERFACEMODE_MAP) {
			mapDraw(data);
			printf("Moving cursor\n");
			printf("Cursor: %d, %d\n", data->cursor.x, data->cursor.y);
			keyPress = getkey();
			if (keyPress == KEY_UP) {
				moveCursor(data, UP);
			} else if (keyPress == KEY_DOWN) {
				moveCursor(data, DOWN);
			} else if (keyPress == KEY_LEFT) {
				moveCursor(data, LEFT);
			} else if (keyPress == KEY_RIGHT) {
				moveCursor(data, RIGHT);
			} else if (keyPress == KEY_SPACE) {
				selectedUnit = unitGetter(data, data->cursor.x, data->cursor.y);
				if (selectedUnit != MAX_UNITS) {
					data->interfaceMode = INTERFACEMODE_MOVE;
				}
			}
		} else if (data->interfaceMode == INTERFACEMODE_MOVE) {
			mapDraw(data);
			printf("Moving unit %d\n", selectedUnit);
			printf("Cursor is at: %d, %d\n", data->cursor.x, data->cursor.y);
			printf("Unit is team %d, unit %d\n", data->unitData[selectedUnit].player, data->unitData[selectedUnit].unitType);
			printf("Unit has %g/10 health and %d/%d ammo.\n", data->unitData[selectedUnit].health, data->unitData[selectedUnit].ammo1, data->unitData[selectedUnit].maxAmmo1);
			keyPress = getkey();
			if (keyPress == KEY_UP) {
				moveUnit(data, selectedUnit, UP);
			} else if (keyPress == KEY_DOWN) {
				moveUnit(data, selectedUnit, DOWN);
			} else if (keyPress == KEY_LEFT) {
				moveUnit(data, selectedUnit, LEFT);
			} else if (keyPress == KEY_RIGHT) {
				moveUnit(data, selectedUnit, RIGHT);
			} else if (keyPress == KEY_SPACE) {
				data->interfaceMode = INTERFACEMODE_MAP;
			}
		}
		if (keyPress == KEY_ENTER) {
			if (data->drawMode == DRAWMODE_MAP) {
				data->drawMode = DRAWMODE_UNITS;
			} else if (data->drawMode == DRAWMODE_UNITS) {
				data->drawMode = DRAWMODE_MAP;
			}
		}
	}
}