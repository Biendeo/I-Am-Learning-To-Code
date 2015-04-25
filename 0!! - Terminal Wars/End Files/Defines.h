/// End-user defines
#define START_GAME game *data = buildGame ()
#define END_GAME freeGame(data)

/// Team colours
#define NONE   0
#define RED    1
#define BLUE   2
#define GREEN  3
#define YELLOW 4

/// Unit types
#define INFANTRY  1
#define MECH      2
#define RECON     3
#define TANK      4
#define MD_TANK   5
#define NEOTANK   6
#define MEGATANK  7
#define APC       8  // SKIP
#define ARTILLERY 9
#define ROCKETS   10
#define ANTI_AIR  11 // SKIP

/// Map boundaries
// These are going to be phased out. The map data will be read to
// include the size (or maybe a dynamic system to find it).
#define MAP_WIDTH  16
#define MAP_HEIGHT 12

/// Map tile types
/// These are the values stored in memory
// The ordering needs to be sorted out (and do the same below).
#define NULL_HQ       1  // This shouldn't be used.
#define NULL_CITY     2 
#define NULL_BASE     3 
#define RED_HQ        11
#define RED_CITY      12
#define RED_BASE      13
#define BLUE_HQ       21
#define BLUE_CITY     22
#define BLUE_BASE     23
#define GREEN_HQ      31
#define GREEN_CITY    32
#define GREEN_BASE    33
#define YELLOW_HQ     41
#define YELLOW_CITY   42
#define YELLOW_BASE   43
#define PLAIN         51
#define ROAD          52
#define SEA           53
#define RIVER         54
#define WOOD          55
#define MOUNTAIN      56
#define BRIDGE        57
#define SHOAL         58
#define REEF          59

/// Map file characters
/// These are the values that you type into the file
// This needs to be a little bit more intuitive.
// Currently, think of it with a left-to-right style.
// Different rows and SHIFT combos give different sets of tiles.
#define CHAR_NULL_HQ       '!'
#define CHAR_NULL_CITY     '@'
#define CHAR_NULL_BASE     '#'
#define CHAR_RED_HQ        'a'
#define CHAR_RED_CITY      's'
#define CHAR_RED_BASE      'd'
#define CHAR_BLUE_HQ       'z'
#define CHAR_BLUE_CITY     'x'
#define CHAR_BLUE_BASE     'c'
#define CHAR_GREEN_HQ      'A'
#define CHAR_GREEN_CITY    'S'
#define CHAR_GREEN_BASE    'D'
#define CHAR_YELLOW_HQ     'Z'
#define CHAR_YELLOW_CITY   'X'
#define CHAR_YELLOW_BASE   'C'
#define CHAR_PLAIN         '1'
#define CHAR_ROAD          '2'
#define CHAR_SEA           '3'
#define CHAR_RIVER         '4'
#define CHAR_WOOD          '5'
#define CHAR_MOUNTAIN      '6'
#define CHAR_BRIDGE        '7'
#define CHAR_SHOAL         '8'
#define CHAR_REEF          '9'

/// The maximum units in the field
// THIS WILL BE TWEAKED
#define MAX_UNITS 100

/// Error messages
#define ERROR_CODE data->errorCode
#define ALL_GOOD 0
#define TEST_FAILED 1
#define BAD_SETUP_INPUT 2
#define FILE_NOT_FOUND 3
#define MAP_INVALID_SIZE 4

/*
Unit		Type		Cost	Move	Range	Fuel	Vision
Infantry	Infantry	1,000	3		1		99		3
Mech		Infantry	3,000	2		1		70		2
Recon		Vehicle		4,000	8		1		80		5
Tank		Vehicle		7,000	6		1		70		3
Medium Tank	Vehicle		16,000	5		1		50		1
Neotank		Vehicle		22,000	6		1		99		1
Megatank	Vehicle		28,000	4		1		50		1
APC			Vehicle		5,000	6		---		70		1
Artillery	Vehicle		6,000	5		2-3		99		1
Rockets		Vehicle		15,000	5		3-5		50		1
Anti-Air	Vehicle		8,000	6		1		60		2
Piperunner	Vehicle		20,000	9		2-5		99		4
Oozium		—			—		1		1		∞		1		
Lander		Ship		12,000	6		---		99		1
Cruiser		Ship		18,000	6		1		99		3
Submarine	Submarine	20,000	5		1		60		5
Battleship	Ship		28,000	5		2-6		99		2
Carrier		Ship		30,000	5		3-8		99		4
Black Boat	Ship		7,500	7		---		60		1
B Copter	Copter		9,000	6		1		99		3
T Copter	Copter		5,000	6		---		99		2
Fighter		Plane		28,000	9		1		99		2
Bomber		Plane		22,000	7		1		99		2
Stealth		Plane		24,000	6		1		60		4
Black Bomb	Bomb		24,000	9		1-3		99		1
*/