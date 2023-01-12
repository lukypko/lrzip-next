/*
 * folderTraversal.c
 *
 *  Created on: Oct 26, 2022
 *      Author: luky
 */

#include <folderTraversal.h>
#include <stdio.h>

struct folderTraversal* traverse_init(char *path) {

	// open folder

	struct folderTraversal *folderTraversal = malloc(
			sizeof(struct folderTraversal));
	folderTraversal->folderStack = stack_init();
//	folderTraversal->path = path;

// if item is a folder
	struct folderTraversal_item *folderTraversalItem = malloc(
			sizeof(struct folderTraversal_item));

	folderTraversalItem->owner = folderTraversal;
	folderTraversalItem->path = path;
	folderTraversalItem->dir = NULL;

	stack_push(folderTraversal->folderStack, folderTraversalItem);

	return folderTraversal;

}

static char* concatPath(char *parent, char *child) {

	int parentLen = strlen(parent);
	int len = parentLen + strlen(child) + 2;
	char *mergedPath = malloc(sizeof(char) * len);
	strcpy(mergedPath, parent);
	mergedPath[parentLen] = '/';
	strcpy(mergedPath + parentLen + 1, child);

	return mergedPath;
}

static bool isFolder(char *path) {

}

bool traverse_iterate(struct folderTraversal *traverser) {

	while (true) {

		struct folderTraversal_item *folderTraversalItem;
		if (!stack_peek(traverser->folderStack,
				(void**) &folderTraversalItem)) {

			printf("Failed to read a current folder\n");
			return false;
//		exit(1);
		}

		// get a next folder item
		if (folderTraversalItem->dir == NULL) {
			if ((folderTraversalItem->dir = opendir(folderTraversalItem->path))
					== NULL) {
				//if ((folderTraversalItem->dir = fdopendir(fd_in)) == NULL) {

				//error, folder cannot be opened
				printf("error, folder %s cannot be opened\n",
						folderTraversalItem->path);
				exit(1);
			}

			folderTraversalItem->parent = folderTraversalItem->path;

		}

		if ((folderTraversalItem->dirEntry = readdir(folderTraversalItem->dir))
				!= NULL) {

			folderTraversalItem->path = concatPath(folderTraversalItem->parent,
					folderTraversalItem->dirEntry->d_name);

//			if (folderTraversalItem->dirEntry->d_type == DT_UNKNOW) {

			if (strcmp(".", folderTraversalItem->dirEntry->d_name) == 0
					|| strcmp("..", folderTraversalItem->dirEntry->d_name)
							== 0) {

				// skipping . and .. folders
				continue;
			}

			folderTraversalItem->folderEntryStat = malloc(sizeof(struct stat));
			stat(folderTraversalItem->path,
					folderTraversalItem->folderEntryStat);

			if (S_ISDIR(folderTraversalItem->folderEntryStat->st_mode)) {

				// folder

				// if item is a folder
				struct folderTraversal_item *newFolderTraversalItem = malloc(
						sizeof(struct folderTraversal_item));

				newFolderTraversalItem->owner = traverser;
				newFolderTraversalItem->path = folderTraversalItem->path;

				stack_push(traverser->folderStack, newFolderTraversalItem);

			}
		} else {

			// no more items in a folder

			// end of iteration
			closedir(folderTraversalItem->dir);

			// return to a previous (parent) entry in a folder/tree hierarchy
//			struct folderTraversal_item *folderTraversalItem;

			free(folderTraversalItem->path);
			free(folderTraversalItem->folderEntryStat);
			stack_pop(traverser->folderStack, NULL);

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
