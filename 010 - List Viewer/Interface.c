/**
 *  \file Interface.c
 *  \brief This file defines the main functions that the user will
 *  interract with.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rlutil.h"
#include "Interface.h"
#include "ListFunctions.h"
#include "FileIO.h"

int main(int argc, char *argv[]) {
	printf("I'm a bit lazy, there's no main right now...whoops!\n");
	
	return EXIT_SUCCESS;
}

void reportError(int errorCode) {
	if (errorCode == ERROR_DELETED_PAST_SIZE) {
		setColor(RED);
		printf("ERROR (%d): ERROR_DELETED_PAST_SIZE\n", ERROR_DELETED_PAST_SIZE);
		setColor(GREY);
		printf("The program tried to delete an item past the size of the list.\n");
		printf("If you're seeing this error, then the program messed up. Blame it on me.\n");
	} else if (errorCode == ERROR_DELETED_ITEM_FROM_NULL_LIST) {
		setColor(RED);
		printf("ERROR (%d): ERROR_DELETED_ITEM_FROM_NULL_LIST\n", ERROR_DELETED_ITEM_FROM_NULL_LIST);
		setColor(GREY);
		printf("The program tried to delete an item from an empty list.\n");
		printf("If you're seeing this error, then the program messed up. Blame it on me.\n");
	} else if (errorCode == ERROR_ADDED_PAST_SIZE) {
		setColor(RED);
		printf("ERROR (%d): ERROR_ADDED_PAST_SIZE\n", ERROR_ADDED_PAST_SIZE);
		setColor(GREY);
		printf("The program tried to add an item past the size of the list.\n");
		printf("If you're seeing this error, then the program messed up. Blame it on me.\n");
	}
}