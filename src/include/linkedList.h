/**
 * Linked list
 */
#ifndef SRC_LINKED_LIST_H_
#define SRC_LINKED_LIST_H_

#include <stdlib.h>
#include <stdint.h>


struct linked_list {
	struct linked_list_item *start;
	struct linked_list_item *end;
};

struct linked_list_item {
	void *item;
	struct linked_list_item *next;
	struct linked_list *owner;
};

/**
 * Initialize an empty linked_list.
 * call `linkedList_cleanup` at the end.
 */
struct linked_list *linkedList_init();

/**
 * Add an item to the list.
 */
void linkedList_add(struct linked_list *linkedList, void *item);

/**
 * Deallocate list.
 */
void linkedList_cleanup(struct linked_list *linkedList, void (*itemDestructor)(struct linked_list_item*/*linked_list_item*/, void* /*linked_list item*/));

/**
 * Count items in a linked list
 */
int64_t linkedList_count(struct linked_list *linkedList);

/**
 * Convert a linkedList to array
 * `array`, pointer to array which will be allocated and filled by a function
 * return `length of array`
 */
int64_t linkedList_toArray(struct linked_list *items, void **array);

/**
 * Get item on index `index`, very ineffective, as it is linkedList
 */
void *linkedList_getItem(struct linked_list *linkedList, int64_t index);

void linkedList_serialize(struct linked_list *linkedList, int fileDescriptor,
		void (*itemSerializer)(void* /*item to serialize*/, int /*fileDescriptor*/));


struct linked_list* linkedList_deserialize(int fileDescriptor,
		void* (*itemDeserializer)(int /*fileDescriptor*/));

#endif /* SRC_LINKED_LIST_H_ */
