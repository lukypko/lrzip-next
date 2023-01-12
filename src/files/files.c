/*
 * files.c
 *
 *  Created on: Sep 24, 2022
 *      Author: luky
 */

#include <fcntl.h>
#include <files.h>
#include <linkedList.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <util.h>
#include <dirent.h>
#include "iterator.h"

// #include "lrzip_private.h"

/**
 * TODO create a in-archive file name based on its provided (external) file name.
 */
static char* getLocalFileName(char *path, char *baseFolder) {

	int len = strlen(path);

	char *localFilePath = malloc(sizeof(char) * (len + 1));
	strcpy(localFilePath, path);
	return localFilePath;
}
//
//struct files_folderIterator {
//
//	int fileDescriptorFolder;
//	char *folderName;
//
//	struct rzip_files *rzip;
//	char *path;
//
//	struct rzip_file *fileItem;
//
//	DIR *folder;
//	struct dirent *folderItem;
//	bool isFolder;
////	bool hasNext;
//};
//
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
//			folderIterator->path = NULL;
//	} else {
//
//	}
//
//}
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
//static bool files_folderIterator(struct iterator *iterator, void **value) {
//
//struct files_folderIterator *folderIterator = iterator->holder;
//
//while (true) {
//	createFileItem(folderIterator);
//	if (folderIterator->isFolder) {
//
//		char *path = readNextFolderItem(folderIterator);
//		continue;
//
//	} else {
//
//		*value = folderIterator->fileItem;
//	}
//
//	//TODO: generate from readNextFolderItem
//	char *path;
//
//	struct iterator *newItems = createFileItems(folderIterator->rzip, path);
//
//	struct linked_list *iterators = linkedList_init();
//	linkedList_add(iterators, iterator);
//	linkedList_add(iterators, newItems);
//
//	struct iterator *iteratorMerged = iterator_initMerge(iterators);
//
//	if (rangeGenerator->current >= rangeGenerator->to) {
//		return false;
//	}
//
////	int *value2 = value;
//	*value = &rangeGenerator->current;
//	rangeGenerator->current++;
////	(*(int*)value) = rangeGenerator->current;
//	return true;
//}
//}

static struct iterator* createFileItems(struct rzip_files *rzip, char *path) {

}
//
//struct iterator *iterator;
////	iterator_init(nextItem);
//
//struct rzip_file *fileItem = malloc(sizeof(struct rzip_file));
//
//int fd_in = open(path, O_RDONLY);
//if (unlikely(fd_in == -1)) {
//	printf("Failed to open %s\n", path);
//	exit(1);
////		fatal("Failed to open %s\n", path);
//}
//
//// get a file length
//struct stat buf;
//fstat(fd_in, &buf);
//
//if (S_ISDIR(buf.st_mode)) {
//
//	// path is a directory
//
//	struct files_folderIterator *folderIterator = malloc(
//			sizeof(struct files_folderIterator));
//	folderIterator->folderName = path;
//	folderIterator->fileDescriptorFolder = fd_in;
//	folderIterator->rzip = rzip;
//
//	readNextFolderItem(folderIterator);
//	fileItem->fileLength = 0;
//
//	// TODO: create string path1/fileName
//
//	path = folderIterator->folderItem->d_name;
//	fileItem->isFolder = true;
//
//	iterator = iterator_init(readNextFolderItem_iterator, folderIterator);
//
//} else {
//
//	fileItem->fileLength = buf.st_size;
//	fileItem->isFolder = false;
////	fileItem->fileLength = buf.st_size;
////	fileItem->fileHandle = fd_in;
//
////		if (rzip->premapFiles) {
//
//	fileItem->preMappedFile = mmap(NULL, fileItem->fileLength,
//	PROT_READ,
//	MAP_SHARED, fd_in, 0);
//	close(fd_in);
////		} else {
////			rzip->premapFiles = NULL;
////		}
//
//	iterator = iterator_initSingleItem(fileItem);
//}
//
//fileItem->filePath = getLocalFileName(path, NULL);
//
//return iterator;
//}

//static struct iterator* createFileItem(struct rzip_files *rzip, char *path) {
//
//	int fd_in = open(path, O_RDONLY);
//	if (unlikely(fd_in == -1)) {
//		printf("Failed to open %s\n", path);
//		exit(1);
////		fatal("Failed to open %s\n", path);
//	}
//
//// get a file length
//	struct stat buf;
//	fstat(fd_in, &buf);
//
//	if (S_ISDIR(buf.st_mode)) {
//
//		readFolder(fd_in);
//
//		// TODO: path is a directory, process is recursively...
//		printf("Item %s is a folder\n", path);
//		exit(1);
//	} else {
//		break;
//	}
//}
//
//struct iterator *iterator = malloc(sizeof(struct iterator));
//}

static void addSingleItem(struct rzip_files *rzip, struct rzip_file *rzip_file) {
linkedList_add(rzip->rzip_files, rzip_file);

// configure offsets for newly added file
rzip_file->dataOffset = rzip->tmpOffset;
rzip->tmpOffset += rzip_file->fileLength;

rzip_file->dataEndByte = rzip_file->dataOffset + rzip_file->fileLength;
}

void files_addFile(struct rzip_files *rzip, char *path) {

//	struct rzip_file *rzip_file = createFileItem(rzip, path);

struct iterator *iterator = createFileItems(rzip, path);
struct rzip_file *rzip_file;

while (iterator_next(iterator, &rzip_file)) {
	//while (iterator->next(iterator, rzip_file)) {

	linkedList_add(rzip->rzip_files, rzip_file);

	// configure offsets for newly added file
	rzip_file->dataOffset = rzip->tmpOffset;
	rzip->tmpOffset += rzip_file->fileLength;

	rzip_file->dataEndByte = rzip_file->dataOffset + rzip_file->fileLength;
}
}

/**
 * Initialize a structure.
 */
struct rzip_files* files_initFiles() {

struct rzip_files *rzip_files = malloc(sizeof(struct rzip_files));
rzip_files->rzip_files = linkedList_init();
rzip_files->tmpOffset = 0;

return rzip_files;
}

//void mmapinput(rzip_control *control, struct rzip_files_buffer *buffer) {
//
//	i64 end = buffer->offset + buffer->length;
//
//	struct linked_list_item *listItem = buffer->origin->rzip_files->start;
//	buffer->rzip_files->start = NULL;
//	buffer->rzip_files->end = NULL;
//
//	while (listItem != NULL) {
//
//		struct rzip_file *rzip_fileItem = listItem->item;
//
//		if (buffer->rzip_files->start == NULL
//				&& (rzip_fileItem->dataEndByte >= buffer->offset)) {
//
//			// found a start
//			buffer->rzip_files->start = listItem;
//		}
//
//		if ((rzip_fileItem->dataOffset + rzip_fileItem->fileLength) <= end) {
//
//			//found the end
//			buffer->rzip_files->end = listItem;
//
//			return;
//		}
//
//		// move to the next file in the list
//		listItem = listItem->next;
//	}
//
//	fatal("FATAL input buffer %d-%d too high!\n", buffer->offset, end);
//}

//void mmapinput(rzip_control *control, i64 offset, i64 len);

/**
 * find first mapping file
 */
static struct linked_list_item* findFirstMappingFile(rzip_control *control,
	struct rzip_files_buffer *buffer, i64 offset) {

struct linked_list_item *listItem = buffer->origin->rzip_files->start;
//	buffer->rzip_files->start = NULL;
//	buffer->rzip_files->end = NULL;

while (listItem != NULL ) {

	struct rzip_file *rzip_fileItem = listItem->item;

	if (rzip_fileItem->dataEndByte > offset) {

		// found a start
//			buffer->rzip_files->start = listItem;
		return listItem;
	}

	// move to the next file in the list
	listItem = listItem->next;
}

fatal("FATAL input buffer %d out of range!\n", offset);

return NULL ;
}

///**
// * `offset` - offset to align
// * return - aligned offset to a page_size
// */
//static i64 alignOffsetToPage(rzip_control *control,
//		struct rzip_file *rzip_fileItem, i64 offset) {
//
//	//i64 delta = (offset - rzip_fileItem->dataOffset) % control->page_size;
//	i64 delta = offset % control->page_size;
////	buffer->offset -= delta;
//
//	return offset - delta;
//}

i64 remap_count = 0;

/**
 * Remmap an offset
 */

//static void map(rzip_control *control, struct rzip_files_buffer *buffer,
//		i64 offset) {
//
////	printf("Freeing buffer %s %d-%d\n", buffer->name, buffer->offset,
////			buffer->end);
//
//	remap_count++;
//	struct linked_list_item *rzip_file = findFirstMappingFile(control, buffer,
//			offset);
//
//	struct rzip_file *rzip_fileItem = rzip_file->item;
//
//	i64 fileDelta = (offset - rzip_fileItem->dataOffset) % control->page_size;
////	i64 aoffset = alignOffsetToPage(control, rzip_fileItem, offset);
//
//	buffer->offset = offset - fileDelta;
//// offset from the start of the current file
//	i64 fileOffset = offset - rzip_fileItem->dataOffset - fileDelta;
//
////	buffer->length
//
//	buffer->rzip_fileItem = rzip_fileItem;
//
////	rzip_control *control, void *__addr, size_t __len,
////	int __prot, int __flags, __off_t __offset
//
//// is a file is smaller then a page size, then length is just a file length
//	i64 bufferLength = MIN(rzip_fileItem->fileLength - fileOffset,
//			control->page_size);
//
//// unmap previous buffer
//	if (buffer->buffer != NULL && munmap(buffer->buffer, buffer->length)) {
//		fatal("Failed to unmmap a buffer\n");
//	}
//
////mmap(__addr, __len, /*__prot*/PROT_READ, /*__flags*/MAP_SHARED, __fd, __offset);
//	buffer->buffer = mmap(buffer->buffer, bufferLength, PROT_READ, MAP_SHARED,
//			rzip_fileItem->fileHandle, fileOffset);
//
//	buffer->length = bufferLength;
//	buffer->end = buffer->offset + bufferLength;
//
////	printf("Mapping buffer %s %d-%d, %d\n", buffer->name, buffer->offset,
////			buffer->end, offset);
//}
/**
 * Remmap of files which are already mapped.
 */

static void mapCached(rzip_control *control, struct rzip_files_buffer *buffer,
	i64 offset) {

//	printf("Freeing buffer %s %d-%d\n", buffer->name, buffer->offset,
//			buffer->end);

remap_count++;
struct linked_list_item *rzip_file = findFirstMappingFile(control, buffer,
		offset);

struct rzip_file *rzip_fileItem = rzip_file->item;

buffer->buffer = rzip_fileItem->preMappedFile;
buffer->offset = rzip_fileItem->dataOffset;
buffer->length = rzip_fileItem->fileLength;
buffer->end = buffer->offset + buffer->length;

//	printf("Mapping buffer %s %d-%d, %d\n", buffer->name, buffer->offset,
//			buffer->end, offset);
}

//void mmapx(struct rzip_files_buffer *buffer, i64 offset) {
//
//rzip_control *control, void *__addr, size_t __len,
//int __prot, int __flags, __off_t __offset
//
//mmap(__addr, __len, /*__prot*/PROT_READ, /*__flags*/MAP_SHARED, __fd, __offset);
//}

struct rzip_files_buffer* files_init_rzip_files_buffer(
	struct rzip_files *rzip_files) {

struct rzip_files_buffer *rzip_files_buffer = malloc(
		sizeof(struct rzip_files_buffer));

if (rzip_files_buffer == MAP_FAILED) {

//		fatal("Failed to allocate a rzip_files_buffer\n");
	printf("Failed to allocate a rzip_files_buffer\n");
}

rzip_files_buffer->buffer = NULL;
rzip_files_buffer->origin = rzip_files;

return rzip_files_buffer;
}

inline bool files_isinBuffer(rzip_control *control,
	struct rzip_files_buffer *filesBuffer, i64 offset) {

return filesBuffer->buffer != NULL && filesBuffer->offset <= offset
		&& offset < filesBuffer->end;
}

/**
 * mmap `offset` into memory,
 * `buffer` - use this buffer to mmap offset `offset`,
 * unmap a buffer when needed
 */
void files_mmapOffset(rzip_control *control, struct rzip_files_buffer *buffer,
	i64 offset) {

if (!files_isinBuffer(control, buffer, offset)) {

	// it is needed to remap a buffer
	//map(control, buffer, offset);
	mapCached(control, buffer, offset);
}

}

inline uchar files_getDirectBufferByte(rzip_control *control,
	struct rzip_files_buffer *buffer, i64 offset) {

i64 delta = offset - buffer->offset;
if (delta < 0 || delta >= buffer->length) {

	fatal("Out of buffer index");
}
return buffer->buffer[delta];
}

///**
// * Get a single byte of input data on a offset `offset` using a `buffer`.
// * If needed a `buffer` is remapped.
// */
//uchar files_getBufferByte(rzip_control *control,
//		struct rzip_files_buffer *buffer, i64 offset) {
//
//	files_mmapOffset(control, buffer, offset);
//
//	return files_getDirectBufferByte(control, buffer, offset);
//}

