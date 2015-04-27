#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Defines.h"
#include "rlutil.h"
#include "GameUI.h"
#include "MainGame.h"
#include "GameAI.h"
#include "FileIO.h"
#include "DrawingUI.h"

void screenSplash() {
	setColor(GREY);
	printf("+------------------------------+\n");
	printf("|                              |\n");
	printf("|         ");
	setColor(RED);
	printf("TERMINAL WARS");
	setColor(GREY);
	printf("        |\n");
	printf("|                              |\n");
	printf("+------------------------------+\n");
	printf("\n");
	printf("An attempt to recreate the game Advance Wars in C.\n");
	printf("\n");
	printf("Version \"I haven't got a version yet\"\n");
	getkey();
}

void mapDraw(game *data) {
	short x = 0;
	short y = 0;
	short arrayPos = 0;
	char didDraw = 0;
	cls();
	while (y < MAP_HEIGHT) {
		while (x < MAP_WIDTH) {
			if (data->drawMode == DRAWMODE_UNITS) {
				arrayPos = 0;
				didDraw = 0;
				while ((arrayPos < MAX_UNITS) && (didDraw == 0)) {
					if ((data->unitData[arrayPos].x == x) &&
    					(data->unitData[arrayPos].y == y)) {
						drawUnit(data, arrayPos);
						didDraw = 1;
					}
					arrayPos++;
				}
				
				if (didDraw == 0) {
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

void drawUnit (game *data, short arrayPos) {
	if (data->unitData[arrayPos].player == TEAM_RED) {
		setColor(RED);
	} else if (data->unitData[arrayPos].player == TEAM_BLUE) {
		setColor(BLUE);
	} else if (data->unitData[arrayPos].player == TEAM_GREEN) {
		setColor(GREEN);
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
	if (data->mapData[x][y] == NULL_HQ) {
		setColor(GREY);
		printf("%c", CHAR_MAP_HQ);
	} else if (data->mapData[x][y] == NULL_CITY) {
		setColor(GREY);
		printf("%c", CHAR_MAP_CITY);
	} else if (data->mapData[x][y] == NULL_BASE) {
		setColor(GREY);
		printf("%c", CHAR_MAP_BASE);
	} else if (data->mapData[x][y] == NULL_AIRPORT) {
		setColor(GREY);
		printf("%c", CHAR_MAP_AIRPORT);
	} else if (data->mapData[x][y] == NULL_PORT) {
		setColor(GREY);
		printf("%c", CHAR_MAP_PORT);
	} else if (data->mapData[x][y] == RED_HQ) {
		setColor(RED);
		printf("%c", CHAR_MAP_HQ);
	} else if (data->mapData[x][y] == RED_CITY) {
		setColor(RED);
		printf("%c", CHAR_MAP_CITY);
	} else if (data->mapData[x][y] == RED_BASE) {
		setColor(RED);
		printf("%c", CHAR_MAP_BASE);
	} else if (data->mapData[x][y] == RED_AIRPORT) {
		setColor(RED);
		printf("%c", CHAR_MAP_AIRPORT);
	} else if (data->mapData[x][y] == RED_PORT) {
		setColor(RED);
		printf("%c", CHAR_MAP_PORT);
	} else if (data->mapData[x][y] == BLUE_HQ) {
		setColor(BLUE);
		printf("%c", CHAR_MAP_HQ);
	} else if (data->mapData[x][y] == BLUE_CITY) {
		setColor(BLUE);
		printf("%c", CHAR_MAP_CITY);
	} else if (data->mapData[x][y] == BLUE_BASE) {
		setColor(BLUE);
		printf("%c", CHAR_MAP_BASE);
	} else if (data->mapData[x][y] == BLUE_AIRPORT) {
		setColor(BLUE);
		printf("%c", CHAR_MAP_AIRPORT);
	} else if (data->mapData[x][y] == BLUE_PORT) {
		setColor(BLUE);
		printf("%c", CHAR_MAP_PORT);
	} else if (data->mapData[x][y] == GREEN_HQ) {
		setColor(GREEN);
		printf("%c", CHAR_MAP_HQ);
	} else if (data->mapData[x][y] == GREEN_CITY) {
		setColor(GREEN);
		printf("%c", CHAR_MAP_CITY);
	} else if (data->mapData[x][y] == GREEN_BASE) {
		setColor(GREEN);
		printf("%c", CHAR_MAP_BASE);
	} else if (data->mapData[x][y] == GREEN_AIRPORT) {
		setColor(GREEN);
		printf("%c", CHAR_MAP_AIRPORT);
	} else if (data->mapData[x][y] == GREEN_PORT) {
		setColor(GREEN);
		printf("%c", CHAR_MAP_PORT);
	} else if (data->mapData[x][y] == YELLOW_HQ) {
		setColor(YELLOW);
		printf("%c", CHAR_MAP_HQ);
	} else if (data->mapData[x][y] == YELLOW_CITY) {
		setColor(YELLOW);
		printf("%c", CHAR_MAP_CITY);
	} else if (data->mapData[x][y] == YELLOW_BASE) {
		setColor(YELLOW);
		printf("%c", CHAR_MAP_BASE);
	} else if (data->mapData[x][y] == YELLOW_AIRPORT) {
		setColor(YELLOW);
		printf("%c", CHAR_MAP_AIRPORT);
	} else if (data->mapData[x][y] == YELLOW_PORT) {
		setColor(YELLOW);
		printf("%c", CHAR_MAP_PORT);
	}
	else if (data->mapData[x][y] == PLAIN) {
		setColor(GREEN);
		printf("%c", CHAR_MAP_PLAIN);
	} else if (data->mapData[x][y] == ROAD) {
		setColor(GREY);
		printf("%c", CHAR_MAP_ROAD);
	} else if (data->mapData[x][y] == SEA) {
		setColor(BLUE);
		printf("%c", CHAR_MAP_SEA);
	} else if (data->mapData[x][y] == RIVER) {
		setColor(BLUE);
		printf("%c", CHAR_MAP_RIVER);
	} else if (data->mapData[x][y] == WOOD) {
		setColor(BROWN);
		printf("%c", CHAR_MAP_WOOD);
	} else if (data->mapData[x][y] == MOUNTAIN) {
		setColor(BROWN);
		printf("%c", CHAR_MAP_MOUNTAIN);
	} else if (data->mapData[x][y] == BRIDGE) {
		setColor(YELLOW);
		printf("%c", CHAR_MAP_BRIDGE);
	} else if (data->mapData[x][y] == SHOAL) {
		setColor(BLUE);
		printf("%c", CHAR_MAP_SHOAL);
	} else if (data->mapData[x][y] == REEF) {
		setColor(BLUE);
		printf("%c", CHAR_MAP_REEF);
	}
}

void testDrawing (game *data) {
	data->unitData[0].unitType = INFANTRY;
	data->unitData[0].player = TEAM_RED;
	data->unitData[0].x = 4;
	data->unitData[0].y = 3;
	data->unitData[1].unitType = MECH;
	data->unitData[1].player = TEAM_RED;
	data->unitData[1].x = 8;
	data->unitData[1].y = 6;
	data->unitData[2].unitType = ARTILLERY;
	data->unitData[2].player = TEAM_BLUE;
	data->unitData[2].x = 5;
	data->unitData[2].y = 3;
	data->unitData[3].unitType = MEGATANK;
	data->unitData[3].player = TEAM_BLUE;
	data->unitData[3].x = 13;
	data->unitData[3].y = 10;
	data->unitData[4].unitType = TANK;
	data->unitData[4].player = TEAM_BLUE;
	data->unitData[4].x = 11;
	data->unitData[4].y = 3;
	data->unitData[5].unitType = MECH;
	data->unitData[5].player = TEAM_GREEN;
	data->unitData[5].x = 1;
	data->unitData[5].y = 10;
	data->unitData[6].unitType = APC;
	data->unitData[6].player = TEAM_YELLOW;
	data->unitData[6].x = 12;
	data->unitData[6].y = 6;
	data->unitData[7].unitType = NEOTANK;
	data->unitData[7].player = TEAM_YELLOW;
	data->unitData[7].x = 10;
	data->unitData[7].y = 10;
	data->drawMode = DRAWMODE_MAP;
	mapDraw(data);
	getkey();
	data->drawMode = DRAWMODE_UNITS;
	mapDraw(data);
	getkey();
}