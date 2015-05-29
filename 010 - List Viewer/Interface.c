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
	addItem(l, "test1", 1);
	addItem(l, "test2", 2);
	addItem(l, "test1.5", 2);
	
	while (l->size < 4510) {
		addItem(l, "BLAH", 3);
	}
	
	printf("d->consoleWidth = %d, d->consoleHeight = %d\n", d->consoleWidth, d->consoleHeight);
	getkey();
	
	cls();
	printList(d, l);
	printFooter(d, l);
	getkey();
	
	quitProgram(d, l);
	
	return EXIT_SUCCESS;
}

void reportError(int errorCode) {
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
	}
}

Data startProgram() {
	Data d = malloc(sizeof(data));
	d->consoleHeight = trows();
	d->consoleWidth = tcols();
	d->cursorPos = 4505;
	d->cursorWidth = 0;
	d->topItem = 4500;
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
	
	/// This loops until we hit the row just above the bottom of the
	/// screen, or we hit a null item.
	while ((writingPos != (d->topItem + d->consoleHeight - 2)) && (currentItem != NULL)) {
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
			}
			
			// printf("sizeof(*(currentItem->data)) = %d\n", strlen(currentItem->data));
			
			/// Now, we print the letters we need to display. We stop 
			/// either when we hit the end of the string, or when we hit
			/// the end of the word.
			while ((stringPos < d->cursorWidth + d->consoleWidth) && (stringPos < strlen(currentItem->data))) {
				printf("%c", currentItem->data[stringPos]);
				stringPos++;
			}
			
			/// If it's highlighted, then we change the colour back.
			if (writingPos == d->cursorPos) {
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
	printf("VIEWMODE");
	
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
	
	locate(d->consoleWidth - charsToDraw, d->consoleHeight);
	printf("%d/%d", d->cursorPos, l->size);
	
	setColor(GREY);
}