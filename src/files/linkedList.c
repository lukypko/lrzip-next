/*
 * linkedList.c
 *
 *  Created on: Oct 6, 2022
 *      Author: luky
 */

#include <endian.h>
#include <linkedList.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

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
void linkedList_cleanup(struct linked_list *linkedList,
		void (*itemDestructor)(struct linked_list_item*/*linkedList_item*/,
				void* /*linked_list item*/)) {

	struct linked_list_item *item = linkedList->start;
	struct linked_list_item *next;
	while (item != NULL) {

		if (itemDestructor != NULL) {
			itemDestructor(item, item->item);
		}

		next = item->next;
		free(item);
		item = next;
	}

	free(linkedList);
}

int64_t linkedList_count(struct linked_list *linkedList) {

	int64_t count = 0;
	struct linked_list_item *item = linkedList->start;
	while (item != NULL) {

		++count;
		item = item->next;
	}

	return count;
}

/**
 * Convert a linkedList to array
 */
int64_t linkedList_toArray(struct linked_list *items, void **array) {

	int64_t  count= linkedList_count(items);
	array = malloc(sizeof(void*) * count);

	struct linked_list_item *listItem = items->start;
	for (int64_t i = 0; i < count; i++) {

		array[i] = listItem->item;
		listItem = listItem->next;
	}

	return count;
}


void *linkedList_getItem(struct linked_list *linkedList, int64_t index) {

	struct linked_list_item *item = linkedList->start;
	while (item != NULL) {

		if(index==0) {

			return item->next;
		}
		--index;
		item = item->next;
	}

	return NULL;
}

void linkedList_serialize(struct linked_list *linkedList, int fileDescriptor,
		void (*itemSerializer)(void* /*item to serialize*/,
				int /*fileDescriptor*/)) {

	int64_t itemsCount = htole64(linkedList_count(linkedList));

	if (write(fileDescriptor, &itemsCount, 8) != 8) {
		printf("Failed to write a linked list count\n");
		exit(1);
	}

	struct linked_list_item *item = linkedList->start;

	while (item != NULL) {

		itemSerializer(item->item, fileDescriptor);
		item = item->next;
	}
}
struct linked_list* linkedList_deserialize(int fileDescriptor,
		void* (*itemDeserializer)(int /*fileDescriptor*/)) {

	int64_t itemsCount;
	if (read(fileDescriptor, &itemsCount, 8) != 8) {
		printf("Failed to read a linked list count\n");
		exit(1);
	}
	itemsCount = le64toh(itemsCount);

	struct linked_list *linkedList = linkedList_init();
	for (; itemsCount > 0; itemsCount--) {

		linkedList_add(linkedList, itemDeserializer(fileDescriptor));
	}

	return linkedList;
}
