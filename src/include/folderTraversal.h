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

#include <stddef.h>
#include <string.h>

#include "stack.h"

struct folderTraversal {

	char *path;

	/**
	 * Parent folder hierarchy of type `struct folderTraversal_item`
	 */
	struct stack *folderStack;

//	void (*itemCallback)(char* /*path*/);
};

struct folderTraversal_item {

	char *path;
	char *parent;

	DIR *dir;
	struct dirent *dirEntry;
	struct stat *folderEntryStat;

	struct folderTraversal *owner;
};

struct folderTraversal* traverse_init(char *path);


bool traverse_iterate(struct folderTraversal *traverser);

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

#endif /* SRC_FOLDER_TRAVERSAL_H_ */
