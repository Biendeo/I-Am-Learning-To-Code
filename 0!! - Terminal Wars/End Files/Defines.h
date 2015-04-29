#ifndef DEFINES_H
#define DEFINES_H

/// End-user defines
#define START_GAME game *data = buildGame ()
#define END_GAME freeGame(data)

#define YES 1
#define NO  0

#define HUMAN 1
#define BOT   2

#define UP    1
#define RIGHT 2
#define DOWN  3
#define LEFT  4

#define PRIMARY  1
#define SECONARY 2

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
#define MISSILES  12
#define BATT_COP  13
#define TRAN_COP  14 // SKIP FOR NOW
#define FIGHTER   15
#define BOMBER    16
#define STEALTH   17
#define LANDER    18 // SKIP FOR NOW
#define CRUISER   19
#define SUB       20
#define BATT_SHIP 21
#define CARRIER   22 // SKIP FOR NOW

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
#define CHAR_MISSILES  'L'
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
// THIS IS INCOMPLETE (ALL PLACEHOLDER VALUES)
// Setting a value to 0 will mean a unit cannot move onto it.
#define MOVE_HQ_INFANTRY 1
#define MOVE_HQ_MECH     1
#define MOVE_HQ_TIRES    1
#define MOVE_HQ_TREAD    1
#define MOVE_HQ_AIR      1
#define MOVE_HQ_SHIP     0
#define MOVE_HQ_CARRIER  0

#define MOVE_CITY_INFANTRY 1
#define MOVE_CITY_MECH     1
#define MOVE_CITY_TIRES    1
#define MOVE_CITY_TREAD    1
#define MOVE_CITY_AIR      1
#define MOVE_CITY_SHIP     0
#define MOVE_CITY_CARRIER  0

#define MOVE_BASE_INFANTRY 1
#define MOVE_BASE_MECH     1
#define MOVE_BASE_TIRES    1
#define MOVE_BASE_TREAD    1
#define MOVE_BASE_AIR      1
#define MOVE_BASE_SHIP     0
#define MOVE_BASE_CARRIER  0

#define MOVE_AIRPORT_INFANTRY 1
#define MOVE_AIRPORT_MECH     1
#define MOVE_AIRPORT_TIRES    1
#define MOVE_AIRPORT_TREAD    1
#define MOVE_AIRPORT_AIR      1
#define MOVE_AIRPORT_SHIP     0
#define MOVE_AIRPORT_CARRIER  0

#define MOVE_PORT_INFANTRY 1
#define MOVE_PORT_MECH     1
#define MOVE_PORT_TIRES    1
#define MOVE_PORT_TREAD    1
#define MOVE_PORT_AIR      1
#define MOVE_PORT_SHIP     0
#define MOVE_PORT_CARRIER  0

#define MOVE_PLAIN_INFANTRY 1
#define MOVE_PLAIN_MECH     1
#define MOVE_PLAIN_TIRES    2
#define MOVE_PLAIN_TREAD    1
#define MOVE_PLAIN_AIR      1
#define MOVE_PLAIN_SHIP     0
#define MOVE_PLAIN_CARRIER  0

#define MOVE_ROAD_INFANTRY 1
#define MOVE_ROAD_MECH     1
#define MOVE_ROAD_TIRES    1
#define MOVE_ROAD_TREAD    1
#define MOVE_ROAD_AIR      1
#define MOVE_ROAD_SHIP     0
#define MOVE_ROAD_CARRIER  0

#define MOVE_SEA_INFANTRY 1
#define MOVE_SEA_MECH     1
#define MOVE_SEA_TIRES    1
#define MOVE_SEA_TREAD    1
#define MOVE_SEA_AIR      1
#define MOVE_SEA_SHIP     0
#define MOVE_SEA_CARRIER  0

#define MOVE_RIVER_INFANTRY 1
#define MOVE_RIVER_MECH     1
#define MOVE_RIVER_TIRES    1
#define MOVE_RIVER_TREAD    1
#define MOVE_RIVER_AIR      1
#define MOVE_RIVER_SHIP     0
#define MOVE_RIVER_CARRIER  0

#define MOVE_WOOD_INFANTRY 1
#define MOVE_WOOD_MECH     1
#define MOVE_WOOD_TIRES    1
#define MOVE_WOOD_TREAD    1
#define MOVE_WOOD_AIR      1
#define MOVE_WOOD_SHIP     0
#define MOVE_WOOD_CARRIER  0

#define MOVE_MOUNTAIN_INFANTRY 1
#define MOVE_MOUNTAIN_MECH     1
#define MOVE_MOUNTAIN_TIRES    1
#define MOVE_MOUNTAIN_TREAD    1
#define MOVE_MOUNTAIN_AIR      1
#define MOVE_MOUNTAIN_SHIP     0
#define MOVE_MOUNTAIN_CARRIER  0

#define MOVE_BRIDGE_INFANTRY 1
#define MOVE_BRIDGE_MECH     1
#define MOVE_BRIDGE_TIRES    1
#define MOVE_BRIDGE_TREAD    1
#define MOVE_BRIDGE_AIR      1
#define MOVE_BRIDGE_SHIP     0
#define MOVE_BRIDGE_CARRIER  0

#define MOVE_SHOAL_INFANTRY 1
#define MOVE_SHOAL_MECH     1
#define MOVE_SHOAL_TIRES    1
#define MOVE_SHOAL_TREAD    1
#define MOVE_SHOAL_AIR      1
#define MOVE_SHOAL_SHIP     0
#define MOVE_SHOAL_CARRIER  0

#define MOVE_REEF_INFANTRY 1
#define MOVE_REEF_MECH     1
#define MOVE_REEF_TIRES    1
#define MOVE_REEF_TREAD    1
#define MOVE_REEF_AIR      1
#define MOVE_REEF_SHIP     0
#define MOVE_REEF_CARRIER  0

/// Tile defense ranks
#define DEFENSE_HQ       4
#define DEFENSE_CITY     3
#define DEFENSE_BASE     3
#define DEFENSE_AIRPORT  3
#define DEFENSE_PORT     3
#define DEFENSE_PLAIN    1
#define DEFENSE_ROAD     0
#define DEFENSE_SEA      0
#define DEFENSE_RIVER    0 // UNCONFIRMED
#define DEFENSE_WOOD     2
#define DEFENSE_MOUNTAIN 4
#define DEFENSE_BRIDGE   0 // UNCONFIRMED
#define DEFENSE_SHOAL    0
#define DEFENSE_REEF     1

/// Default unit properties
// I might need to change the style of these.
#define COST_INFANTRY      1000
#define MOVETYPE_INFANTRY  MOVE_INFANTRY
#define MOVESPEED_INFANTRY 3
#define MAXAMMO_INFANTRY_1 -1
#define MAXAMMO_INFANTRY_2 0
#define MAXFUEL_INFANTRY   99
#define VISION_INFANTRY    2
#define RANGE_MIN_INFANTRY 1
#define RANGE_MAX_INFANTRY 1

#define COST_MECH      3000
#define MOVETYPE_MECH  MOVE_MECH
#define MOVESPEED_MECH 2
#define MAXAMMO_MECH_1 3
#define MAXAMMO_MECH_2 -1
#define MAXFUEL_MECH   70
#define VISION_MECH    2
#define RANGE_MIN_MECH 1
#define RANGE_MAX_MECH 1

#define COST_RECON      4000
#define MOVETYPE_RECON  MOVE_TIRES
#define MOVESPEED_RECON 8
#define MAXAMMO_RECON_1 -1
#define MAXAMMO_RECON_2 0
#define MAXFUEL_RECON   80
#define VISION_RECON    5
#define RANGE_MIN_RECON 1
#define RANGE_MAX_RECON 1

#define COST_TANK      7000
#define MOVETYPE_TANK  MOVE_TREAD
#define MOVESPEED_TANK 6
#define MAXAMMO_TANK_1 9
#define MAXAMMO_TANK_2 -1
#define MAXFUEL_TANK   99
#define VISION_TANK    3
#define RANGE_MIN_TANK 1
#define RANGE_MAX_TANK 1

#define COST_MD_TANK      16000
#define MOVETYPE_MD_TANK  MOVE_TREAD
#define MOVESPEED_MD_TANK 5
#define MAXAMMO_MD_TANK_1 8
#define MAXAMMO_MD_TANK_2 -1
#define MAXFUEL_MD_TANK   50
#define VISION_MD_TANK    1
#define RANGE_MIN_MD_TANK 1
#define RANGE_MAX_MD_TANK 1

#define COST_NEOTANK      22000
#define MOVETYPE_NEOTANK  MOVE_TREAD
#define MOVESPEED_NEOTANK 6
#define MAXAMMO_NEOTANK_1 9
#define MAXAMMO_NEOTANK_2 -1
#define MAXFUEL_NEOTANK   99
#define VISION_NEOTANK    1
#define RANGE_MIN_NEOTANK 1
#define RANGE_MAX_NEOTANK 1

#define COST_MEGATANK      28000
#define MOVETYPE_MEGATANK  MOVE_TREAD
#define MOVESPEED_MEGATANK 4
#define MAXAMMO_MEGATANK_1 3
#define MAXAMMO_MEGATANK_2 -1
#define MAXFUEL_MEGATANK   70
#define VISION_MEGATANK    1
#define RANGE_MIN_MEGATANK 1
#define RANGE_MAX_MEGATANK 1

#define COST_APC      5000
#define MOVETYPE_APC  MOVE_TREAD
#define MOVESPEED_APC 6
#define MAXAMMO_APC_1 0
#define MAXAMMO_APC_2 0
#define MAXFUEL_APC   70
#define VISION_APC    1
#define RANGE_MIN_APC 0
#define RANGE_MAX_APC 0

#define COST_ARTILLERY      6000
#define MOVETYPE_ARTILLERY  MOVE_TREAD
#define MOVESPEED_ARTILLERY 5
#define MAXAMMO_ARTILLERY_1 9
#define MAXAMMO_ARTILLERY_2 0
#define MAXFUEL_ARTILLERY   70
#define VISION_ARTILLERY    1
#define RANGE_MIN_ARTILLERY 2
#define RANGE_MAX_ARTILLERY 3

#define COST_ROCKETS      15000
#define MOVETYPE_ROCKETS  MOVE_TIRES
#define MOVESPEED_ROCKETS 5
#define MAXAMMO_ROCKETS_1 9
#define MAXAMMO_ROCKETS_2 0
#define MAXFUEL_ROCKETS   50
#define VISION_ROCKETS    2
#define RANGE_MIN_ROCKETS 3
#define RANGE_MAX_ROCKETS 5

#define COST_ANTI_AIR      8000
#define MOVETYPE_ANTI_AIR  MOVE_TREAD
#define MOVESPEED_ANTI_AIR 6
#define MAXAMMO_ANTI_AIR_1 9
#define MAXAMMO_ANTI_AIR_2 0
#define MAXFUEL_ANTI_AIR   60
#define VISION_ANTI_AIR    2
#define RANGE_MIN_ANTI_AIR 1
#define RANGE_MAX_ANTI_AIR 1

#define COST_MISSILES      12000
#define MOVETYPE_MISSILES  MOVE_TIRES
#define MOVESPEED_MISSILES 4
#define MAXAMMO_MISSILES_1 6
#define MAXAMMO_MISSILES_2 0
#define MAXFUEL_MISSILES   50
#define VISION_MISSILES    5
#define RANGE_MIN_MISSILES 3
#define RANGE_MAX_MISSILES 5

#define COST_BATT_COP      9000
#define MOVETYPE_BATT_COP  MOVE_AIR
#define MOVESPEED_BATT_COP 6
#define MAXAMMO_BATT_COP_1 6
#define MAXAMMO_BATT_COP_2 -1
#define MAXFUEL_BATT_COP   99
#define VISION_BATT_COP    3
#define RANGE_MIN_BATT_COP 1
#define RANGE_MAX_BATT_COP 1

#define COST_TRAN_COP      5000
#define MOVETYPE_TRAN_COP  MOVE_AIR
#define MOVESPEED_TRAN_COP 6
#define MAXAMMO_TRAN_COP_1 0
#define MAXAMMO_TRAN_COP_2 0
#define MAXFUEL_TRAN_COP   99
#define VISION_TRAN_COP    2
#define RANGE_MIN_TRAN_COP 0
#define RANGE_MAX_TRAN_COP 0

#define COST_FIGHTER      20000
#define MOVETYPE_FIGHTER  MOVE_AIR
#define MOVESPEED_FIGHTER 9
#define MAXAMMO_FIGHTER_1 9
#define MAXAMMO_FIGHTER_2 0
#define MAXFUEL_FIGHTER   99
#define VISION_FIGHTER    2
#define RANGE_MIN_FIGHTER 1
#define RANGE_MAX_FIGHTER 1

#define COST_BOMBER      1000
#define MOVETYPE_BOMBER  MOVE_AIR
#define MOVESPEED_BOMBER 7
#define MAXAMMO_BOMBER_1 9
#define MAXAMMO_BOMBER_2 0
#define MAXFUEL_BOMBER   99
#define VISION_BOMBER    2
#define RANGE_MIN_BOMBER 1
#define RANGE_MAX_BOMBER 1

#define COST_STEALTH      24000
#define MOVETYPE_STEALTH  MOVE_AIR
#define MOVESPEED_STEALTH 6
#define MAXAMMO_STEALTH_1 6
#define MAXAMMO_STEALTH_2 0
#define MAXFUEL_STEALTH   60
#define VISION_STEALTH    4
#define RANGE_MIN_STEALTH 1
#define RANGE_MAX_STEALTH 1

#define COST_LANDER      12000
#define MOVETYPE_LANDER  MOVE_CARRIER
#define MOVESPEED_LANDER 6
#define MAXAMMO_LANDER_1 0
#define MAXAMMO_LANDER_2 0
#define MAXFUEL_LANDER   99
#define VISION_LANDER    1
#define RANGE_MIN_LANDER 0
#define RANGE_MAX_LANDER 0

#define COST_CRUISER      18000
#define MOVETYPE_CRUISER  MOVE_SHIP
#define MOVESPEED_CRUISER 6
#define MAXAMMO_CRUISER_1 9
#define MAXAMMO_CRUISER_2 -1 // I THINK THIS IS DIFFERENT
#define MAXFUEL_CRUISER   99
#define VISION_CRUISER    3
#define RANGE_MIN_CRUISER 1
#define RANGE_MAX_CRUISER 1

#define COST_SUB      1000
#define MOVETYPE_SUB  MOVE_SHIP
#define MOVESPEED_SUB 5
#define MAXAMMO_SUB_1 6
#define MAXAMMO_SUB_2 0
#define MAXFUEL_SUB   60
#define VISION_SUB    5
#define RANGE_MIN_SUB 1
#define RANGE_MAX_SUB 1

#define COST_BATT_SHIP      28000
#define MOVETYPE_BATT_SHIP  MOVE_SHIP
#define MOVESPEED_BATT_SHIP 5
#define MAXAMMO_BATT_SHIP_1 9
#define MAXAMMO_BATT_SHIP_2 0
#define MAXFUEL_BATT_SHIP   99
#define VISION_BATT_SHIP    2
#define RANGE_MIN_BATT_SHIP 2
#define RANGE_MAX_BATT_SHIP 6

#define COST_CARRIER      30000
#define MOVETYPE_CARRIER  MOVE_SHIP
#define MOVESPEED_CARRIER 5
#define MAXAMMO_CARRIER_1 9
#define MAXAMMO_CARRIER_2 0
#define MAXFUEL_CARRIER   99
#define VISION_CARRIER    4
#define RANGE_MIN_CARRIER 3
#define RANGE_MAX_CARRIER 8


/// Base damage values (percentages)
// Use the style DAMAGE_ATTACKER_DEFENDER
// The APC, TRAN_COP, and LANDER don't attack, so they're not on this list.
// I NEED TO ADD VALUES FOR SECONDARY WEAPONS ON MOST THINGS
#define DAMAGE_INFANTRY_INFANTRY  55
#define DAMAGE_INFANTRY_MECH      45
#define DAMAGE_INFANTRY_RECON     12
#define DAMAGE_INFANTRY_TANK       5
#define DAMAGE_INFANTRY_MD_TANK    1
#define DAMAGE_INFANTRY_NEOTANK    1
#define DAMAGE_INFANTRY_MEGATANK   1
#define DAMAGE_INFANTRY_APC       14
#define DAMAGE_INFANTRY_ARTILLERY 15
#define DAMAGE_INFANTRY_ROCKETS   25
#define DAMAGE_INFANTRY_ANTI_AIR   5
#define DAMAGE_INFANTRY_MISSILES  26
#define DAMAGE_INFANTRY_BATT_COP   7
#define DAMAGE_INFANTRY_TRAN_COP  30
#define DAMAGE_INFANTRY_FIGHTER    0
#define DAMAGE_INFANTRY_BOMBER     0
#define DAMAGE_INFANTRY_STEALTH    0
#define DAMAGE_INFANTRY_LANDER     0
#define DAMAGE_INFANTRY_CRUISER    0
#define DAMAGE_INFANTRY_SUB        0
#define DAMAGE_INFANTRY_BATT_SHIP  0
#define DAMAGE_INFANTRY_CARRIER    0

// ADD SECONDARY WEAPON
#define DAMAGE_MECH_INFANTRY  65
#define DAMAGE_MECH_MECH      55
#define DAMAGE_MECH_RECON     85
#define DAMAGE_MECH_TANK      55
#define DAMAGE_MECH_MD_TANK   15
#define DAMAGE_MECH_NEOTANK   15
#define DAMAGE_MECH_MEGATANK   5
#define DAMAGE_MECH_APC       75
#define DAMAGE_MECH_ARTILLERY 70
#define DAMAGE_MECH_ROCKETS   85
#define DAMAGE_MECH_ANTI_AIR  65
#define DAMAGE_MECH_MISSILES  85
#define DAMAGE_MECH_BATT_COP   9
#define DAMAGE_MECH_TRAN_COP  35
#define DAMAGE_MECH_FIGHTER    0
#define DAMAGE_MECH_BOMBER     0
#define DAMAGE_MECH_STEALTH    0
#define DAMAGE_MECH_LANDER     0
#define DAMAGE_MECH_CRUISER    0
#define DAMAGE_MECH_SUB        0
#define DAMAGE_MECH_BATT_SHIP  0
#define DAMAGE_MECH_CARRIER    0

#define DAMAGE_RECON_INFANTRY  70
#define DAMAGE_RECON_MECH      65
#define DAMAGE_RECON_RECON     35
#define DAMAGE_RECON_TANK       6
#define DAMAGE_RECON_MD_TANK    1
#define DAMAGE_RECON_NEOTANK    1
#define DAMAGE_RECON_MEGATANK   1
#define DAMAGE_RECON_APC       45
#define DAMAGE_RECON_ARTILLERY 45
#define DAMAGE_RECON_ROCKETS   55
#define DAMAGE_RECON_ANTI_AIR   4
#define DAMAGE_RECON_MISSILES  28
#define DAMAGE_RECON_BATT_COP  10
#define DAMAGE_RECON_TRAN_COP  35
#define DAMAGE_RECON_FIGHTER    0
#define DAMAGE_RECON_BOMBER     0
#define DAMAGE_RECON_STEALTH    0
#define DAMAGE_RECON_LANDER     0
#define DAMAGE_RECON_CRUISER    0
#define DAMAGE_RECON_SUB        0
#define DAMAGE_RECON_BATT_SHIP  0
#define DAMAGE_RECON_CARRIER    0

// ADD SECONDARY WEAPON
#define DAMAGE_TANK_INFANTRY  75
#define DAMAGE_TANK_MECH      70
#define DAMAGE_TANK_RECON     85
#define DAMAGE_TANK_TANK      55
#define DAMAGE_TANK_MD_TANK   15
#define DAMAGE_TANK_NEOTANK   15
#define DAMAGE_TANK_MEGATANK  10
#define DAMAGE_TANK_APC       75
#define DAMAGE_TANK_ARTILLERY 70
#define DAMAGE_TANK_ROCKETS   85
#define DAMAGE_TANK_ANTI_AIR  65
#define DAMAGE_TANK_MISSILES  85
#define DAMAGE_TANK_BATT_COP  10
#define DAMAGE_TANK_TRAN_COP  40
#define DAMAGE_TANK_FIGHTER    0
#define DAMAGE_TANK_BOMBER     0
#define DAMAGE_TANK_STEALTH    0
#define DAMAGE_TANK_LANDER    10
#define DAMAGE_TANK_CRUISER    5
#define DAMAGE_TANK_SUB        1
#define DAMAGE_TANK_BATT_SHIP  1
#define DAMAGE_TANK_CARRIER    1

// ADD SECONDARY WEAPON
#define DAMAGE_MD_TANK_INFANTRY  105
#define DAMAGE_MD_TANK_MECH       95
#define DAMAGE_MD_TANK_RECON     105
#define DAMAGE_MD_TANK_TANK       85
#define DAMAGE_MD_TANK_MD_TANK    55
#define DAMAGE_MD_TANK_NEOTANK    45
#define DAMAGE_MD_TANK_MEGATANK   25
#define DAMAGE_MD_TANK_APC       105
#define DAMAGE_MD_TANK_ARTILLERY 105
#define DAMAGE_MD_TANK_ROCKETS   105
#define DAMAGE_MD_TANK_ANTI_AIR  105
#define DAMAGE_MD_TANK_MISSILES  105
#define DAMAGE_MD_TANK_BATT_COP   12
#define DAMAGE_MD_TANK_TRAN_COP   45
#define DAMAGE_MD_TANK_FIGHTER     0
#define DAMAGE_MD_TANK_BOMBER      0
#define DAMAGE_MD_TANK_STEALTH     0
#define DAMAGE_MD_TANK_LANDER     35
#define DAMAGE_MD_TANK_CRUISER    30
#define DAMAGE_MD_TANK_SUB        10
#define DAMAGE_MD_TANK_BATT_SHIP  10
#define DAMAGE_MD_TANK_CARRIER    35

// ADD SECONDARY WEAPON
#define DAMAGE_NEOTANK_INFANTRY  125
#define DAMAGE_NEOTANK_MECH      115
#define DAMAGE_NEOTANK_RECON     125
#define DAMAGE_NEOTANK_TANK      105
#define DAMAGE_NEOTANK_MD_TANK    75
#define DAMAGE_NEOTANK_NEOTANK    55
#define DAMAGE_NEOTANK_MEGATANK   35
#define DAMAGE_NEOTANK_APC       125
#define DAMAGE_NEOTANK_ARTILLERY 115
#define DAMAGE_NEOTANK_ROCKETS   125
#define DAMAGE_NEOTANK_ANTI_AIR  115
#define DAMAGE_NEOTANK_MISSILES  125
#define DAMAGE_NEOTANK_BATT_COP   22
#define DAMAGE_NEOTANK_TRAN_COP   55
#define DAMAGE_NEOTANK_FIGHTER     0
#define DAMAGE_NEOTANK_BOMBER      0
#define DAMAGE_NEOTANK_STEALTH     0
#define DAMAGE_NEOTANK_LANDER     40
#define DAMAGE_NEOTANK_CRUISER    30
#define DAMAGE_NEOTANK_SUB        15
#define DAMAGE_NEOTANK_BATT_SHIP  15
#define DAMAGE_NEOTANK_CARRIER    15

// ADD SECONDARY WEAPON
#define DAMAGE_MEGATANK_INFANTRY  135
#define DAMAGE_MEGATANK_MECH      125
#define DAMAGE_MEGATANK_RECON     185
#define DAMAGE_MEGATANK_TANK      180
#define DAMAGE_MEGATANK_MD_TANK   125
#define DAMAGE_MEGATANK_NEOTANK   115
#define DAMAGE_MEGATANK_MEGATANK   65
#define DAMAGE_MEGATANK_APC       195
#define DAMAGE_MEGATANK_ARTILLERY 195
#define DAMAGE_MEGATANK_ROCKETS   195
#define DAMAGE_MEGATANK_ANTI_AIR  195
#define DAMAGE_MEGATANK_MISSILES  195
#define DAMAGE_MEGATANK_BATT_COP   22
#define DAMAGE_MEGATANK_TRAN_COP   55
#define DAMAGE_MEGATANK_FIGHTER     0
#define DAMAGE_MEGATANK_BOMBER      0
#define DAMAGE_MEGATANK_STEALTH     0
#define DAMAGE_MEGATANK_LANDER     75
#define DAMAGE_MEGATANK_CRUISER    65
#define DAMAGE_MEGATANK_SUB        45
#define DAMAGE_MEGATANK_BATT_SHIP  45
#define DAMAGE_MEGATANK_CARRIER    45

#define DAMAGE_ARTILLERY_INFANTRY  90
#define DAMAGE_ARTILLERY_MECH      85
#define DAMAGE_ARTILLERY_RECON     80
#define DAMAGE_ARTILLERY_TANK      70
#define DAMAGE_ARTILLERY_MD_TANK   45
#define DAMAGE_ARTILLERY_NEOTANK   40
#define DAMAGE_ARTILLERY_MEGATANK  15
#define DAMAGE_ARTILLERY_APC       70
#define DAMAGE_ARTILLERY_ARTILLERY 75
#define DAMAGE_ARTILLERY_ROCKETS   80
#define DAMAGE_ARTILLERY_ANTI_AIR  75
#define DAMAGE_ARTILLERY_MISSILES  80
#define DAMAGE_ARTILLERY_BATT_COP   0
#define DAMAGE_ARTILLERY_TRAN_COP   0
#define DAMAGE_ARTILLERY_FIGHTER    0
#define DAMAGE_ARTILLERY_BOMBER     0
#define DAMAGE_ARTILLERY_STEALTH    0
#define DAMAGE_ARTILLERY_LANDER    55
#define DAMAGE_ARTILLERY_CRUISER   50
#define DAMAGE_ARTILLERY_SUB       60
#define DAMAGE_ARTILLERY_BATT_SHIP 40
#define DAMAGE_ARTILLERY_CARRIER   45

#define DAMAGE_ROCKETS_INFANTRY  95
#define DAMAGE_ROCKETS_MECH      90
#define DAMAGE_ROCKETS_RECON     90
#define DAMAGE_ROCKETS_TANK      85
#define DAMAGE_ROCKETS_MD_TANK   55
#define DAMAGE_ROCKETS_NEOTANK   50
#define DAMAGE_ROCKETS_MEGATANK  25
#define DAMAGE_ROCKETS_APC       80
#define DAMAGE_ROCKETS_ARTILLERY 80
#define DAMAGE_ROCKETS_ROCKETS   85
#define DAMAGE_ROCKETS_ANTI_AIR  85
#define DAMAGE_ROCKETS_MISSILES  90
#define DAMAGE_ROCKETS_BATT_COP   0
#define DAMAGE_ROCKETS_TRAN_COP   0
#define DAMAGE_ROCKETS_FIGHTER    0
#define DAMAGE_ROCKETS_BOMBER     0
#define DAMAGE_ROCKETS_STEALTH    0
#define DAMAGE_ROCKETS_LANDER    60
#define DAMAGE_ROCKETS_CRUISER   60
#define DAMAGE_ROCKETS_SUB       85
#define DAMAGE_ROCKETS_BATT_SHIP 55
#define DAMAGE_ROCKETS_CARRIER   60

#define DAMAGE_ANTI_AIR_INFANTRY  105
#define DAMAGE_ANTI_AIR_MECH      105
#define DAMAGE_ANTI_AIR_RECON      60
#define DAMAGE_ANTI_AIR_TANK       25
#define DAMAGE_ANTI_AIR_MD_TANK    10
#define DAMAGE_ANTI_AIR_NEOTANK     5
#define DAMAGE_ANTI_AIR_MEGATANK    1
#define DAMAGE_ANTI_AIR_APC        50
#define DAMAGE_ANTI_AIR_ARTILLERY  50
#define DAMAGE_ANTI_AIR_ROCKETS    45
#define DAMAGE_ANTI_AIR_ANTI_AIR   45
#define DAMAGE_ANTI_AIR_MISSILES   55
#define DAMAGE_ANTI_AIR_BATT_COP  105
#define DAMAGE_ANTI_AIR_TRAN_COP  105
#define DAMAGE_ANTI_AIR_FIGHTER    65
#define DAMAGE_ANTI_AIR_BOMBER     75
#define DAMAGE_ANTI_AIR_STEALTH    75
#define DAMAGE_ANTI_AIR_LANDER    120
#define DAMAGE_ANTI_AIR_CRUISER     0
#define DAMAGE_ANTI_AIR_SUB         0
#define DAMAGE_ANTI_AIR_BATT_SHIP   0
#define DAMAGE_ANTI_AIR_CARRIER     0

#define DAMAGE_MISSILES_INFANTRY    0
#define DAMAGE_MISSILES_MECH        0
#define DAMAGE_MISSILES_RECON       0
#define DAMAGE_MISSILES_TANK        0
#define DAMAGE_MISSILES_MD_TANK     0
#define DAMAGE_MISSILES_NEOTANK     0
#define DAMAGE_MISSILES_MEGATANK    0
#define DAMAGE_MISSILES_APC         0
#define DAMAGE_MISSILES_ARTILLERY   0
#define DAMAGE_MISSILES_ROCKETS     0
#define DAMAGE_MISSILES_ANTI_AIR    0
#define DAMAGE_MISSILES_MISSILES    0
#define DAMAGE_MISSILES_BATT_COP  120
#define DAMAGE_MISSILES_TRAN_COP  120
#define DAMAGE_MISSILES_FIGHTER   100
#define DAMAGE_MISSILES_BOMBER    100
#define DAMAGE_MISSILES_STEALTH   100
#define DAMAGE_MISSILES_LANDER    120
#define DAMAGE_MISSILES_CRUISER     0
#define DAMAGE_MISSILES_SUB         0
#define DAMAGE_MISSILES_BATT_SHIP   0
#define DAMAGE_MISSILES_CARRIER     0

#define DAMAGE_BATT_COP_INFANTRY  75
#define DAMAGE_BATT_COP_MECH      75
#define DAMAGE_BATT_COP_RECON     55
#define DAMAGE_BATT_COP_TANK      55
#define DAMAGE_BATT_COP_MD_TANK   25
#define DAMAGE_BATT_COP_NEOTANK   20
#define DAMAGE_BATT_COP_MEGATANK  10
#define DAMAGE_BATT_COP_APC       60
#define DAMAGE_BATT_COP_ARTILLERY 65
#define DAMAGE_BATT_COP_ROCKETS   65
#define DAMAGE_BATT_COP_ANTI_AIR  25
#define DAMAGE_BATT_COP_MISSILES  65
#define DAMAGE_BATT_COP_BATT_COP  65
#define DAMAGE_BATT_COP_TRAN_COP  95
#define DAMAGE_BATT_COP_FIGHTER    0
#define DAMAGE_BATT_COP_BOMBER     0
#define DAMAGE_BATT_COP_STEALTH    0
#define DAMAGE_BATT_COP_LANDER    25
#define DAMAGE_BATT_COP_CRUISER   25
#define DAMAGE_BATT_COP_SUB       25
#define DAMAGE_BATT_COP_BATT_SHIP 25
#define DAMAGE_BATT_COP_CARRIER   25

#define DAMAGE_FIGHTER_INFANTRY    0
#define DAMAGE_FIGHTER_MECH        0
#define DAMAGE_FIGHTER_RECON       0
#define DAMAGE_FIGHTER_TANK        0
#define DAMAGE_FIGHTER_MD_TANK     0
#define DAMAGE_FIGHTER_NEOTANK     0
#define DAMAGE_FIGHTER_MEGATANK    0
#define DAMAGE_FIGHTER_APC         0
#define DAMAGE_FIGHTER_ARTILLERY   0
#define DAMAGE_FIGHTER_ROCKETS     0
#define DAMAGE_FIGHTER_ANTI_AIR    0
#define DAMAGE_FIGHTER_MISSILES    0
#define DAMAGE_FIGHTER_BATT_COP  100
#define DAMAGE_FIGHTER_TRAN_COP  100
#define DAMAGE_FIGHTER_FIGHTER    55
#define DAMAGE_FIGHTER_BOMBER    100
#define DAMAGE_FIGHTER_STEALTH    85
#define DAMAGE_FIGHTER_LANDER      0
#define DAMAGE_FIGHTER_CRUISER     0
#define DAMAGE_FIGHTER_SUB         0
#define DAMAGE_FIGHTER_BATT_SHIP   0
#define DAMAGE_FIGHTER_CARRIER     0

#define DAMAGE_BOMBER_INFANTRY  110
#define DAMAGE_BOMBER_MECH      110
#define DAMAGE_BOMBER_RECON     105
#define DAMAGE_BOMBER_TANK      105
#define DAMAGE_BOMBER_MD_TANK    95
#define DAMAGE_BOMBER_NEOTANK    90
#define DAMAGE_BOMBER_MEGATANK   35
#define DAMAGE_BOMBER_APC       105
#define DAMAGE_BOMBER_ARTILLERY 105
#define DAMAGE_BOMBER_ROCKETS   105
#define DAMAGE_BOMBER_ANTI_AIR   95
#define DAMAGE_BOMBER_MISSILES  105
#define DAMAGE_BOMBER_BATT_COP    0
#define DAMAGE_BOMBER_TRAN_COP    0
#define DAMAGE_BOMBER_FIGHTER     0
#define DAMAGE_BOMBER_BOMBER      0
#define DAMAGE_BOMBER_STEALTH     0
#define DAMAGE_BOMBER_LANDER     95
#define DAMAGE_BOMBER_CRUISER    50
#define DAMAGE_BOMBER_SUB        95
#define DAMAGE_BOMBER_BATT_SHIP  75
#define DAMAGE_BOMBER_CARRIER    75

#define DAMAGE_STEALTH_INFANTRY  90
#define DAMAGE_STEALTH_MECH      90
#define DAMAGE_STEALTH_RECON     85
#define DAMAGE_STEALTH_TANK      75
#define DAMAGE_STEALTH_MD_TANK   70
#define DAMAGE_STEALTH_NEOTANK   60
#define DAMAGE_STEALTH_MEGATANK  15
#define DAMAGE_STEALTH_APC       85
#define DAMAGE_STEALTH_ARTILLERY 75
#define DAMAGE_STEALTH_ROCKETS   85
#define DAMAGE_STEALTH_ANTI_AIR  50
#define DAMAGE_STEALTH_MISSILES  85
#define DAMAGE_STEALTH_BATT_COP  85
#define DAMAGE_STEALTH_TRAN_COP  95
#define DAMAGE_STEALTH_FIGHTER   45
#define DAMAGE_STEALTH_BOMBER    70
#define DAMAGE_STEALTH_STEALTH   55
#define DAMAGE_STEALTH_LANDER    65
#define DAMAGE_STEALTH_CRUISER   35
#define DAMAGE_STEALTH_SUB       55
#define DAMAGE_STEALTH_BATT_SHIP 45
#define DAMAGE_STEALTH_CARRIER   45

#define DAMAGE_CRUISER_INFANTRY    0
#define DAMAGE_CRUISER_MECH        0
#define DAMAGE_CRUISER_RECON       0
#define DAMAGE_CRUISER_TANK        0
#define DAMAGE_CRUISER_MD_TANK     0
#define DAMAGE_CRUISER_NEOTANK     0
#define DAMAGE_CRUISER_MEGATANK    0
#define DAMAGE_CRUISER_APC         0
#define DAMAGE_CRUISER_ARTILLERY   0
#define DAMAGE_CRUISER_ROCKETS     0
#define DAMAGE_CRUISER_ANTI_AIR    0
#define DAMAGE_CRUISER_MISSILES    0
#define DAMAGE_CRUISER_BATT_COP  105
#define DAMAGE_CRUISER_TRAN_COP  105
#define DAMAGE_CRUISER_FIGHTER    85
#define DAMAGE_CRUISER_BOMBER    100
#define DAMAGE_CRUISER_STEALTH   100
#define DAMAGE_CRUISER_LANDER     25
#define DAMAGE_CRUISER_CRUISER    25
#define DAMAGE_CRUISER_SUB        90
#define DAMAGE_CRUISER_BATT_SHIP   5
#define DAMAGE_CRUISER_CARRIER     5

#define DAMAGE_SUB_INFANTRY   0
#define DAMAGE_SUB_MECH       0
#define DAMAGE_SUB_RECON      0
#define DAMAGE_SUB_TANK       0
#define DAMAGE_SUB_MD_TANK    0
#define DAMAGE_SUB_NEOTANK    0
#define DAMAGE_SUB_MEGATANK   0
#define DAMAGE_SUB_APC        0
#define DAMAGE_SUB_ARTILLERY  0
#define DAMAGE_SUB_ROCKETS    0
#define DAMAGE_SUB_ANTI_AIR   0
#define DAMAGE_SUB_MISSILES   0
#define DAMAGE_SUB_BATT_COP   0
#define DAMAGE_SUB_TRAN_COP   0
#define DAMAGE_SUB_FIGHTER    0
#define DAMAGE_SUB_BOMBER     0
#define DAMAGE_SUB_STEALTH    0
#define DAMAGE_SUB_LANDER    95
#define DAMAGE_SUB_CRUISER   25
#define DAMAGE_SUB_SUB       55
#define DAMAGE_SUB_BATT_SHIP 65
#define DAMAGE_SUB_CARRIER   75

#define DAMAGE_BATT_SHIP_INFANTRY  95
#define DAMAGE_BATT_SHIP_MECH      90
#define DAMAGE_BATT_SHIP_RECON     90
#define DAMAGE_BATT_SHIP_TANK      85
#define DAMAGE_BATT_SHIP_MD_TANK   55
#define DAMAGE_BATT_SHIP_NEOTANK   50
#define DAMAGE_BATT_SHIP_MEGATANK  25
#define DAMAGE_BATT_SHIP_APC       80
#define DAMAGE_BATT_SHIP_ARTILLERY 80
#define DAMAGE_BATT_SHIP_ROCKETS   85
#define DAMAGE_BATT_SHIP_ANTI_AIR  85
#define DAMAGE_BATT_SHIP_MISSILES  90
#define DAMAGE_BATT_SHIP_BATT_COP   0
#define DAMAGE_BATT_SHIP_TRAN_COP   0
#define DAMAGE_BATT_SHIP_FIGHTER    0
#define DAMAGE_BATT_SHIP_BOMBER     0
#define DAMAGE_BATT_SHIP_STEALTH    0
#define DAMAGE_BATT_SHIP_LANDER    95
#define DAMAGE_BATT_SHIP_CRUISER   95
#define DAMAGE_BATT_SHIP_SUB       95
#define DAMAGE_BATT_SHIP_BATT_SHIP 50
#define DAMAGE_BATT_SHIP_CARRIER   60

#define DAMAGE_CARRIER_INFANTRY    0
#define DAMAGE_CARRIER_MECH        0
#define DAMAGE_CARRIER_RECON       0
#define DAMAGE_CARRIER_TANK        0
#define DAMAGE_CARRIER_MD_TANK     0
#define DAMAGE_CARRIER_NEOTANK     0
#define DAMAGE_CARRIER_MEGATANK    0
#define DAMAGE_CARRIER_APC         0
#define DAMAGE_CARRIER_ARTILLERY   0
#define DAMAGE_CARRIER_ROCKETS     0
#define DAMAGE_CARRIER_ANTI_AIR    0
#define DAMAGE_CARRIER_MISSILES    0
#define DAMAGE_CARRIER_BATT_COP  115
#define DAMAGE_CARRIER_TRAN_COP  115
#define DAMAGE_CARRIER_FIGHTER   100
#define DAMAGE_CARRIER_BOMBER    100
#define DAMAGE_CARRIER_STEALTH   100
#define DAMAGE_CARRIER_LANDER      0
#define DAMAGE_CARRIER_CRUISER     0
#define DAMAGE_CARRIER_SUB         0
#define DAMAGE_CARRIER_BATT_SHIP   0
#define DAMAGE_CARRIER_CARRIER     0

/// Map boundaries
// These are going to be phased out. The map data will be read to
// include the size (or maybe a dynamic system to find it).
#define MAP_WIDTH  16
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
#define CHAR_MAP_PLAIN          '-'
#define CHAR_MAP_ROAD           '+'
#define CHAR_MAP_SEA            '~'
#define CHAR_MAP_RIVER          '-'
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
#define MAX_UNITTYPES 23

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

#endif