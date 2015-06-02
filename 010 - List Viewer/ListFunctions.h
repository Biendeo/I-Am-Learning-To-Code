/**
 *  \file ListFunctions.h
 *  \brief This file declares the data structure of the lists and all
 *  the functions that operate on lists in ListFunctions.c.
 */

/**
 *  \typedef struct _item * Item
 *  \brief Defines Item as a pointer to the struct item.
 */
typedef struct _item * Item;

/**
 *  \struct _item
 *  \brief This is an element of the list.
 */
/**
 *  \typedef struct _item item
 *  \brief Defines item as the struct item.
 */
typedef struct _item {
	/** 
	 *  This stores a pointer to data string. The maximum size is
	 *  dictated by DATA_MAX_SIZE.
	 */
	char *data;
	/**
	 *  This stores a pointer to the next object in the list.
	 */
	Item next;
} item;

/**
 *  \typedef struct _list * List
 *  \brief Defines List as a pointer to the struct list.
 */
typedef struct _list * List;

/**
 *  \struct _list
 *  \brief This marks the beginning of the list.
 */
/**
 *  \typedef struct _list list
 *  \brief Defines list as the struct list.
 */
typedef struct _list {
	/**
	 *  This stores the size of the list.
	 */
	int size;
	/**
	 *  This stores a pointer to the first element of the list.
	 */
	Item next;
} list;

/**
 *  \def DATA_MAX_SIZE
 *  \brief This denotes what the maximum size of a data element (in
 *  terms of characters).
 */
#define DATA_MAX_SIZE 256

List createList();
void addItem(List l, char *data, int pos);
void editItem(List l, char *data, int pos);
void deleteItem(List l, int pos);
void moveItem(List l, int posFrom, int posTo);
void copyItem(List l, int posFrom, int posTo);
void deleteList(List l);