/*
 * linkedList.c
 *
 *  Created on: Oct 6, 2022
 *      Author: luky
 */
#include "linkedList.h"
#include <stdlib.h>

/**
 * Initialize an empty linked_list.
 * call `linkedList_cleanup` at the end.
 */
struct linked_list* linkedList_init() {

//	struct linked_list *linked_list=  (struct linked_list *) malloc(sizeof(struct linked_list));
	struct linked_list *linkedList = malloc(sizeof(struct linked_list));
	linkedList->start = NULL;
	linkedList->end = NULL;

	return linkedList;
}

/**
 * Add an item to the list.
 */
void linkedList_add(struct linked_list *linkedList, void *item) {

	struct linked_list_item *newItem = malloc(sizeof(struct linked_list_item));
	newItem->item = item;
	newItem->owner = linkedList;
	newItem->next = NULL;

	if (linkedList->end != NULL) {
		linkedList->end->next = newItem;
	}

	linkedList->end = newItem;

	if (linkedList->start == NULL) {
		linkedList->start = newItem;
	}

}

/**
 * Deallocate list.
 */
void linkedList_cleanup(struct linked_list *linkedList) {

	struct linked_list_item *item = linkedList->start;
	struct linked_list_item *next;
	while (item != NULL) {

		next = item->next;
		free(item);
		item = next;
	}

	free(linkedList);
}

