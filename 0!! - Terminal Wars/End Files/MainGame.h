#include "Defines.h"

typedef struct unitdata {
	char unitType;
	char player;
	float health;
	char ammo1;
	char ammo2;
	short fuel;
} unit;

typedef struct playerdata {
	int money;
	short buildingsOwned;
	short currentUnits;
} player;

typedef struct buildingdata {
	char buildingType;
	char player;
} building;

typedef struct gamedata {
	int turnNum;
	char whoseTurn;
	unsigned char mapData[MAP_WIDTH][MAP_HEIGHT];
	// MAX_UNITS won't be overflowed, set this to a high enough level that people won't reach it.
	player p1;
	player p2;
	unit currentUnits[MAX_UNITS];
} game;

int initialiseGame (game *gameData);
int checkInitialiseGame (game *gameData);