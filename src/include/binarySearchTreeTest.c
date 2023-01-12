/*
 * iteratorTest.c
 *
 *  Created on: Oct 25, 2022
 *      Author: luky
 */

#include <stdbool.h>
#include <stdio.h>

#include "binarySearchTree.h"
#include "linkedList.h"

static inline int binComparator(void *value1, void *value2) {

	int *first = (int*) value1;
	int *second = (int*) value2;

//	printf("First addr=%p\n", value1);
//	printf("First value=%'lu\n", (int*)value1);

// 0 or -1 or 1
//return (*first > *second) - (*first < *second);
	return first < second ? -1 : first > second ? 1 : 0;
}

void binarySearchTree_test1() {

	struct linked_list *items = linkedList_init();
	linkedList_add(items, (void*) 3);
	linkedList_add(items, (void*) 5);
	linkedList_add(items, (void*) 6);
	linkedList_add(items, (void*) 7);
	linkedList_add(items, (void*) 9);
	linkedList_add(items, (void*) 11);
	linkedList_add(items, (void*) 12);
	linkedList_add(items, (void*) 14);
	linkedList_add(items, (void*) 17);
	linkedList_add(items, (void*) 22);

	struct binary_search_tree *tree = binarySearchTree_init(&binComparator,
			items);
}
