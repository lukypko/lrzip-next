/*
 * iterator.c
 *
 *  Created on: Oct 12, 2022
 *      Author: luky
 */

#ifndef SRC_FILES_ITERATOR_
#define SRC_FILES_ITERATOR_


#include <stdbool.h>
#include "linkedList.h"

struct iterator {

	void *holder;

	/**
	 * Internal function
	 */
	bool (*nextInternal)(struct iterator*, void**);
};

/**
 * Initialize an iterator with a generator function reference
 */
struct iterator* iterator_init(bool (*nextItem)(struct iterator*, void**),
		void *holder);

/**
 * Initialize an iterator with a single item
 */
struct iterator* iterator_initSingleItem(void *value);

struct iterator* iterator_initMerge(struct linked_list *iterators);

bool iterator_next(struct iterator *iterator, void **item);


#endif /* SRC_FILES_ITERATOR_ */
