/**
 * Linked list
 */
#ifndef SRC_LINKED_LIST_H_
#define SRC_LINKED_LIST_H_


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
void linkedList_cleanup(struct linked_list *linkedList);


#endif /* SRC_LINKED_LIST_H_ */
