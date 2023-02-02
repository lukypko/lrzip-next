#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <util.h>
#include <libgen.h>

#include "stack.h"
#include "binarySearchTree.h"

/**
 * Save those variables into a stack
 */
static void beforeRecursion(struct stack *stack, int codeSegment, int64_t *start, int64_t *end, struct binary_search_tree_node *node)
{

	struct binary_search_tree_balance *balance = malloc(sizeof(struct binary_search_tree_balance));

	// store a clone of codeSegment
	balance->codeSegment = malloc(sizeof(int));
	memcpy(balance->codeSegment, &codeSegment, sizeof(int));

	// store a clone of start
	balance->start = malloc(sizeof(int64_t));
	memcpy((void*) (balance->start), (void*) start, sizeof(int64_t));

	// store a clone of end
	balance->end = malloc(sizeof(int64_t));
	memcpy((void*) (balance->end), (void*) end, sizeof(int64_t));

	// do not clone a node
	balance->node = node;

//	printf("push start=%d, end=%d, node=%d, codeSegment=%d\n", *start, *end, node->value, codeSegment);

	stack_push(stack, balance);
}

/**
 * Load those variables value from a stack
 */
static bool afterRecursion(struct stack *stack, int *codeSegment, int64_t *start, int64_t *end, struct binary_search_tree_node **node)
{

	struct binary_search_tree_balance *balance;
	bool exist = stack_pop(stack, (void**) &balance);
	if (exist) {
		*codeSegment = *balance->codeSegment;
		*start = *balance->start;
		*end = *balance->end;
		*node = balance->node;

		free(balance->codeSegment);
		free(balance->start);
		free(balance->end);
		free(balance);

//		printf("pop start=%d, end=%d, node=%d, codeSegment=%d\n", *start, *end, (*node)->value, *codeSegment);
	}

	return exist;
}

static struct binary_search_tree_node* walkRecursive(struct binary_search_tree *tree, int64_t start, int64_t end)
{

	struct binary_search_tree_node *newItem;

	if (start > end) {

		printf("Return 0(NULL)\n");
		return NULL;
	}

	int64_t middle = (start + end) / 2;
	newItem = malloc(sizeof(struct binary_search_tree_node));
	newItem->value = tree->sourceItems[middle];

	newItem->left = walkRecursive(tree, start, middle - 1);
	printf("Setting value of %d->left to %d\n", newItem->value, newItem->left != NULL ? newItem->left->value : NULL);
	newItem->right = walkRecursive(tree, middle + 1, end);
	printf("Setting value of %d->right to %d\n", newItem->value, newItem->right != NULL ? newItem->right->value : NULL);

	printf("Return %d\n", newItem->value);
	return newItem;
}

/**
 * Recursive version
 */
static void walk1(struct binary_search_tree *tree)
{

	tree->root = walkRecursive(tree, 0, tree->nodeCount - 1);
}

/**
 *
 * Recursive version of this code:
 *
 * codeSegment=0
 *
 if (start > end) {

 return NULL;
 }

 //Get the middle element and make it root
 int mid = (start + end)/2;
 TNode *root = newNode(arr[mid]);

 //Recursively construct the left subtree
 // and make it left child of root
 root->left = recursion(arr, start, mid - 1);

 codeSegment=1

 //Recursively construct the right subtree
 // and make it right child of root
 root->right = recursion(arr, mid + 1, end);

 codeSegment=2

 return root;
 }
 */
static void walk2(struct binary_search_tree *tree)
{

	int64_t start = 0;
	int64_t end = tree->nodeCount - 1;

	int codeSegment = 0;

	struct stack *stack = stack_init();
	struct binary_search_tree_node *newItem;
	struct binary_search_tree_node *returnValue;

	while (true) {

		// as we are storing only start and end, then middle have to be computed
		int64_t middle = (start + end) / 2;

		switch (codeSegment) {

		case 0:

			if (start > end) {

				returnValue = NULL;

				if (!afterRecursion(stack, &codeSegment, &start, &end, &newItem)) {
					goto cycleDone;
				}
				break;
			}

			newItem = malloc(sizeof(struct binary_search_tree_node));
			newItem->value = tree->sourceItems[middle];

			int v = 1;
			beforeRecursion(stack, 1, &start, &end, newItem);
			end = middle - 1;
			break;
		case 1:

			newItem->left = returnValue;
			printf("Setting value of %d->left to %d\n", newItem->value, returnValue != NULL ? returnValue->value : NULL);
			v = 2;
			beforeRecursion(stack, 2, &start, &end, newItem);

			start = middle + 1;
			codeSegment = 0;

			break;

		case 2:

			newItem->right = returnValue;
			printf("Setting value of %d->right to %d\n", newItem->value, returnValue != NULL ? returnValue->value : NULL);
			returnValue = newItem;

			if (!afterRecursion(stack, &codeSegment, &start, &end, &newItem)) {
				goto cycleDone;
			}
			break;
		}

	}

	cycleDone:

	tree->root = returnValue;
}

static void walk3(struct binary_search_tree *tree)
{

	int64_t start = 0;
	int64_t end = tree->nodeCount - 1;

	int codeSegment = 0;

	struct stack *stack = stack_init();
	struct binary_search_tree_node *newItem;
	struct binary_search_tree_node *returnValue;

	do {

		// inner loop iteration cycle
		while (true) {

			// as we are storing only start and end, then middle have to be computed
			int64_t middle = (start + end) / 2;

			switch (codeSegment) {
			case 0:

				if (start > end) {

					returnValue = NULL;
					goto recursiveReturn;
				}

				newItem = malloc(sizeof(struct binary_search_tree_node));
				newItem->value = tree->sourceItems[middle];

				beforeRecursion(stack, 1, &start, &end, newItem);
				end = middle - 1;
				break;
			case 1:

				newItem->left = returnValue;
//				printf("Setting value of %d->left to %d\n", newItem->value, returnValue != NULL ? returnValue->value : NULL);
				beforeRecursion(stack, 2, &start, &end, newItem);

				start = middle + 1;
				codeSegment = 0;
				break;
			case 2:

				newItem->right = returnValue;
//				printf("Setting value of %d->right to %d\n", newItem->value, returnValue != NULL ? returnValue->value : NULL);
				returnValue = newItem;
				goto recursiveReturn;

			}
		}

		recursiveReturn: ;

	} while (afterRecursion(stack, &codeSegment, &start, &end, &newItem));

	tree->root = returnValue;
}

/**
 * Convert a sorted linkedList to array, validate order of input items
 */
static void binarySearchlinkedList_toArray(struct binary_search_tree *tree, struct linked_list *items)
{

	tree->nodeCount = linkedList_count(items);
	tree->sourceItems = malloc(sizeof(void*) * tree->nodeCount);

	void *lastItem;

	struct linked_list_item *listItem = items->start;
	for (int64_t i = 0; i < tree->nodeCount; i++) {

		if (i > 0) {
			if (tree->valueComparator(lastItem, listItem->item) > 0) {
				printf("binarySearchTree: error linked list items must be sorted");
				exit(1);
			}
		}

		tree->sourceItems[i] = listItem->item;
		lastItem = listItem->item;

		listItem = listItem->next;
	}
}

struct binary_search_tree* binarySearchTree_init(int (*valueComparator)(void*/*value1*/, void*/*value2*/),
		int (*searchComparator)(void*/*value1*/, void*/*value2*/),
		struct linked_list *items)
{

	struct binary_search_tree *tree = malloc(sizeof(struct binary_search_tree));
	tree->valueComparator = valueComparator;
	tree->searchComparator = searchComparator;
	tree->root = NULL;

	binarySearchlinkedList_toArray(tree, items);

	walk3(tree);
//	walk2(tree);
//	walk1(tree);

	return tree;
}

/**
 * Compare two items using a tree specified comparator.
 */
static int binarySearchTree_compare(struct binary_search_tree *tree, void *item1, void *item2)
{

	return tree->valueComparator(item1, item2);
}

///**
// * Add an item to the search tree.
// */
//void binarySearchTree_add(struct binary_search_tree *tree, void *item) {
//
//	struct binary_search_tree_node *newItem = malloc(
//			sizeof(struct binary_search_tree_node));
//	newItem->value = item;
//
//	if (tree->root != NULL) {
//
//		struct binary_search_tree_node *treeNode = tree->root;
//		struct binary_search_tree_node *parent;
//
//		while (true) {
//
//			parent = treeNode;
//			int cmp = tree->valueComparator(newItem, treeNode);
//
//			if (cmp < 0) {
//
//				treeNode = treeNode->left;
//				if (treeNode == NULL) {
//					parent->left = newItem;
//					break;
//				}
//			} else /*if(cmp >0)*/{
//
//				treeNode = treeNode->right;
//				if (treeNode == NULL) {
//					parent->right = newItem;
//					break;
//				}
//			}
//
//		}
//	} else {
//
//		// it is the initial node in the tree
//		tree->root = newItem;
//		newItem->left = NULL;
//		newItem->right = NULL;
//	}
//}

void* binarySearchTree_search(struct binary_search_tree *tree, void *value)
{
	struct binary_search_tree_node *item = tree->root;

	while (item != NULL) {

		int cmp = tree->searchComparator(value, item->value);
		if (cmp < 0) {

			//go left
			item = item->left;
		} else if (cmp > 0) {

			//go right
			item = item->right;
		} else {

			// item found
			return item->value;
		}
	}

	// reached end ot the tree, item not found
	return NULL;
}

/**
 * Deallocate tree.
 */
void binarySearchTree_cleanup(struct binary_search_tree *tree, void (*itemDestructor)(struct linked_list_item*/*linkedList_item*/, void* /*linked_list item*/))
{
//
//	struct linked_list_item *item = linkedList->start;
//	struct linked_list_item *next;
//	while (item != NULL) {
//
//		if (itemDestructor != NULL) {
//			itemDestructor(item, item->item);
//		}
//
//		next = item->next;
//		free(item);
//		item = next;
//	}
//
//	free(linkedList);
}

