#include "Defines.h"

typedef struct unitdata {
	/// This defines what type of unit it is.
	char unitType;
	char player;
	float health;
	char ammo1;
	char ammo2;
	short fuel;
} unit;

typedef struct playerdata {
	/// This one determines if the player is a human (0) or a bot (1).
	char isItPlayer;
	
	char color;
	int money;
	short buildingsOwned;
	short currentUnits;
} player;

typedef struct buildingdata {
	char buildingType;
	char player;
} building;

typedef struct gamedata {
	/// This will count the number turn it is. No effect in game, but
	/// it's a data point to follow.
	int turnNum;
	
	/// This will be an input determining how many players (whether AI
	/// or human) are in this game. It's used for cycling new turns.
	char numberOfPlayers;
	
	/// These contain all the data that each player uses.
	/// The actual game is 4 player, so I'll be designing with that in
	/// mind (but it's not going to be implemented).
	player p1;
	player p2;
	// player p3;
	// player p4;
	
	/// This will note whose turn it is. This is determined via a
	/// remainder detector.
	char whoseTurn;
	
	/// This will store all the map data. It will initially be read from
	/// a file, but then stored in memory (and eventually outputted to
	/// the save data). This is purely so that File IO is minimal.
	unsigned char mapData[MAP_WIDTH][MAP_HEIGHT];

	/// This stores all the data for the units on the field. MAX_UNITS
	/// is a value that shouldn't be overflowed, so it needs to be set
	/// high enough that you don't reach it, but low enough that it
	/// doesn't use too much memory.
	unit currentUnits[MAX_UNITS];
	
	/// This stores an error code if the program needs to exit.
	char errorCode;
} game;

game *buildGame ();
void initialiseGame (game *data);
void checkInitialiseGame (game *data);
void reportError (game *data, char errorCode);
void startArguments (game *data);
void freeGame (game *data);