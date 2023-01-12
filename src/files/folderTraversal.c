/*
 * folderTraversal.c
 *
 *  Created on: Oct 26, 2022
 *      Author: luky
 */

#include <folderTraversal.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

struct folderTraversal* traverse_init(char *path) {

	// open folder

	struct folderTraversal *folderTraversal = malloc(
			sizeof(struct folderTraversal));
	folderTraversal->folderStack = stack_init();
	folderTraversal->path = NULL;

	// get a current folder
//	folderTraversal->currentFolder = get_current_dir_name();
	folderTraversal->currentFolder = getcwd(NULL, 0);

// if item is a folder
	struct folderTraversal_item *folderTraversalItem = malloc(
			sizeof(struct folderTraversal_item));

	folderTraversalItem->owner = folderTraversal;
	folderTraversalItem->parent = NULL;

	// copy a path, because we are "freeing" a previous path in each iteration step
	folderTraversalItem->path = strdup(path);

	folderTraversalItem->dir = NULL;
	folderTraversalItem->hasNext = true;

	stack_push(folderTraversal->folderStack, folderTraversalItem);

	return folderTraversal;

}

/**
 * Make a canonical path of `src` path
 * `pwd` - current folder
 */
static char* normalizePath(char *pwd, const char *src, char *res) {
	size_t res_len;
	size_t src_len = strlen(src);

	const char *ptr = src;
	const char *end = &src[src_len];
	const char *next;

	if (src_len == 0 || src[0] != '/') {
		// relative path
		size_t pwd_len;

		pwd_len = strlen(pwd);
		memcpy(res, pwd, pwd_len);
		res_len = pwd_len;
	} else {
		res_len = 0;
	}

	for (ptr = src; ptr < end; ptr = next + 1) {
		size_t len;
		next = (char*) memchr(ptr, '/', end - ptr);
		if (next == NULL) {
			next = end;
		}
		len = next - ptr;
		switch (len) {
		case 2:
			if (ptr[0] == '.' && ptr[1] == '.') {
				const char *slash = (char*) memrchr(res, '/', res_len);
				if (slash != NULL) {
					res_len = slash - res;
				}
				continue;
			}
			break;
		case 1:
			if (ptr[0] == '.') {
				continue;
			}
			break;
		case 0:
			continue;
		}

		if (res_len != 1)
			res[res_len++] = '/';

		memcpy(&res[res_len], ptr, len);
		res_len += len;
	}

	if (res_len == 0) {
		res[res_len++] = '/';
	}
	res[res_len] = '\0';
	return res;
}

/**
 * Make a path absolute
 */
static char* concatPath(struct folderTraversal *traversal, char *parent,
		char *child) {

	int parentLen = strlen(parent);
	int len = parentLen + strlen(child) + 2;
	char *mergedPath = malloc(sizeof(char) * len);
	strcpy(mergedPath, parent);
	mergedPath[parentLen] = '/';
	strcpy(mergedPath + parentLen + 1, child);

	char *canonicalPath = strdup(
			normalizePath(traversal->currentFolder, mergedPath,
					traversal->canonicalPath));
//	char *canonicalPath=realpath(mergedPath, NULL);

	free(mergedPath);
	return canonicalPath;
}

void cleanupItem(struct folderTraversal_item *folderTraversalItem) {

	if (folderTraversalItem->dir != NULL) {
		closedir(folderTraversalItem->dir);
	}

	// path is not freeing as it will be free from parent folder
	if (folderTraversalItem->path != NULL) {
		//				printf("END Freeing path %p, %s\n", folderTraversalItem->path,
		//						folderTraversalItem->path);
		free(folderTraversalItem->path);
	}

	if (folderTraversalItem->parent != NULL) {
		//				printf("END Freeing parent %p, %s\n",
		//						folderTraversalItem->parent,
		//						folderTraversalItem->parent);
		free(folderTraversalItem->parent);
	}

	free(folderTraversalItem);
}

bool traverse_iterate(struct folderTraversal *traverser) {

	while (true) {

		struct folderTraversal_item *folderTraversalItem;
		if (!stack_peek(traverser->folderStack,
				(void**) &folderTraversalItem)) {

//			if (traverser->path != NULL) {
//				printf("Final END Freeing path %p, %s\n", traverser->path,
//						traverser->path);
//				free(traverser->path);
//				traverser->path = NULL;
//			}

			return false;
		}

		if (!folderTraversalItem->hasNext) {

			return false;
		}

		// get a next folder item
		if (folderTraversalItem->dir == NULL) {
			if ((folderTraversalItem->dir = opendir(folderTraversalItem->path))
					== NULL) {

				folderTraversalItem->hasNext = false;

				// check whether it is not a file
				if (lstat(folderTraversalItem->path,
						&traverser->folderEntryStat)) {

					//error, path cannot be opened
					printf("error, path '%s' cannot be opened\n",
							folderTraversalItem->path);
					exit(1);
				}

				traverser->path = realpath(folderTraversalItem->path, NULL);

				// it is single file, so end in a next iteration

				return true;
			}

			folderTraversalItem->parent = strdup(folderTraversalItem->path);
		}

		if ((folderTraversalItem->dirEntry = readdir(folderTraversalItem->dir))
				!= NULL) {

			if (strcmp(".", folderTraversalItem->dirEntry->d_name) == 0
					|| strcmp("..", folderTraversalItem->dirEntry->d_name)
							== 0) {

				// skipping . and .. folders
				continue;
			}

			// free the previous item
			if (folderTraversalItem->path != NULL) {
//				printf("Freeing %p, %s\n", folderTraversalItem->path,
//						folderTraversalItem->path);
				free(folderTraversalItem->path);
				folderTraversalItem->path = NULL;
			}

			folderTraversalItem->path = concatPath(traverser,
					folderTraversalItem->parent,
					folderTraversalItem->dirEntry->d_name);

//			printf("New %p, %s\n", folderTraversalItem->path,
//					folderTraversalItem->path);

//			folderTraversalItem->folderEntryStat = malloc(sizeof(struct stat));

			// do not follow sym-links
			lstat(folderTraversalItem->path, &traverser->folderEntryStat);

			if (S_ISDIR(traverser->folderEntryStat.st_mode)) {

				// if item is a folder
				struct folderTraversal_item *newFolderTraversalItem = malloc(
						sizeof(struct folderTraversal_item));

				newFolderTraversalItem->owner = traverser;
				newFolderTraversalItem->path = strdup(
						folderTraversalItem->path);
				newFolderTraversalItem->parent = NULL;
				newFolderTraversalItem->dir = NULL;
				newFolderTraversalItem->hasNext = true;

				stack_push(traverser->folderStack, newFolderTraversalItem);

			}
		} else {

			// no more items in a folder
			cleanupItem(folderTraversalItem);

			// return to a previous (parent) entry in a folder/tree hierarchy
			//			struct folderTraversal_item *oldFolderTraversal;
			stack_pop(traverser->folderStack, (void**) NULL);

			// repeat reading of another item
			continue;
		}

		traverser->path = folderTraversalItem->path;
		break;
	}

	return true;
}

///**
// * Return: path of new folder item or NULL when no exist
// */
//static char* readNextFolderItem(struct files_folderIterator *folderIterator) {
//
//	if (folderIterator->folder == NULL) {
//
//		if ((folderIterator->folder = fdopendir(
//				folderIterator->fileDescriptorFolder)) == NULL) {
//
//			//error, folder cannot be opened
//			printf("error, folder %s cannot be opened\n",
//					folderIterator->folderName);
//			exit(1);
//
//		}
//	} else {
//
////	struct dirent *folderItem = readdir(folderIterator->folder);
//		folderIterator->folderItem = readdir(folderIterator->folder);
////	folderIterator->hasNext = folderItem != NULL;
//
//		if (folderIterator->folderItem == NULL) {
//
//			// end of iteration
//			closedir(folderIterator->folder);
//			close(folderIterator->fileDescriptorFolder);
//
//			folderIterator->path = NULL
//		:
//	} else {
//
//	}
//}
//
//}
//
//struct files_iteratorSingle {
//
//	bool hasNext;
//	void **value;
//};
//
//bool files_singleIterators(struct iterator *iterator, void *value) {
//
//	struct files_iteratorSingle *single = iterator->holder;
//	if (single->hasNext) {
////		*(struct rzip_file*) value = single->value;
//		single->hasNext = false;
//		return true;
//	} else {
//
//		return false;
//	}
//}

//static bool readNextFolderItem_iterator(struct iterator *iterator, void *value) {
//
//	struct files_folderIterator *folderIterator = iterator->holder;
//	char *path = folderIterator->folderItem->d_name;
//	folderIterator->folderName;
//
//	// new value
//	value;
//
//	return true;
//
//}
//
//static readFolder(int fdFolder) {
//
////	iterator_init (nextItem)
//
//	DIR *dp;
//	struct dirent *ep;
//	dp = fdopendir(fdFolder);
//	if (dp != NULL) {
//		while ((ep = readdir(dp)) != NULL )
//			puts(ep->d_name);
//
//		closedir(dp);
//		return 0;
//	}
//}
//
//struct iterator* createFileItems(struct rzip_files *rzip, char *path);
//
//static void readFolder(struct folderTraversal *folderTraversal, char *path) {
//
//struct rzip_files *rzip;
//
//struct rzip_file *fileItem = malloc(sizeof(struct rzip_file));
//
//int fd_in = open(path, O_RDONLY);
//if (fd_in == -1) {
//	printf("Failed to open %s\n", path);
//	exit(1);
////		fatal("Failed to open %s\n", path);
//}
//
//// get a file length
//struct stat buf;
//fstat(fd_in, &buf);
//
//folderTraversal->itemCallback(path);
//
//if (S_ISDIR(buf.st_mode)) {
//
//// path is a directory
//
//	DIR *dir;
//
//	if ((dir = fdopendir(fd_in)) == NULL) {
//
//		//error, folder cannot be opened
//		printf("error, folder %s cannot be opened\n", path);
//		exit(1);
//
//	} else {
//
//		struct dirent *dirEntry;
//		//	struct dirent *folderItem = readdir(folderIterator->folder);
//		while ((dirEntry = readdir(dir)) != NULL ) {
//
//			dirEntry->d_name;
//		}
//		//	folderIterator->hasNext = folderItem != NULL;
//
//		if (folderIterator->folderItem == NULL) {
//
//			// end of iteration
//			closedir(folderIterator->folder);
//			close(folderIterator->fileDescriptorFolder);
//
//			folderIterator->path = NULL
//		:
//	} else {
//
//	}
//
//}
//
//struct files_folderIterator *folderIterator = malloc(
//		sizeof(struct files_folderIterator));
//folderIterator->folderName = path;
//folderIterator->fileDescriptorFolder = fd_in;
//folderIterator->rzip = rzip;
//
//readNextFolderItem(folderIterator);
//fileItem->fileLength = 0;
//
//// TODO: create string path1/fileName
//
//path = folderIterator->folderItem->d_name;
//fileItem->isFolder = true;
//folderIterator->isFolder = true;
//
//iterator = iterator_init(readNextFolderItem_iterator, folderIterator);
//
//} else {
//
//fileItem->fileLength = buf.st_size;
//fileItem->isFolder = false;
////	fileItem->fileLength = buf.st_size;
////	fileItem->fileHandle = fd_in;
//
////		if (rzip->premapFiles) {
//
//fileItem->preMappedFile = mmap(NULL, fileItem->fileLength, PROT_READ,
//		MAP_SHARED, fd_in, 0);
//close(fd_in);
////		} else {
////			rzip->premapFiles = NULL;
////		}
//folderIterator->isFolder = false;
//iterator = iterator_initSingleItem(fileItem);
//}
//
//fileItem->filePath = getLocalFileName(path, NULL);
//folderIterator->fileItem = fileItem;
//}

void traverse_cleanup(struct folderTraversal *traverse) {

	struct folderTraversal_item *folderStackItem;

	while (stack_pop(traverse->folderStack, (void**) &folderStackItem)) {

		cleanupItem(folderStackItem);
	}

	stack_free(traverse->folderStack);
	free(traverse->currentFolder);
	free(traverse);
}
