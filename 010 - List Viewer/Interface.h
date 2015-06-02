/**
 *  \file Interface.h
 *  \brief This file declares all the functions that are used by
 *  Interface.c.
 */

typedef struct _internaldata * Data;

/// This stores some basic data that the program uses.
typedef struct _internaldata {
	/// This stores the height of the console window.
	int consoleHeight;
	/// This stores the width of the console window.
	int consoleWidth;
	/// This stores what item is being selected.
	int cursorPos;
	/// This stores the left-most letter of the item being shown.
	int cursorWidth;
	/// This stores the top-most item being shown.
	int topItem;
	/// This stores what mode the program is currently in.
	int mode;
	/// This stores the top selected item.
	int selectedTopItem;
	/// This stores the bottom selected item (used for ranges later).
	int selectedBottomItem;
	/// This stores what is selected in the menu.
	int menuItem;
} data;

/// Program modes
#define MODE_VIEW      1
#define MODE_VIEW_MENU 2
#define MODE_MOVE      3
#define MODE_MOVE_MENU 4
#define MODE_ADD       5
#define MODE_EDIT      6
#define MODE_EXIT      20

/// Error codes
#define ERROR_DELETED_PAST_SIZE 1
#define ERROR_DELETED_ITEM_FROM_NULL_LIST 2
#define ERROR_ADDED_PAST_SIZE 3
#define ERROR_UNIMPLEMENTED 4
#define ERROR_EDITED_PAST_SIZE 5

void reportError(int errorCode);
Data startProgram();
void quitProgram(Data d, List l);
void printList(Data d, List l);
void printFooter(Data d, List l);
void printViewMenu(Data d, List l);
void editItemScreen(Data d, List l);
void showList(Data d, List l);
void computeInput(Data d, List l);
void updateConsoleData(Data d);
void scrollScreenUp(Data d, List l);
void scrollScreenDown(Data d, List l);
void jumpScreenUp(Data d, List l);
void jumpScreenDown(Data d, List l);