#ifndef SRC_BINARY_SEARCH_TREE_H_
#define SRC_BINARY_SEARCH_TREE_H_

#include <stdbool.h>
#include <stdint.h>
#include <linkedList.h>

struct binary_search_tree {

	struct binary_search_tree_node *root;
	/**
	 * Compare a binary search tree nodes based on its value
	 */
	int (*valueComparator)(void* /*tree node*/, void* /*tree node*/);

	/**
	 * Compare a `value` and a binary search tree node value
	 */
	int (*searchComparator)(void* /*tree node value*/, void* /*tree node*/);
	int64_t nodeCount;
	void **sourceItems;
};

struct binary_search_tree_node {

	struct binary_search_tree_node *left;
	struct binary_search_tree_node *right;
	void *value;

	struct binary_search_tree *origin;
};

struct binary_search_tree_balance {

	int *codeSegment;
	int64_t *start;
	int64_t *end;
	struct binary_search_tree_node *node;
};

/**
 * Create a balanced binary search tree based on sorted items from `items`
 */
struct binary_search_tree* binarySearchTree_init(int (*valueComparator)(void*/*tree node*/, void*/*tree node*/),
		int (*searchComparator)(void*/*tree node value*/, void*/*tree node*/),
		struct linked_list *items);

/**
 * Search for in item in a binary search tree
 * `value` a value to search (and compare using a configured binarySearchTree valueComparator),
 * returns NULL, if value was not found
 */
void* binarySearchTree_search(struct binary_search_tree *tree, void *value);

//void binarySearchTree_add(struct binary_search_tree *tree, void *item);

#endif /* SRC_BINARY_SEARCH_TREE_H_ */
