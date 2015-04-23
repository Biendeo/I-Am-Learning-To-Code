#include <stdio.h>
#include <stdlib.h>

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
	unsigned char mapData[20][5];
	// MAX_UNITS won't be overflowed, set this to a high enough level that people won't reach it.
	player p1;
	player p2;
	unit currentUnits[5];
} game;

void doThis (game *data);
void doThat (game *data);

int main (int argc, char *argv[]) {
	game data;
	game *dataPtr = &data;
	data.p1.money = 1;
	printf("%d\n", data.p1.money);
	doThis (dataPtr);
	printf("%d\n", data.p1.money);
	return EXIT_SUCCESS;
}

void doThis (game *data) {
	data->p1.money = 2;
	printf("%d\n", data->p1.money);
	doThat (data);
	printf("%d\n", data->p1.money);
}

void doThat (game *data) {
	data->p1.money = 3;
}