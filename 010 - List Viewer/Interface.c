/**
 *  \file Interface.c
 *  \brief This file defines the main functions that the user will
 *  interact with.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "rlutil.h"
#include "ListFunctions.h"
#include "Interface.h"
#include "FileIO.h"

int main(int argc, char *argv[]) {
	Data d = startProgram();
	
	// For now, the program will just do some default operations.
	List l = createList();
	addItem(l, "The Linked List Viewer!", 1);
	addItem(l, "\"It displays linked lists and lets you directly modify them!\"", 2);
	addItem(l, "-----------------------------", 3);
	
	addItem(l, "The max length of an item in this list is 256 characters. That's a lot, it's like a couple of sentences. Still it's not forever, so you need to cut it off at some point.", 4);
	addItem(l, "You can scroll LEFT and RIGHT too on things that are too long to fit on one screen, which is handy.", 4);
	addItem(l, "You can also scroll UP and DOWN.", 6);
	addItem(l, "PAGE UP and PAGE DOWN work to scroll through larger lists.", 7);
	addItem(l, "Here's a bit of dummy items to test that.", 8);
	
	while (l->size < 50) {
		addItem(l, "DUMMY TEXT", l->size + 1);
	}
	
	addItem(l, "You can press SPACE to enter the menu, and accept options.", 51);
	addItem(l, "Finally, ESCAPE exits the program.", 52);
	
	while (d->mode != MODE_EXIT) {
		updateConsoleData(d);
		printList(d, l);
		if (d->mode == MODE_VIEW_MENU) {
			printViewMenu(d, l);
		} else if (d->mode == MODE_EDIT) {
			editItemScreen(d, l);
		} else if (d->mode == MODE_ADD_MENU) {
			printAddMenu(d, l);
		} else if (d->mode == MODE_ADD) {
			addItemScreen(d, l);
		} else if (d->mode == MODE_DELETE_MENU) {
			printDeleteMenu(d, l);
		} else {
			printFooter(d, l);
		}
		
		if (d->mode == MODE_EDIT) {
			d->mode = MODE_VIEW;
		} else if (d->mode == MODE_ADD) {
			d->mode = MODE_VIEW;
		} else if (d->mode == MODE_DELETE) {
			d->mode = MODE_VIEW;
		} else {
			computeInput(d, l);
		}
	}
	
	quitProgram(d, l);
	
	return EXIT_SUCCESS;
}

void reportError(int errorCode) {
	printf("\n");
	if (errorCode == ERROR_DELETED_PAST_SIZE) {
		setColor(LIGHTRED);
		printf("ERROR (%d): ERROR_DELETED_PAST_SIZE\n", ERROR_DELETED_PAST_SIZE);
		setColor(GREY);
		printf("The program tried to delete an item past the size of the list.\n");
		printf("If you're seeing this error, then the program messed up. Blame it on me.\n");
	} else if (errorCode == ERROR_DELETED_ITEM_FROM_NULL_LIST) {
		setColor(LIGHTRED);
		printf("ERROR (%d): ERROR_DELETED_ITEM_FROM_NULL_LIST\n", ERROR_DELETED_ITEM_FROM_NULL_LIST);
		setColor(GREY);
		printf("The program tried to delete an item from an empty list.\n");
		printf("If you're seeing this error, then the program messed up. Blame it on me.\n");
	} else if (errorCode == ERROR_ADDED_PAST_SIZE) {
		setColor(LIGHTRED);
		printf("ERROR (%d): ERROR_ADDED_PAST_SIZE\n", ERROR_ADDED_PAST_SIZE);
		setColor(GREY);
		printf("The program tried to add an item past the size of the list.\n");
		printf("If you're seeing this error, then the program messed up. Blame it on me.\n");
	} else if (errorCode == ERROR_UNIMPLEMENTED) {
		setColor(YELLOW);
		printf("WARNING (%d): ERROR_UNIMPLEMENTED\n", ERROR_UNIMPLEMENTED);
		setColor(GREY);
		printf("The bit you accessed hasn't been written yet.\n");
		printf("Nothing is wrong, just that feature isn't in the program yet.\n");
	} else if (errorCode == ERROR_EDITED_PAST_SIZE) {
		setColor(LIGHTRED);
		printf("ERROR (%d): ERROR_EDITED_PAST_SIZE\n", ERROR_EDITED_PAST_SIZE);
		setColor(GREY);
		printf("The program tried to edit an item past the size of the list.\n");
		printf("If you're seeing this error, then the program messed up. Blame it on me.\n");
	}
	printf("Press ENTER to keep using the program.\n");
	getkey();
}

Data startProgram() {
	Data d = malloc(sizeof(data));
	d->consoleHeight = trows();
	d->consoleWidth = tcols();
	d->cursorPos = 1;
	d->cursorWidth = 0;
	d->topItem = 1;
	d->mode = MODE_VIEW;
	d->selectedTopItem = 0;
	d->selectedBottomItem = 0;
	d->menuItem = 0;
	return d;
}

void quitProgram(Data d, List l) {
	deleteList(l);
	free(d);
}

// THIS FUNCTION NEEDS TO BE REWRITTEN TO BE A BIT MORE LOGICAL.
void printList(Data d, List l) {
	Item currentItem = l->next;
	// Also the variables have bad names.
	int writingPos = d->topItem;
	int currentPos = 1;
	int stringPos = 0;
	
	/// Firstly, we clear the screen.
	cls();
	
	/// This loops until we hit the row just above the bottom of the
	/// screen, or we hit a null item.
	while ((writingPos != (d->topItem + d->consoleHeight - 1)) && (currentItem != NULL)) {
		/// If we've hit the end of the list, we print this message.
		if (currentItem->next == NULL) {
			setColor(DARKGREY);
			printf("Reached the end of the list of %d elements.\n", l->size);
			setColor(GREY);
			break;
		} else {
			currentItem = l->next;
			currentPos = 1;
			/// If the object is highlighted, we'll check to see if the
			/// user has scrolled to see more of it.
			if (writingPos == d->cursorPos) {
				stringPos = d->cursorWidth;
			} else {
				stringPos = 0;
			}
			
			/// Then we find the item they want.
			while (currentPos != writingPos) {
				currentItem = currentItem->next;
				currentPos++;
			}
			
			/// If it's highlighted, then it's printed as yellow.
			if (writingPos == d->cursorPos) {
				setColor(YELLOW);
			/// If it's selected for a process, we colour it depending on the
			/// mode we're in.
			} else if ((writingPos >= d->selectedTopItem) && (writingPos <= d->selectedBottomItem)) {
				/// If we're moving it, we highlight it green.
				if ((d->mode == MODE_MOVE) || (d->mode == MODE_MOVE_MENU)) {
					setColor(LIGHTGREEN);
				}
				/// If we're copying it, we highlight it blue.
				/// If we're deleting it, we highlight it red.
			}
			
			/// Now, we print the letters we need to display. We stop 
			/// either when we hit the end of the string, or when we hit
			/// the end of the word.
			
			/// If it's selected, we go until the point where we need
			/// to end.
			if (writingPos == d->cursorPos) {
				while ((stringPos < d->cursorWidth + d->consoleWidth) && (stringPos < strlen(currentItem->data))) {
					printf("%c", currentItem->data[stringPos]);
					stringPos++;
				}
			/// Otherwise, we don't care how far across they are, we go
			/// up to the screen width.
			} else {
				while ((stringPos < d->consoleWidth) && (stringPos < strlen(currentItem->data))) {
					printf("%c", currentItem->data[stringPos]);
					stringPos++;
				}
			}
			/// If it's highlighted, then we change the colour back.
			if ((writingPos == d->cursorPos) || ((writingPos >= d->selectedTopItem) && (writingPos <= d->selectedBottomItem))) {
				setColor(GREY);
			}
			printf("\n");
			writingPos++;
		}
	}
}

void printFooter(Data d, List l) {
	/// This is the left-most element of the footer.
	// It'll probably print the current action.
	setColor(DARKGREY);
	
	locate(1, d->consoleHeight);
	if (d->mode == MODE_VIEW) {
		printf("VIEWMODE");	
	} else if (d->mode == MODE_ADD) {
		printf("ADDMODE");
	} else if (d->mode == MODE_DELETE) {
		printf("DELETEMODE");
	}
	/// This is the right-most element of the footer. It shows the
	/// current number of the selected element, and the total items in
	/// the list.
	int charsToDraw = 3;
	if (l->size != 0) {
		charsToDraw += log10(l->size);
	}
	if (d->cursorPos != 0) {
		charsToDraw += log10(d->cursorPos);
	}
	
	locate(d->consoleWidth - charsToDraw + 1, d->consoleHeight);
	printf("%d/%d", d->cursorPos, l->size);
	
	setColor(GREY);
}

void printViewMenu(Data d, List l) {
	// This will not be 100% good on thinner terminals.
	/// This is the number of characters that is drawn on the menu.
	// It's hardcoded per menu. Plus, I don't entirely know how to
	// implement it.
	// int charsToDraw = 31;
	
	setColor(WHITE);
	
	if (d->menuItem == 0) {
		setColor(YELLOW);
	}
	locate(1, d->consoleHeight);
	printf("ADD");
	setColor(WHITE);
	
	if (d->menuItem == 1) {
		setColor(YELLOW);
	}
	locate(5, d->consoleHeight);
	printf("EDIT");
	setColor(WHITE);
	
	if (d->menuItem == 2) {
		setColor(YELLOW);
	}
	locate(10, d->consoleHeight);
	printf("DELETE");
	setColor(WHITE);
	
	if (d->menuItem == 3) {
		setColor(YELLOW);
	}
	locate(17, d->consoleHeight);
	printf("MOVE");
	setColor(WHITE);
	
	if (d->menuItem == 4) {
		setColor(YELLOW);
	}
	locate(22, d->consoleHeight);
	printf("COPY");
	setColor(WHITE);
	
	if (d->menuItem == 5) {
		setColor(YELLOW);
	}
	locate(27, d->consoleHeight);
	printf("LOAD");
	setColor(WHITE);
	
	if (d->menuItem == 6) {
		setColor(YELLOW);
	}
	locate(32, d->consoleHeight);
	printf("SAVE");
	setColor(WHITE);
	
	if (d->menuItem == 7) {
		setColor(YELLOW);
	}
	locate(37, d->consoleHeight);
	printf("EXIT");
	
	setColor(GREY);
}

void printAddMenu(Data d, List l) {
	setColor(WHITE);
	
	if (d->menuItem == 0) {
		setColor(YELLOW);
	}
	locate(1, d->consoleHeight);
	printf("ADD ABOVE");
	setColor(WHITE);
	
	if (d->menuItem == 1) {
		setColor(YELLOW);
	}
	locate(11, d->consoleHeight);
	printf("ADD BELOW");
	setColor(WHITE);
	
	setColor(GREY);
}

void printDeleteMenu(Data d, List l) {
	setColor(WHITE);
	
	if (d->menuItem == 0) {
		setColor(YELLOW);
	}
	locate(1, d->consoleHeight);
	printf("DELETE ITEM");
	setColor(WHITE);
	
	if (d->menuItem == 1) {
		setColor(YELLOW);
	}
	locate(13, d->consoleHeight);
	printf("DELETE RANGE");
	setColor(WHITE);
	
	setColor(GREY);
}

void editItemScreen(Data d, List l) {
	/// Firstly, we move the cursor to the bottom of the screen.
	locate(1, d->consoleHeight);
	
	/// Our text will be stored in this array.
	char inputText[DATA_MAX_SIZE] = {0};
	
	/// The user then inputs the text.
	printf("Type what you want: ");
	fgets(inputText, DATA_MAX_SIZE, stdin);
	
	/// Then, we scan through the input and get rid of any unnecessary
	/// characters.
	int pos = 0;
	while (pos < DATA_MAX_SIZE) {
		if (inputText[pos] == '\n') {
			inputText[pos] = 0;
		}
		pos++;
	}
	
	/// Finally, we edit this specific item in the interface.
	editItem(l, inputText, d->cursorPos);
	
	/// We also flush stdin, as if you write over the limit, it'll try to apply
	/// itself to the next thing you write.
	fflush(stdin);
}

void addItemScreen(Data d, List l) {
	// This is the same as editItemScreen, just with a different function.
	// I might need to merge them.
	/// Firstly, we move the cursor to the bottom of the screen.
	locate(1, d->consoleHeight);
	
	/// Our text will be stored in this array.
	char inputText[DATA_MAX_SIZE] = {0};
	
	/// The user then inputs the text.
	printf("Type what you want: ");
	fgets(inputText, DATA_MAX_SIZE, stdin);
	
	/// Then, we scan through the input and get rid of any unnecessary
	/// characters.
	int pos = 0;
	while (pos < DATA_MAX_SIZE) {
		if (inputText[pos] == '\n') {
			inputText[pos] = 0;
		}
		pos++;
	}
	
	/// Finally, we edit this specific item in the interface.
	addItem(l, inputText, d->targetedItem);
	
	/// We also flush stdin, as if you write over the limit, it'll try to apply
	/// itself to the next thing you write.
	fflush(stdin);
}

void computeInput(Data d, List l) {
	/// Firstly, we get the keypress, then figure out what to do with it.
	int keyPress = getkey();
	/// When in viewmode...
	if (d->mode == MODE_VIEW) {
		/// If up is pressed...
		if (keyPress == KEY_UP) {
			d->cursorWidth = 0;
			scrollScreenUp(d, l);
		/// If down is pressed...
		} else if (keyPress == KEY_DOWN) {
			d->cursorWidth = 0;
			scrollScreenDown(d, l);
		/// If page up is pressed...
		} else if (keyPress == KEY_PGUP) {
			d->cursorWidth = 0;
			jumpScreenUp(d, l);
		/// If page down is pressed...
		} else if (keyPress == KEY_PGDOWN) {
			d->cursorWidth = 0;
			jumpScreenDown(d, l);
		/// If left was pressed...
		} else if (keyPress == KEY_LEFT) {
			scrollItemLeft(d, l);
		/// If right was pressed...
		} else if (keyPress == KEY_RIGHT) {
			scrollItemRight(d, l);
		/// If space is pressed...
		} else if (keyPress == KEY_SPACE) {
			/// The program enters the menu.
			d->mode = MODE_VIEW_MENU;
			d->menuItem = 0;
		/// If escape is pressed...
		} else if (keyPress == KEY_ESCAPE) {
			/// Quit the program.
			d->mode = MODE_EXIT;
		}
	} else if (d->mode == MODE_VIEW_MENU) {
		if (keyPress == KEY_RIGHT) {
			if (d->menuItem < 7) { // The 7 is the number of list items + 1.
				d->menuItem++;
			}
		} else if (keyPress == KEY_LEFT) {
			if (d->menuItem > 0) {
				d->menuItem--;
			}
		} else if (keyPress == KEY_ESCAPE) {
			d->mode = MODE_VIEW;
		} else if (keyPress == KEY_SPACE) {
			if (d->menuItem == 0) { // ADD
				d->mode = MODE_ADD_MENU;
				d->menuItem = 0;
			} else if (d->menuItem == 1) { // EDIT
				d->mode = MODE_EDIT;
			} else if (d->menuItem == 2) { // DELETE
				d->mode = MODE_DELETE_MENU;
				d->menuItem = 0;
			} else if (d->menuItem == 3) { // MOVE
				reportError(ERROR_UNIMPLEMENTED);
			} else if (d->menuItem == 4) { // COPY
				reportError(ERROR_UNIMPLEMENTED);
			} else if (d->menuItem == 5) { // LOAD
				reportError(ERROR_UNIMPLEMENTED);
			} else if (d->menuItem == 6) { // SAVE
				reportError(ERROR_UNIMPLEMENTED);
			} else if (d->menuItem == 7) { // EXIT
				d->mode = MODE_EXIT;
			}
		}
	} else if (d->mode == MODE_ADD_MENU) {
		if (keyPress == KEY_RIGHT) {
			if (d->menuItem < 1) {
				d->menuItem++;
			}
		} else if (keyPress == KEY_LEFT) {
			if (d->menuItem > 0) {
				d->menuItem--;
			}
		} else if (keyPress == KEY_ESCAPE) {
			d->mode = MODE_VIEW_MENU;
			d->menuItem = 0;
		} else if (keyPress == KEY_SPACE) {
			if (d->menuItem == 0) { // ADD ABOVE
				d->targetedItem = d->cursorPos;
			} else if (d->menuItem == 1) { // ADD BELOW
				d->targetedItem = d->cursorPos + 1;
			}
			d->mode = MODE_ADD;
		}
	} else if (d->mode == MODE_DELETE_MENU) {
		if (keyPress == KEY_RIGHT) {
			if (d->menuItem < 1) {
				d->menuItem++;
			}
		} else if (keyPress == KEY_LEFT) {
			if (d->menuItem > 0) {
				d->menuItem--;
			}
		} else if (keyPress == KEY_ESCAPE) {
			d->mode = MODE_VIEW_MENU;
			d->menuItem = 2;
		} else if (keyPress == KEY_SPACE) {
			if (d->menuItem == 0) { // DELETE ITEM
				d->targetedItem = d->cursorPos;
				deleteItem(l, d->cursorPos);
			} else if (d->menuItem == 1) { // DELETE RANGE
				reportError(ERROR_UNIMPLEMENTED);
			}
			d->mode = MODE_VIEW;
		}
	}
}

void updateConsoleData(Data d) {
	d->consoleHeight = trows();
	d->consoleWidth = tcols() - 1;
}

void scrollScreenUp(Data d, List l) {
	/// If the cursor is not at the top of the list, we move it up.
	if (d->cursorPos > 1) {
		d->cursorPos--;
	}
	
	/// If the screen is not at the top...
	if (d->topItem > 1) {
		/// And it's moved past the top quarter of the screen, then we
		/// move it up.
		if ((d->topItem + d->consoleHeight / 4) > d->cursorPos) {
			d->topItem--;
		}
	}
}

void scrollScreenDown(Data d, List l) {
	/// If the cursor is not at the bottom of the list, we move it down.
	if (d->cursorPos < l->size) {
		d->cursorPos++;
	}
	
	/// If the screen is not at the bottom, we move it down.
	// This currently goes further, leaving black space. Ideally, we
	// should just leave it when it prints NO MORE ITEMs.
	if (d->topItem < l->size) {
		/// There's also a catch if it's at the top of the list.
		// Do we still need this after the next check?
		if ((d->topItem > 5) || (d->cursorPos > 5)) {
			/// Also, if the cursor moves to the bottom quarter of the
			/// screen, then the screen moves down.
			if ((d->topItem + 3 * d->consoleHeight / 4) < d->cursorPos) {
				d->topItem++;
			}
		}
	}
}

void scrollItemLeft(Data d, List l) {
	if (d->cursorWidth > 0) {
		d->cursorWidth--;
	}
}

void scrollItemRight(Data d, List l) {
	// In the future, replace this 256 with the stringlength. I'll add a function
	// in ListFunctions that returns the length of the data of an item, which will
	// assist this.
	if (d->cursorWidth < (256 - d->consoleWidth)) {
		d->cursorWidth++;
	}
}

void jumpScreenUp(Data d, List l) {
	/// If the cursor is within a screen's distance to the top, then it
	/// just sets it as the top. Otherwise, it moves it a screen.
	if (d->cursorPos > d->consoleHeight - 1) {
		d->cursorPos -= d->consoleHeight - 1;
	} else {
		d->cursorPos = 1;
	}
	
	/// Similarly with the top item.
	if (d->topItem > d->consoleHeight - 1) {
		d->topItem -= d->consoleHeight - 1;
	} else {
		d->topItem = 1;
	}
}

void jumpScreenDown(Data d, List l) {
	/// If the cursor is within a screen's distance to the bottom, then
	/// it just sets it as the bottom. Otherwise, it moves it a screen.
	if (d->cursorPos < l->size - (d->consoleHeight - 1)) {
		d->cursorPos += d->consoleHeight - 1;
	} else {
		d->cursorPos = l->size;
	}
	
	/// Similarly with the bottom item.
	if (d->topItem < l->size - (d->consoleHeight - 1)) {
		d->topItem += d->consoleHeight - 1;
	} else {
		d->topItem = l->size;
	}
}
