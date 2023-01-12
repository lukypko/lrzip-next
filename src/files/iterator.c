/*
 * iterator.c
 *
 *  Created on: Oct 12, 2022
 *      Author: luky
 */

#include <stdlib.h>
#include "iterator.h"

struct iteratorMerge {

	struct linked_list_item *currentIterator;
};

struct iteratorSingle {

	bool hasNext;
	void *value;
};

bool mergeIterators(struct iterator *iterator, void **value) {

	struct iteratorMerge *merger = iterator->holder;
	struct iterator *currentIterator = merger->currentIterator->item;

	while (true) {
		bool ret = iterator_next(currentIterator, value);
		if (!ret) {

			//move to the next item
			merger->currentIterator = merger->currentIterator->next;
			if (merger->currentIterator == NULL) {

				free(merger);
				*value = NULL;
				return false;
			}

			// read a new value from next iterator
			currentIterator = merger->currentIterator->item;
			continue;
		}

		break;

	}
	return true;
}

static bool singleIterators(struct iterator *iterator, void **value) {

	struct iteratorSingle *single = iterator->holder;
	if (single->hasNext) {
		*value = single->value;
//		*(struct rzip_file*) value = single->value;
		single->hasNext = false;
		return true;
	} else {

		return false;
	}
}

struct iterator* iterator_initMerge(struct linked_list *iterators) {

	struct iteratorMerge *merger = malloc(sizeof(struct iteratorMerge));
	merger->currentIterator = iterators->start;
	return iterator_init(&mergeIterators, merger);
}

bool iterator_next(struct iterator *iterator, void **item) {

	bool ret = iterator->nextInternal(iterator, item);
	if (!ret) {

		free(iterator);
		*item = NULL;
	}
	return ret;

}
struct iterator* iterator_init(bool (*nextItem)(struct iterator*, void **value),
		void *holder) {

	struct iterator *iterator = malloc(sizeof(struct iterator));
	iterator->holder = holder;
	iterator->nextInternal = nextItem;

	return iterator;
}

struct iterator* iterator_initSingleItem(void *value) {

	struct iteratorSingle *iteratorSingle = malloc(
			sizeof(struct iteratorSingle));
	iteratorSingle->hasNext = true;
	iteratorSingle->value = value;

	return iterator_init(&singleIterators, iteratorSingle);

}
