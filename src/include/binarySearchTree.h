
#ifndef SRC_BINARY_SEARCH_TREE_H_
#define SRC_BINARY_SEARCH_TREE_H_

#include <stdbool.h>
#include <stdint.h>
#include <linkedList.h>


struct binary_search_tree {

	struct binary_search_tree_node *root;
	int (*valueComparator)(void* /*value1*/, void* /*value2*/);
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
struct binary_search_tree* binarySearchTree_init(
		int (*valueComparator)(void*/*value1*/, void*/*value2*/),
		struct linked_list *items);

void binarySearchTree_add(struct binary_search_tree *tree, void *item);

#endif /* SRC_BINARY_SEARCH_TREE_H_ */
