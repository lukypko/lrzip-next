#include "stack.h"
#include <stdlib.h>

/**
 * Initialize an empty stack.
 * call `stack_cleanup` at the end.
 */
struct stack* stack_init() {

	struct stack *stack = malloc(sizeof(struct stack));
	stack->top = NULL;
//	stack->cleanup = NULL;

	return stack;
}

///**
// * Cleanup last popped item if any.
// */
//static void stack_cleanup(struct stack *stack) {
//
//	if (!stack->cleanup) {
//
//		free(stack->cleanup);
//		stack->cleanup = NULL;
//	}
//}

/**
 * Push (add) an item to the stack.
 */
void stack_push(struct stack *stack, void *item) {

//	stack_cleanup(stack);

	struct stack_item *newItem = malloc(sizeof(struct stack_item));
	newItem->item = item;
	newItem->owner = stack;

	newItem->previous = stack->top;
	stack->top = newItem;
}

/**
 * Pop (remove) an item to the stack.
 * Return: `true` if item from top of the stack exist or `false` if stack is empty
 */
bool stack_pop(struct stack *stack, void **item) {

//	stack_cleanup(stack);

	struct stack_item *topItem = stack->top;
	if (topItem != NULL) {

		stack->top = topItem->previous;
		if (item != NULL) {
			*item = topItem->item;
		}

		// TODO: bad thing !!! How to free a memory when item reference is returned
		// so store an item which have to be cleanup (free) and free it in a next stack function call
		// find a better way how to do it !!!
//		stack->cleanup = topItem;
		free(topItem);
	} else {
		if (item != NULL) {
			*item = NULL;
		}
	}

	return topItem != NULL ;
}

/**
 * Return a value at a top of the stack
 */
bool stack_peek(struct stack *stack, void **item) {

//	stack_cleanup(stack);

	struct stack_item *topItem = stack->top;
	if (topItem != NULL) {
		*item = topItem->item;
	} else {
		*item = NULL;
	}

	return topItem != NULL ;
}

/**
 * Check a whether a stak is empty
 */
bool stack_isEmpty(struct stack *stack) {

	return stack->top==NULL;
}


/**
 * Deallocate stack.
 */
void stack_free(struct stack *stack) {

//	stack_cleanup(stack);

	struct stack_item *item = stack->top;
	struct stack_item *previousItem;
	while (item != NULL ) {

		previousItem = item->previous;
		free(item);
		item = previousItem;
	}

	free(stack);
}
