/**
 *  \file ListFunctions.c
 *  \brief This file defines all the operations the program will use for
 *  lists.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rlutil.h"
#include "Interface.h"
#include "ListFunctions.h"
#include "FileIO.h"

/**
 *  \brief This function creates a list element.
 *  
 *  \return Returns a pointer to the created list.
 */
List createList() {
	List l = malloc(sizeof(list));
	l->size = 0;
	l->next = NULL;
	return list;
}

/**
 *  \brief This function adds an item to the given list, accepting the
 *  data and position of the item.
 *  
 *  \param [in] l The pointer to the list that will store this item.
 *  \param [in] data The data string that will be in the item.
 *  \param [in] pos The position in the list that the item is going in.
 */
void addItem(List l, char *data, int pos) {
	
}

/**
 *  \brief This function deletes an item from the given list, accepting
 *  the position of the item.
 *  
 *  \param [in] l The pointer to the list that stores this item.
 *  \param [in] pos The position in the list that the item is going out.
 */
void deleteItem(List l, int pos) {
	
}

/**
 *  \brief This function moves an item from one position to another in
 *  the list.
 *  
 *  \param [in] l The pointer to the list that stores this item.
 *  \param [in] posFrom The position in the list that is being moved.
 *  \param [in] posTo The position the item is being moved to.
 */
void moveItem(List l, int posFrom, int posTo) {
	
}

/**
 *  \brief This function copies an item from one position into another
 *  in the list.
 *  
 *  \param [in] l The pointer to the list that stores this item.
 *  \param [in] posFrom The position in the list that is being copied.
 *  \param [in] posTo The position the item is being copied to.
 */
void copyItem(List l, int posFrom, int posTo) {
	
}

/**
 *  \brief This function deletes the list from memory, used for loading
 *  a new list, or closing the program.
 *  
 *  \param [in] l The pointer to the list.
 */
void deleteList(List l) {
	Item currentItem = NULL;
	int pos = 0;
	while (l->next != NULL) {
		currentItem = l->next;
		pos = 1;
		while (currentItem->next != NULL) {
			currentItem = currentItem->next;
			pos++;
		}
		deleteItem(l, pos);
	}
	free(l);
}