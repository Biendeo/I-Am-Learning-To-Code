/// End-user defines
#define START_GAME game *data = buildGame ()
#define END_GAME freeGame(data)

#define YES 1
#define NO  0

#define HUMAN 1
#define BOT   2

#define DRAWMODE_MAP   1
#define DRAWMODE_UNITS 2

/// Team colours
#define TEAM_NONE   0
#define TEAM_RED    1
#define TEAM_BLUE   2
#define TEAM_GREEN  3
#define TEAM_YELLOW 4

/// Unit types
// The skips are currently for transport units.
// If I can, I'll try to get those working (but no guarantees).
#define INFANTRY  1
#define MECH      2
#define RECON     3
#define TANK      4
#define MD_TANK   5
#define NEOTANK   6
#define MEGATANK  7
#define APC       8  // SKIP FOR NOW
#define ARTILLERY 9
#define ROCKETS   10
#define ANTI_AIR  11
#define BATT_COP  12
#define TRAN_COP  13 // SKIP FOR NOW
#define FIGHTER   14
#define BOMBER    15
#define STEALTH   16
#define LANDER    17 // SKIP FOR NOW
#define CRUISER   18
#define SUB       19
#define BATT_SHIP 20
#define CARRIER   21 // SKIP FOR NOW

/// Characters for unit types
#define CHAR_INFANTRY  'i'
#define CHAR_MECH      'm'
#define CHAR_RECON     'r'
#define CHAR_TANK      't'
#define CHAR_MD_TANK   'T'
#define CHAR_NEOTANK   'N'
#define CHAR_MEGATANK  'M'
#define CHAR_APC       'a'
#define CHAR_ARTILLERY 'A'
#define CHAR_ROCKETS   'R'
#define CHAR_ANTI_AIR  'I'
#define CHAR_BATT_COP  'C'
#define CHAR_TRAN_COP  'c'
#define CHAR_FIGHTER   'F'
#define CHAR_BOMBER    'B'
#define CHAR_STEALTH   'S'
#define CHAR_LANDER    'L'
#define CHAR_CRUISER   'u'
#define CHAR_SUB       's'
#define CHAR_BATT_SHIP 'b'
#define CHAR_CARRIER   'E'

/// Vehicle transport types
#define MOVE_INFANTRY 1
#define MOVE_MECH     2
#define MOVE_TIRES    3
#define MOVE_TREAD    4
#define MOVE_AIR      5
#define MOVE_SHIP     6
#define MOVE_CARRIER  7

/// Tile movement costs
// THIS IS INCOMPLETE
// Setting a value to 0 will mean a unit cannot move onto it.
#define MOVE_GRASS_INFANTRY 1
#define MOVE_GRASS_MECH     1
#define MOVE_GRASS_TIRES    2
#define MOVE_GRASS_TREAD    1
#define MOVE_GRASS_AIR      1
#define MOVE_GRASS_SHIP     0
#define MOVE_GRASS_CARRIER  0

// All buildings use the same costs as roads.
#define MOVE_ROAD_INFANTRY 1
#define MOVE_ROAD_MECH     1
#define MOVE_ROAD_TIRES    1
#define MOVE_ROAD_TREAD    1
#define MOVE_ROAD_AIR      1
#define MOVE_ROAD_SHIP     0
#define MOVE_ROAD_CARRIER  0

/// Tile defense ranks
// THIS IS INCOMPLETE
#define DEFENSE_GRASS 1
#define DEFENSE_ROAD  0
#define DEFENSE_HQ    5

/// Default unit properties
// THIS IS INCOMPLETE
// I might need to change the style of these.
#define COST_INFANTRY      1000
#define MOVETYPE_INFANTRY  MOVE_INFANTRY
#define MOVESPEED_INFANTRY 3
#define MAXAMMO_INFANTRY_1 0
#define MAXFUEL_INFANTRY   99
#define VISION_INFANTRY    3
#define DRAWCHAR_INFANTRY  'I'

/// Base damage values (percentages)
// Use the style DAMAGE_ATTACKER_DEFENDER
// THIS IS INCOMPLETE
#define DAMAGE_INFANTRY_INFANTRY 50

/// Map boundaries
// These are going to be phased out. The map data will be read to
// include the size (or maybe a dynamic system to find it).
#define MAP_WIDTH  14
#define MAP_HEIGHT 12

/// Map tile types
/// These are the values stored in memory
// The ordering needs to be sorted out (and do the same below).
#define NULL_HQ        1  // This shouldn't be used.
#define NULL_CITY      2 
#define NULL_BASE      3 
#define NULL_AIRPORT   4
#define NULL_PORT      5
#define RED_HQ         11
#define RED_CITY       12
#define RED_BASE       13
#define RED_AIRPORT    14
#define RED_PORT       15
#define BLUE_HQ        21
#define BLUE_CITY      22
#define BLUE_BASE      23
#define BLUE_AIRPORT   24
#define BLUE_PORT      25
#define GREEN_HQ       31
#define GREEN_CITY     32
#define GREEN_BASE     33
#define GREEN_AIRPORT  34
#define GREEN_PORT     35
#define YELLOW_HQ      41
#define YELLOW_CITY    42
#define YELLOW_BASE    43
#define YELLOW_AIRPORT 44
#define YELLOW_PORT    45
#define PLAIN          51
#define ROAD           52
#define SEA            53
#define RIVER          54
#define WOOD           55
#define MOUNTAIN       56
#define BRIDGE         57
#define SHOAL          58
#define REEF           59

/// Map draw characters
/// These are the values that are printed when the map is drawn.
// I think it's a little bit counter-inutitive how the colour is
// determined in the drawing function, but the character is determined
// here. Maybe I can merge both.
#define CHAR_MAP_HQ             '!'
#define CHAR_MAP_CITY           '#'
#define CHAR_MAP_BASE           '%'
#define CHAR_MAP_AIRPORT        '$'
#define CHAR_MAP_PORT           '&'
#define CHAR_MAP_PLAIN          '_'
#define CHAR_MAP_ROAD           '+'
#define CHAR_MAP_SEA            '~'
#define CHAR_MAP_RIVER          '_'
#define CHAR_MAP_WOOD           '#'
#define CHAR_MAP_MOUNTAIN       '^'
#define CHAR_MAP_BRIDGE         '+'
#define CHAR_MAP_SHOAL          ':'
#define CHAR_MAP_REEF           '.'

/// Map file characters
/// These are the values that you type into the file
// This needs to be a little bit more intuitive.
// Currently, think of it with a left-to-right style.
// Different rows and SHIFT combos give different sets of tiles.
#define CHAR_NULL_HQ        '!'
#define CHAR_NULL_CITY      '@'
#define CHAR_NULL_BASE      '#'
#define CHAR_NULL_AIRPORT   '$'
#define CHAR_NULL_PORT      '%'
#define CHAR_RED_HQ         'a'
#define CHAR_RED_CITY       's'
#define CHAR_RED_BASE       'd'
#define CHAR_RED_AIRPORT    'f'
#define CHAR_RED_PORT       'g'
#define CHAR_BLUE_HQ        'z'
#define CHAR_BLUE_CITY      'x'
#define CHAR_BLUE_BASE      'c'
#define CHAR_BLUE_AIRPORT   'v'
#define CHAR_BLUE_PORT      'b'
#define CHAR_GREEN_HQ       'A'
#define CHAR_GREEN_CITY     'S'
#define CHAR_GREEN_BASE     'D'
#define CHAR_GREEN_AIRPORT  'F'
#define CHAR_GREEN_PORT     'G'
#define CHAR_YELLOW_HQ      'Z'
#define CHAR_YELLOW_CITY    'X'
#define CHAR_YELLOW_BASE    'C'
#define CHAR_YELLOW_AIRPORT 'V'
#define CHAR_YELLOW_PORT    'B'
#define CHAR_PLAIN          '1'
#define CHAR_ROAD           '2'
#define CHAR_SEA            '3'
#define CHAR_RIVER          '4'
#define CHAR_WOOD           '5'
#define CHAR_MOUNTAIN       '6'
#define CHAR_BRIDGE         '7'
#define CHAR_SHOAL          '8'
#define CHAR_REEF           '9'

/// The maximum amounts stored
// THIS WILL BE TWEAKED
#define MAX_UNITS 100
#define MAX_BUILDINGS 100

/// Some game-specific numbers
#define STARTING_MONEY 7000
#define MONEY_PER_BUILDING 1000

/// Error messages
#define ERROR_CODE data->errorCode
#define ALL_GOOD 0
#define TEST_FAILED 1
#define BAD_SETUP_INPUT 2
#define FILE_NOT_FOUND 3
#define MAP_INVALID_SIZE 4

// This is just for reference for knowing what the units do.
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