#include "Defines.h"

typedef struct unitdata {
	/// This defines what type of unit it is.
	char unitType;
	
	/// This determines who owns a unit.
	char player;
	
	/// This tracks how much health a unit currently has.
	float health;
	
	/// This tracks how much ammo a unit has for both weapons.
	/// An ammo of -1 means infinite ammo.
	char ammo1;
	char ammo2;
	
	/// This tracks how much fuel a unit has.
	char fuel;
	
	/// This tracks how far a unit has left to move for that turn.
	char movement;
	
	// This tracks where the unit is.
	short x;
	short y;
} unit;

typedef struct playerdata {
	/// This determines if the player is a human (1) or a bot (2).
	char isItHuman;
	
	/// This determines the player's color (number in the defines).
	char color;
	
	/// This stores how much money a player has.
	int money;
	
	/// This tracks the number of buildings and units a player has.
	short buildingsOwned;
	short unitsOwned;
} player;

typedef struct buildingdata {
	/// This determines what kind of building it is.
	char buildingType;
	
	/// This determines who owns it.
	char player;
	
	/// This is where it is.
	short x;
	short y;
} building;

typedef struct cursor {
	/// This is to access the cursor position anywhere in the program.
	short x;
	short y;
} cursor;

typedef struct gamedata {
	/// This will count the number turn it is. No effect in game, but
	/// it's a data point to follow.
	int turnNum;
	
	/// This will be an input determining how many players (whether AI
	/// or human) are in this game. It's used for cycling new turns.
	char numberOfPlayers;
	
	/// These contain all the data that each player uses.
	player p1;
	player p2;
	player p3;
	player p4;
	
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
	unit unitData[MAX_UNITS];
	
	/// This stores all the data for the buildings. Like the map
	/// dimensions, MAX_BUILDINGS should be determined by the map, not
	/// the program.
	building buildingData[MAX_BUILDINGS];
	
	/// This stores the cursor position.
	cursor cursor;
	
	/// This stores an error code if the program needs to exit.
	char errorCode;
} game;

game *buildGame ();
void initialiseGame (game *data);
void checkInitialiseGame (game *data);
void scanMap (game *data);
void freeGame (game *data);