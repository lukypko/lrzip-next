/*
 * iteratorTest.c
 *
 *  Created on: Oct 25, 2022
 *      Author: luky
 */

#include "iterator.h"

#include "folderTraversal.h"
#include "linkedList.h"

struct rangeGeneratorHolder {

	int to;
	int current;
};

bool rangeGenerator(struct iterator *iterator, void **value) {

	struct rangeGeneratorHolder *rangeGenerator = iterator->holder;

	if (rangeGenerator->current >= rangeGenerator->to) {
		return false;
	}

//	int *value2 = value;
	*value = &rangeGenerator->current;
	rangeGenerator->current++;
//	(*(int*)value) = rangeGenerator->current;
	return true;
}

void iteratorTest_test1() {

//	struct rzip_files *rzip_files = malloc(sizeof(struct rzip_files));

	struct rangeGeneratorHolder range1;

	range1.current = 2;
	range1.to = 10;

	struct iterator *iterator1 = iterator_init(&rangeGenerator, &range1);

	printf("Test1\n");

	//usage
	int *value;
	while (iterator_next(iterator1, (void*) &value)) {
//	while (iterator1->next(&value)) {

		printf("Value=%d\n", *value);

	}

	printf("\nTest2\n");

	range1.current = 2;
	struct rangeGeneratorHolder range2;

	range2.current = 5;
	range2.to = 8;

	struct rangeGeneratorHolder range3;

	range3.current = -3;
	range3.to = 2;

	iterator1 = iterator_init(&rangeGenerator, &range1);
	struct iterator *iterator2 = iterator_init(&rangeGenerator, &range2);
	struct iterator *iterator3 = iterator_init(&rangeGenerator, &range3);

	struct linked_list *iterators = linkedList_init();
	linkedList_add(iterators, iterator1);
	linkedList_add(iterators, iterator2);
	linkedList_add(iterators, iterator3);

	struct iterator *iteratorMerged = iterator_initMerge(iterators);

	//usage
	while (iterator_next(iteratorMerged, (void*) &value)) {

		printf("Value=%d\n", *value);

	}

	printf("\nTest3\n");
	int val1 = 5;

	iterator1 = iterator_initSingleItem(&val1);

	while (iterator_next(iterator1, (void*) &value)) {

		printf("Value=%d\n", *value);

	}

}

void change(void **target, void *source) {
	*target = source;
}

void iteratorTest_test2() {

	int *intNumber;
	int value = 6;
	change((void*) &intNumber, &value);

	printf("Number=%d\n", *intNumber);

	double *doubleNumber;
	double valueDouble = 3.14159;
	change((void*) &doubleNumber, &valueDouble);

	printf("Double=%f\n", *doubleNumber);
}

void stack_test1() {

	struct stack *stack1 = stack_init();
	char *value;

	printf("peek returned=%s has value=%d\n", value,
			stack_peek(stack1, (void**) &value));

	stack_push(stack1, "one");

	printf("peek returned=%s has value=%d\n", value,
			stack_peek(stack1, (void**) &value));
	stack_push(stack1, "two");
	stack_push(stack1, "three");
	stack_push(stack1, "four");

	printf("peek returned=%s has value=%d\n", value,
			stack_peek(stack1, (void**) &value));

	while (stack_pop(stack1, (void**) &value)) {
		printf("pop returned=%s\n", value);
	}

	printf("peek returned=%s has value=%d\n", value,
			stack_peek(stack1, (void**) &value));

	stack_push(stack1, "five");

	printf("pop returned=%s has value=%d\n", value,
				stack_pop(stack1, (void**) &value));


	printf("pop returned=%s has value=%d\n", value,
					stack_pop(stack1, (void**) &value));


	int value1=1;
	int value2=2;
	int value3=3;
	int value4=4;



	stack_push(stack1, &value1);
	stack_push(stack1, &value2);
	stack_push(stack1, &value3);
	stack_push(stack1, &value4);


	int *intValue;

	while (stack_pop(stack1, (void**) &intValue)) {
		printf("pop returned=%d\n", *intValue);
	}

}

void folder_test1() {

	struct folderTraversal *traversal = traverse_init(".");
	while (traverse_iterate(traversal)) {

		printf("Path=%s\n", traversal->path);

	}

}
