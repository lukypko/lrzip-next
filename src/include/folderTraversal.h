/*
 * folderTraversal.c
 *
 *  Created on: Oct 26, 2022
 *      Author: luky
 */

#ifndef SRC_FOLDER_TRAVERSAL_H_
#define SRC_FOLDER_TRAVERSAL_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <limits.h>

#include <stddef.h>
#include <string.h>

#include "stack.h"

struct folderTraversal {

	char *path;
	struct stat folderEntryStat;

	/**
	 * Parent folder hierarchy of type `struct folderTraversal_item`
	 */
	struct stack *folderStack;

	/**
	 * Holds a current folder path, it is immutable value
	 */
	char *currentFolder;

	/**
	 * Temporary working path.
	 * TODO: PATH_MAX is not a constant, see `man 3 pathconf`, `man 3 get_current_dir_name`
	 */
	char canonicalPath[PATH_MAX];
};

struct folderTraversal_item {

	char *path;
	char *parent;

	bool hasNext;

	DIR *dir;
	struct dirent *dirEntry;
	struct folderTraversal *owner;
};

struct folderTraversal* traverse_init(char *path);

bool traverse_iterate(struct folderTraversal *traverser);

void traverse_cleanup(struct folderTraversal *traverse);

#endif /* SRC_FOLDER_TRAVERSAL_H_ */
