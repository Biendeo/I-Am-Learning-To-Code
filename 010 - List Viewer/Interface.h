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
} data;

/// Error codes
#define ERROR_DELETED_PAST_SIZE 1
#define ERROR_DELETED_ITEM_FROM_NULL_LIST 2
#define ERROR_ADDED_PAST_SIZE 3

void reportError(int errorCode);
Data startProgram();
void quitProgram(Data d, List l);
void printList(Data d, List l);