/*
 * files.h
 *
 *  Created on: Sep 24, 2022
 *      Author: luky
 */

#ifndef SRC_FILES_FILES_H_
#define SRC_FILES_FILES_H_

#include <stdbool.h>
#include <stdint.h>

//#include "lrzip_private.h"

extern int64_t remap_count;

/**
 * Files mapping
 */
struct rzip_files {

	/**
	 * List of files of type `struct rzip_file*`
	 */
	struct linked_list *rzip_files;

	/**
	 * First priority buffer.
	 */
	struct rzip_files_buffer *lowBuffer;

	/**
	 * Second priority buffer.
	 * Buffer is remapped when needed.
	 */
	struct rzip_files_buffer *highBuffer;


	struct rzip_files_buffer *bufferMatchLen1;
	struct rzip_files_buffer *bufferMatchLen2;
	struct rzip_files_buffer *bufferMatchLen3;
	struct rzip_files_buffer *bufferMatchLen4;

	struct rzip_files_buffer *bufferReadRange;

	struct rzip_files_buffer *bufferNextTag1;
	struct rzip_files_buffer *bufferNextTag2;

	struct rzip_files_buffer *bufferFullTag;




	/**
	 * List of files/regexp which have to be extracted from archive
	 * linked_list of `char*`
	 * This is possible only when file in not compressed
	 */
	struct linked_list *decompressFilter;

	/**
	 * When decompressing a full archive, then this is current output file
	 * type `struct rzip_file*`
	 */
	struct linked_list_item *decompressingItem;

	/**
	 * Base path to compute a relative in-archive file name
	 */
	char *basePath;

	/**
	 * Current offset, used when adding files into archive to compute offset of a next file.
	 */
	int64_t tmpOffset;


	/**
	 * Tree used to a quick search of file based on if source offset.
	 * Item type `struct rzip_file *`
	 */
	struct binary_search_tree *decompressionTree;

	/**
	 * reference to a function to get a mapping file,
	 * implementations are linkedList or binarySearchTree based on items count
	 */
	struct rzip_file* (*findMappingFile)(struct rzip_files_buffer *buffer, int64_t offset);


//	/**
//	 * MMap all files to a virtual memory
//	 */
//	bool premapFiles;
};


struct rzip_file {

	/**
	 * offset of this file in a resulting compressed file.
	 */
	int64_t dataOffset;

	/**
	 * Length of file in bytes.
	 */
	int64_t fileLength;

	/**
	 * This is `dataOffset` + `fileLength` just to improve a performance.
	 */
	int64_t dataEndByte;

	/**
	 * Some extended file attributes, like
	 * - creation/modification time
	 * - owner of file
	 */
	int64_t fileAttributes;

	bool isFolder;

	/**
	 * In archive relative file path
	 */
	char *filePath;

	/**
	 * Handle to a file opened for random access reading.
	 */
	int fileHandle;


	/**
	 * File to memory mmap-ed buffer (in case if a file is premmaped into a memory
	 */
	uint8_t *preMappedFile;
};

/**
 * Sliding buffer
 */
struct rzip_files_buffer {

	/**
	 * offset of a memory buffer
	 * aligned to system `page_size` of first file `rzip_fileItem`
	 */
	int64_t offset;

	/**
	 * Length of mmap buffer
	 * TODO: does it make a sence to make it larger?
	 */
	int64_t length;

	/**
	 * offset+length
	 */
	int64_t end;

	/**
	 * File to memory mmap-ed buffer
	 */
	uint8_t *buffer;

	/**
	 * Origin of this buffer.
	 */
	struct rzip_files *origin;

//	/**
//	 * Which file from rzip_files is this buffer mapped from.
//	 * For 64-bit systems it is 1:1 mapping,
//	 * but for 32-bit system one large file (>2GB) is mapped into multiple buffers (as it is not possible to mmap >2GB files)
//	 *
//	 * Type of `struct rzip_file *`
//	 */
//	struct linked_list_item *rzip_file;

	/**
	 * First file.
	 * I guess it is not needed to map all files, because:
	 * - there are not so many files, and locating a correct file to map is fast
	 */
//	struct rzip_file *rzip_fileItem;

	/**
	 * List of files which are mapped for this buffer,
	 * this is a sublist of original "all file list".
	 */
//	struct linked_list *rzip_files;

	/**
	 * Buffer name (just for a debug purpose)
	 */
	char* name;
};

void getFile();

/**
 * Initialize a structure.
 */
struct rzip_files* files_initFiles();

/**
 * Add a file or folder to compress.
 * `path` - file or a folder path
 * if it is a folder, then all folder files are processed recursively
 * TODO: in case if there are multiple paths, their internal (relative) path
 * can be resolved into the same file names (which must be unique)
 */
void files_addPath(struct rzip_files *rzip, char *path);


/**
 * Deallocate memory objects.
 */
void files_cleanupFiles(struct rzip_files *rzip_files);

//void mmapinput(rzip_control *control, i64 offset, i64 len);
//void mmapinput(rzip_control *control, struct rzip_files_buffer *buffer);
//
//void munmapinput(rzip_control *control, i64 offset, i64 len);

/**
 * Get a single byte of input data on a offset `offset` using a `buffer`.
 * If needed a `buffer` is remapped.
 */
uint8_t files_getBufferByte(
		struct rzip_files_buffer *buffer, int64_t offset);

uint8_t files_getByte(int64_t offset);

/**
 * copy input data range of `offset` and `len` to a buffer `buf`
 */
void files_copyRange(unsigned char *buf, int64_t offset,
		int64_t len);

struct rzip_files_buffer* files_init_rzip_files_buffer(
		struct rzip_files *rzip_files);

bool files_isinBuffer(struct rzip_files_buffer *buffer,
		int64_t offset);

struct rzip_files_buffer* files_mmapOffset(struct rzip_files_buffer *buffer, int64_t offset);

uint8_t files_getDirectBufferByte(struct rzip_files_buffer *buffer, int64_t offset);
uint8_t files_getManagedBufferByte(struct rzip_files_buffer *buffer, int64_t offset);


void files_mapCached(struct rzip_files_buffer *buffer,
		int64_t offset);

/**
 * Serialize `struct rzip_files`
 */
void files_serialize(struct rzip_files *rzipFiles, int fileDescriptor);

/**
 * Deserialize `struct rzip_files`
 */
struct rzip_files* files_deserialize(struct rzip_files *rzipFiles, int fileDescriptor);

char* files_createFilesHolderName(char *outFileName);

void files_prepareDecompression(struct rzip_files *rzip_files);
void files_prepareCompression(struct rzip_files *rzip_files);

int64_t files_min(int64_t a, int64_t b);
int64_t files_max(int64_t a, int64_t b);

//void files_remapLower(struct rzip_files_buffer *buffer, int64_t offset);

#endif /* SRC_FILES_FILES_H_ */
