/*
 * files.c
 *
 *  Created on: Sep 24, 2022
 *      Author: luky
 */

#include <fcntl.h>
#include <files.h>
#include <folderTraversal.h>
#include <linkedList.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <util.h>
#include <libgen.h>
#include "binarySearchTree.h"

// #include "lrzip_private.h"

/**
 * create an in-archive file name based on its provided (external) file name.
 */
static char* getLocalFileName(char *path, char *baseFolder) {

	int pathLen = strlen(path);

	int len = files_max(pathLen, strlen(baseFolder));
	int i;

	for (i = 0; i < len; i++) {

		if (path[i] != baseFolder[i]) {
			char *localFilePath = malloc(sizeof(char) * (pathLen - i + 1));
			strcpy(localFilePath, path + i);
			return localFilePath;

		}

	}

	char *localFilePath = malloc(sizeof(char) * (pathLen + 1));
	strcpy(localFilePath, path);
	return localFilePath;
}

/**
 * Concatenate two paths, allocates a new buffer, add a `/`
 */
static char* concatStrings(char *first, char *second) {

	int len1 = strlen(first);
	int len2 = strlen(second);

	char *newStr = malloc(sizeof(char) * (len1 + len2 + 1));
	strcpy(newStr, first);
	strcpy(newStr + len1, second);
	newStr[len1 + len2 + 1] = 0;

	return newStr;
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
//
//static struct rzip_file* createFileItem(struct rzip_files *rzip,
//		struct folderTraversal *sourceFile, char *basePath) {
//
//	struct rzip_file *fileItem = malloc(sizeof(struct rzip_file));
//
//	int fd_in = open(sourceFile->path, O_RDONLY);
//	if (unlikely(fd_in == -1)) {
//		printf("Failed to open %s\n", sourceFile->path);
//		exit(1);
//		//		fatal("Failed to open %s\n", path);
//	}
//
//	fileItem->fileLength = sourceFile->folderEntryStat.st_size;
//	fileItem->isFolder = false;
//	//	fileItem->fileHandle = fd_in;
//
//	fileItem->preMappedFile = mmap(NULL, fileItem->fileLength,
//	PROT_READ,
//	MAP_SHARED, fd_in, 0);
//	close(fd_in);
//
//	fileItem->filePath = getLocalFileName(sourceFile->path, basePath);
//
//	return fileItem;
//
//}

static struct rzip_file* createReadFileItem(struct rzip_files *rzip,
		struct folderTraversal *sourceFile) {

	struct rzip_file *fileItem = malloc(sizeof(struct rzip_file));

	int fd_in = open(sourceFile->path, O_RDONLY);
	if (unlikely(fd_in == -1)) {
		printf("Failed to open %s\n", sourceFile->path);
		exit(1);
	}

	fileItem->fileLength = sourceFile->folderEntryStat.st_size;

	// this absolute path will be replaced later with its in-archive relative path
	fileItem->filePath = strdup(sourceFile->path);
	fileItem->isFolder = false;
	fileItem->fileHandle = -1;

	fileItem->preMappedFile = mmap(NULL, fileItem->fileLength,
	PROT_READ,
	MAP_SHARED, fd_in, 0);
	close(fd_in);

	return fileItem;
}

static void createDestinationFolder(char *filePath) {

	char *folderPath = strdup(filePath);
	char *folderPath2=dirname(folderPath);

	mkdir(folderPath2, 0777);

	free(folderPath);
}

static void createWriteFileItem(struct rzip_files *rzip,
		struct rzip_file *fileItem) {

	char *filePath = concatStrings(rzip->basePath, fileItem->filePath);

	createDestinationFolder(filePath);

	int fd_out = open(filePath,
	O_RDWR | O_CREAT | O_TRUNC/*| O_EXCL*/, 0666);
	if (fd_out < 0) {
		printf("Cannot create a destination file '%s'\n", filePath);
		exit(1);
	}

//	iflseek(fd_out,fileItem->fileLength, SEEK_SET)==-1) {
//		printf("Cannot seea files holder file");
//				exit(1);
//	}

//	fileItem->fileLength = sourceFile->folderEntryStat.st_size;
//	fileItem->isFolder = false;
	//	fileItem->fileHandle = fd_in;

	fileItem->preMappedFile = mmap(NULL, fileItem->fileLength,
	PROT_READ,
	MAP_SHARED, fd_out, 0);

	fileItem->fileHandle = fd_out;
	//fileItem->filePath = getLocalFileName(sourceFile->path, basePath);

	free(fileItem->filePath);

	// replace "in-archive" path with a full disk path
	fileItem->filePath = filePath;
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

//static void addSingleItem(struct rzip_files *rzip, struct rzip_file *rzip_file) {
//	linkedList_add(rzip->rzip_files, rzip_file);
//
//// configure offsets for newly added file
//	rzip_file->dataOffset = rzip->tmpOffset;
//	rzip->tmpOffset += rzip_file->fileLength;
//
//	rzip_file->dataEndByte = rzip_file->dataOffset + rzip_file->fileLength;
//}

/**
 configure offsets for newly added file
 */
static void addPathOffsets(struct rzip_files *rzip, struct rzip_file *rzip_file) {

	// configure offsets for newly added file
	rzip_file->dataOffset = rzip->tmpOffset;
	rzip->tmpOffset += rzip_file->fileLength;

	rzip_file->dataEndByte = rzip_file->dataOffset + rzip_file->fileLength;
}

void files_addPath(struct rzip_files *rzip, char *path) {

	struct folderTraversal *traversal = traverse_init(path);
	while (traverse_iterate(traversal)) {

		if (!S_ISDIR(traversal->folderEntryStat.st_mode)) {
			// it is file

			if (S_ISREG(traversal->folderEntryStat.st_mode)) {

//				if (!S_ISLNK(traversal->folderEntryStat.st_mode)) {

				struct rzip_file *rzip_file = createReadFileItem(rzip,
						traversal);

				linkedList_add(rzip->rzip_files, rzip_file);

				addPathOffsets(rzip, rzip_file);

				printf("Input file=%s (%'ld)\n", rzip_file->filePath,
						rzip_file->fileLength);
//				} else {
//
//					printf("Skipping a link =%s\n", traversal->path);
//				}
			} else {

				printf("Skipping not regular file=%s\n", traversal->path);
			}
		} else {

			printf("Skipping folder=%s\n", traversal->path);
		}

	}
	traverse_cleanup(traversal);
}
//
//void files_addFile(struct rzip_files *rzip, char *path) {
//
////	struct rzip_file *rzip_file = createFileItem(rzip, path);
//
//
//
//struct iterator *iterator = createFileItems(rzip, path);
//struct rzip_file *rzip_file;
//
//while (iterator_next(iterator, &rzip_file)) {
//	//while (iterator->next(iterator, rzip_file)) {
//
//	linkedList_add(rzip->rzip_files, rzip_file);
//
//	// configure offsets for newly added file
//	rzip_file->dataOffset = rzip->tmpOffset;
//	rzip->tmpOffset += rzip_file->fileLength;
//
//	rzip_file->dataEndByte = rzip_file->dataOffset + rzip_file->fileLength;
//}
//}

/**
 * Initialize a structure.
 */
struct rzip_files* files_initFiles() {

	struct rzip_files *rzip_files = malloc(sizeof(struct rzip_files));
	rzip_files->rzip_files = linkedList_init();
	rzip_files->decompressFilter = linkedList_init();
	rzip_files->decompressingItem = NULL;
	rzip_files->tmpOffset = 0;
	rzip_files->basePath = NULL;

	return rzip_files;
}

/**
 * Serialize a `struct rzip_file`, just fileLength and fileName
 */
void rzip_file_serialize(void *rzip_file, int fileDescriptor) {

	struct rzip_file *serialize = rzip_file;

	int64_t fileLength = htole64(serialize->fileLength);
	if (write(fileDescriptor, &fileLength, 8) != 8) {
		printf("Failed to write a fileLength of a rzip_file\n");
		exit(1);
	}

	__uint16_t fileNameLength = htole16(strlen(serialize->filePath));

	if (write(fileDescriptor, &fileNameLength, 2) != 2) {
		printf("Failed to write a fileNameLength of a rzip_file\n");
		exit(1);
	}

	if (write(fileDescriptor, serialize->filePath, fileNameLength)
			!= fileNameLength) {
		printf("Failed to write a fileName of a rzip_file\n");
		exit(1);
	}

}

/**
 * Deserialize a `struct rzip_file`, just fileLength and fileName
 */
struct rzip_file* rzip_file_deserialize(int fileDescriptor) {

	struct rzip_file *rzip_file = malloc(sizeof(struct rzip_file));

	if (read(fileDescriptor, &rzip_file->fileLength, 8) != 8) {
		printf("Failed to read a fileLength of rzip_file\n");
		exit(1);
	}
	rzip_file->fileLength = le64toh(rzip_file->fileLength);

	uint16_t fileNameLength;
	if (read(fileDescriptor, &fileNameLength, 2) != 2) {
		printf("Failed to read a fileNameLength of rzip_file\n");
		exit(1);
	}
	fileNameLength = le16toh(fileNameLength);

	rzip_file->filePath = malloc(sizeof(char) * fileNameLength + 1);
	if (read(fileDescriptor, rzip_file->filePath, fileNameLength)
			!= fileNameLength) {
		printf("Failed to read a fileName of rzip_file\n");
		exit(1);
	}

	// end of string
	rzip_file->filePath[fileNameLength] = 0;

	return rzip_file;
}

/**
 * Serialize `struct rzip_files`
 */
void files_serialize(struct rzip_files *rzipFiles, int fileDescriptor) {

	linkedList_serialize(rzipFiles->rzip_files, fileDescriptor,
			&rzip_file_serialize);

}



/**
 * comparator for a binarySearchTree of type `struct rzip_file *`
 * Comparing based on of offset of a file
 */
static int rzip_file_binary_tree_comparator(struct rzip_file *file1,
		struct rzip_file *file2) {

	int64_t *first = &file1->dataOffset;
	int64_t *second = &file2->dataOffset;

	// 0 or -1 or 1
	//return (*first > *second) - (*first < *second);
	return *first < *second ? -1 : *first > *second ? 1 : 0;
}

/**
 * Generate a binary search tree from sorted `struct rzip_file`
 */
static void generateBinarySearchTree(struct rzip_files *rzipFiles) {

	rzipFiles->decompressionTree=binarySearchTree_init(
			&rzip_file_binary_tree_comparator, rzipFiles->rzip_files);

}

/**
 * Deserialize `struct rzip_files` into a linkedList
 */
struct rzip_files* files_deserialize(struct rzip_files *rzipFiles,
		int fileDescriptor) {

	rzipFiles->rzip_files = linkedList_deserialize(fileDescriptor,
			(void*) &rzip_file_deserialize);

	// post process a data
	struct linked_list_item *listItem = rzipFiles->rzip_files->start;
	struct rzip_file *rzip_file;

	while (listItem != NULL) {

		addPathOffsets(rzipFiles, listItem->item);
		listItem = listItem->next;
	}

	generateBinarySearchTree(rzipFiles);

	return rzipFiles;

}


/**
 * Prepare an output files for a decompression
 */
static void prepareOutputFiles(struct rzip_files *rzip_files) {

	struct linked_list_item *listItem = rzip_files->rzip_files->start;
	struct rzip_file *rzip_file;

	while (listItem != NULL) {

		createWriteFileItem(rzip_files, listItem->item);
		listItem = listItem->next;
	}

	rzip_files->decompressingItem = rzip_files->rzip_files->start;
	rzip_files->tmpOffset = 0;
}

static void updateDestinationPath(struct rzip_files *rzip_files) {

	int64_t len = strlen(rzip_files->basePath);

	if (rzip_files->basePath[len - 1] != '/') {

		char *newStr = malloc(sizeof(char) * len + 2);
		strcpy(newStr, rzip_files->basePath);
		newStr[len] = '/';
		newStr[len + 1] = 0;
		free(rzip_files->basePath);
		rzip_files->basePath = newStr;
	}

}

void files_prepareDecompression(struct rzip_files *rzip_files) {

	updateDestinationPath(rzip_files);
	prepareOutputFiles(rzip_files);

	// initialize te first buffer
	files_mmapOffset(rzip_files->lowBuffer, 0);

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

int64_t remap_count = 0;

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
///**
// * find first mapping file
// * TODO: Replace it with a binary search tree
// */
//static struct linked_list_item* findFirstMappingFile(
//		struct rzip_files_buffer *buffer, int64_t offset) {
//
//	struct linked_list_item *listItem = buffer->origin->rzip_files->start;
////	buffer->rzip_files->start = NULL;
////	buffer->rzip_files->end = NULL;
//
//	while (listItem != NULL) {
//
//		struct rzip_file *rzip_fileItem = listItem->item;
//
//		if (rzip_fileItem->dataEndByte > offset) {
//
//			// found a start
////			buffer->rzip_files->start = listItem;
//			return listItem;
//		}
//
//		// move to the next file in the list
//		listItem = listItem->next;
//	}
//
//	printf("FATAL input buffer %lu out of range!\n", offset);
//	exit(1);
//
//	return NULL;
//}
/**
 * find first mapping file based on binary search tree
 */
inline static struct linked_list_item* findFirstMappingFile(
		struct rzip_files_buffer *buffer, int64_t offset) {

	struct linked_list_item *listItem = buffer->origin->rzip_files->start;
//	buffer->rzip_files->start = NULL;
//	buffer->rzip_files->end = NULL;

	while (listItem != NULL) {

		struct rzip_file *rzip_fileItem = listItem->item;

		if (rzip_fileItem->dataEndByte > offset) {

			// found a start
//			buffer->rzip_files->start = listItem;
			return listItem;
		}

		// move to the next file in the list
		listItem = listItem->next;
	}

	printf("FATAL input buffer %lu out of range!\n", offset);
	exit(1);

	return NULL;
}

/**
 * Remmap of files which are already mapped.
 */

inline void files_mapCached(struct rzip_files_buffer *buffer, int64_t offset) {

//	printf("Freeing buffer %s %d-%d\n", buffer->name, buffer->offset,
//			buffer->end);

	remap_count++;
	struct linked_list_item *rzip_file = findFirstMappingFile(buffer, offset);

	struct rzip_file *rzip_fileItem = rzip_file->item;

	buffer->buffer = rzip_fileItem->preMappedFile;
	buffer->offset = rzip_fileItem->dataOffset;
	buffer->length = rzip_fileItem->fileLength;
	buffer->end =  buffer->offset + buffer->length;
	buffer->rzip_file=rzip_file;

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
	rzip_files_buffer->offset = -1;
	rzip_files_buffer->length = 0;
	rzip_files_buffer->end = -1;

	return rzip_files_buffer;
}

inline bool files_isinBuffer(struct rzip_files_buffer *filesBuffer,
		int64_t offset) {

	return filesBuffer->offset <= offset && offset < filesBuffer->end;
}

/**
 * mmap `offset` into memory,
 * `buffer` - use this buffer to mmap offset `offset`,
 * unmap a buffer when needed
 */
inline struct rzip_files_buffer* files_mmapOffset(struct rzip_files_buffer *buffer, int64_t offset) {

	if (!files_isinBuffer(buffer, offset)) {

		// it is needed to remap a buffer
		//map(control, buffer, offset);
		files_mapCached(buffer, offset);
	}

	return buffer;
}

/**
 * Use a next file in an order,
 * because a lower buffer is sliding continuous buffer moving from start to the end
 */
void files_remapLower(struct rzip_files_buffer *buffer, int64_t offset) {

	if( buffer->offset <= offset) {

		if(offset >= buffer->end) {

			//remap, use a next item
			//struct linked_list_item *rzip_file = buffer->rzip_file->next;

			buffer->rzip_file=buffer->rzip_file->next;
			//struct rzip_file *rzip_fileItem = rzip_file->item;

			files_mapRzipItemToBuffer(buffer, buffer->rzip_file->item);
		}

	} else {

		printf("lower buffer not contiguous");
		exit(1);
	}
}

inline void files_mapRzipItemToBuffer(struct rzip_files_buffer *buffer, struct rzip_file *rzip_fileItem) {

//	printf("Freeing buffer %s %d-%d\n", buffer->name, buffer->offset,
//			buffer->end);

	remap_count++;
//	struct linked_list_item *rzip_file = findFirstMappingFile(buffer, offset);

	buffer->buffer = rzip_fileItem->preMappedFile;
	buffer->offset = rzip_fileItem->dataOffset;
	buffer->length = rzip_fileItem->fileLength;
	buffer->end =  buffer->offset + buffer->length;
	//buffer->rzip_file=rzip_file;

//	printf("Mapping buffer %s %d-%d, %d\n", buffer->name, buffer->offset,
//			buffer->end, offset);
}


/**
 * Read a byte from concatenated input on offset `offset`
 */
inline uint8_t files_getDirectBufferByte(struct rzip_files_buffer *buffer,
		int64_t offset) {

	//int64_t delta = offset - buffer->offset;
//	if (delta < 0 || delta >= buffer->length) {
//
//		printf("Out of buffer index!!!\n");
//		exit(1);
//		//fatal("Out of buffer index\n");
//	}
	return buffer->buffer[offset - buffer->offset];
}

inline uint8_t files_getManagedBufferByte(struct rzip_files_buffer *buffer, int64_t offset) {

	files_mmapOffset(buffer, offset);
//	int64_t delta = offset - buffer->offset;
//	if (delta < 0 || delta >= buffer->length) {
//
//		printf("Out of buffer index!!!\n");
//		exit(1);
//		//fatal("Out of buffer index\n");
//	}
	return buffer->buffer[offset - buffer->offset];
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

/**
 * Create a name ".files"
 */
char* files_createFilesHolderName(char *outFileName) {

	// .files
	return concatStrings(outFileName, ".files");
}

/**
 * Close file handles and free allocated memory
 */
static void cleanupFile(struct linked_list_item *listItem, void *rzip_file_void) {

	struct rzip_file *rzip_file = rzip_file_void;

	if (rzip_file->fileHandle >= 0) {

		close(rzip_file->fileHandle);
		rzip_file->fileHandle = -1;
	}

	if (rzip_file->preMappedFile != NULL) {
		munmap(rzip_file->preMappedFile, rzip_file->fileLength);
		rzip_file->preMappedFile = NULL;
	}

	if (rzip_file->filePath != NULL) {

		free(rzip_file->filePath);
		rzip_file->filePath = NULL;
	}
}

void files_cleanupFiles(struct rzip_files *rzip_files) {

	linkedList_cleanup(rzip_files->rzip_files, &cleanupFile);

	if (rzip_files->basePath != NULL) {
		free(rzip_files->basePath);
		rzip_files->basePath = NULL;
	}
}

/**
 * Get length of longest common prefix of two strings
 */
static int64_t getLongestPrefixLength(char *first, char *second) {

	int64_t i = 0;
	int64_t lastPathIndex = 0;

	while (true) {

		// go to the end of any string or first different character
		if (*first != *second || *first == 0 || *second == 0) {
			return lastPathIndex;
		}

		if (*first == '/') {
			lastPathIndex = i;
		}

		i++;
		first++;
		second++;
	}
}

/**
 * Get all files which have to be compressed and identify their longest common prefix path
 */
static void resolveBasePath(struct rzip_files *rzip_files) {

	struct linked_list_item *item = rzip_files->rzip_files->start;
	struct rzip_file *rzip_file;

	char *lastPath = NULL;
	int64_t longest = -1;

	char *parent;
	char *parent2;

	while (item != NULL) {

		rzip_file = item->item;

		parent = strdup(rzip_file->filePath);
		parent2 = dirname(parent);

		if (lastPath != NULL) {
			longest = files_min(getLongestPrefixLength(lastPath, parent2),
					longest);
		} else {

			// first inialization
			longest = strlen(parent2);
		}

		lastPath = strdup(parent2);

		free(parent);

		item = item->next;
	}

	if (longest > 0) {

		rzip_files->basePath = malloc(sizeof(char) * longest + 1);
		strncpy(rzip_files->basePath, lastPath, longest);
		rzip_files->basePath[longest] = 0;
	} else {

		rzip_files->basePath = "";
	}

	if (lastPath != NULL) {
		free(lastPath);
	}

}

static void relativizeFilePaths(struct rzip_files *rzip_files) {

	struct linked_list_item *item = rzip_files->rzip_files->start;
	struct rzip_file *rzip_file;

	char *path = NULL;

	while (item != NULL) {

		rzip_file = item->item;

		path = getLocalFileName(rzip_file->filePath, rzip_files->basePath);
		free(rzip_file->filePath);

		// replace a full path with a in-archive relative path
		rzip_file->filePath = path;
		item = item->next;
	}

}

/**
 * All files to be compressed were added, make a pre-compression preparation.
 */
void files_prepareCompression(struct rzip_files *rzip_files) {

	resolveBasePath(rzip_files);
	relativizeFilePaths(rzip_files);
}

inline int64_t files_min(int64_t a, int64_t b) {

	if (a < b) {
		return a;
	}
	return b;
}

inline int64_t files_max(int64_t a, int64_t b) {

	if (a > b) {
		return a;
	}
	return b;
}

