/**
 *  \file Interface.h
 *  \brief This file declares all the functions that are used by
 *  Interface.c.
 */

/// Error codes
#define ERROR_DELETED_PAST_SIZE 1
#define ERROR_DELETED_ITEM_FROM_NULL_LIST 2
#define ERROR_ADDED_PAST_SIZE 3

void reportError(int errorCode);