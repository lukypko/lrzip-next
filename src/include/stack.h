#ifndef SRC_STACK_H_
#define SRC_STACK_H_

#include <stdlib.h>
#include <stdbool.h>

struct stack {
	struct stack_item *top;
//	/**
//	 * Item which needs to be free
//	 */
//	struct stack_item *cleanup;
};

struct stack_item {
	void *item;
	struct stack_item *previous;
	struct stack *owner;
};

/**
 * Initialize an empty stack.
 * call `stack_cleanup` at the end.
 */
struct stack* stack_init();
/**
 * Push (add) an item to the stack.
 */
void stack_push(struct stack *stack, void *item);

/**
 * Pop (remove) an item off the stack.
 * `stack` - stack to operate with
 * `item` - pointer to a variable to store a popped value
 * Return: `true` if item from top of the stack exist or `false` if stack is empty
 */
bool stack_pop(struct stack *stack, void **item);

/**
 * Return a value at a top of the stack
 */
bool stack_peek(struct stack *stack, void **item);

/**
 * Check a whether a stak is empty
 */
bool stack_isEmpty(struct stack *stack);

/**
 * Deallocate stack.
 */
void stack_free(struct stack *stack);

#endif /* SRC_STACK_H_ */
