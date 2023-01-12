/*
 * files.h
 *
 *  Created on: Sep 24, 2022
 *      Author: luky
 */

#ifndef SRC_FILES_FILES_H_
#define SRC_FILES_FILES_H_

#include <stdbool.h>

#include "lrzip_private.h"

extern i64 remap_count;

/**
 * Files mapping
 */
struct rzip_files {

	/**
	 * List of files
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

	/**
	 * Current offset, used when adding files into archive to compute offset of a next file.
	 */
	i64 tmpOffset;

	/**
	 * MMap all files to a virtual memory
	 */
	bool premapFiles;
};

struct rzip_file_list {

	/**
	 * Count of files.
	 */
	long count;
	struct rzip_file_list *next;
};

struct rzip_file {

	/**
	 * offset of this file in a resulting compressed file.
	 */
	i64 dataOffset;

	/**
	 * Length of file in bytes.
	 */
	i64 fileLength;

	/**
	 * This is `dataOffset` + `fileLength` just to improve a performance.
	 */
	i64 dataEndByte;

	/**
	 * Some extended file attributes, like
	 * - creation/modification time
	 * - owner of file
	 */
	i64 fileAttributes;

	bool isFolder;

	/**
	 * In archive relative file path
	 */
	char *filePath;

//	/**
//	 * Handle to a file opened for random access reading.
//	 */
//	int fileHandle;


	/**
	 * File to memory mmap-ed buffer (in case if a file is premmaped into a memory
	 */
	uchar *preMappedFile;
};

/**
 * Sliding buffer
 */
struct rzip_files_buffer {

	/**
	 * offset of a memory buffer
	 * aligned to system `page_size` of first file `rzip_fileItem`
	 */
	i64 offset;

	/**
	 * Length of mmap buffer
	 * TODO: does it make a sence to make it larger?
	 */
	i64 length;

	/**
	 * offset+length
	 */
	i64 end;

	/**
	 * File to memory mmap-ed buffer
	 */
	uchar *buffer;

	/**
	 * Origin of this buffer.
	 */
	struct rzip_files *origin;

	/**
	 * First file.
	 * I guess it is not needed to map all files, because:
	 * - there are not so many files, and locating a correct file to map is fast
	 */
	struct rzip_file *rzip_fileItem;

	/**
	 * List of files which are mapped for this buffer,
	 * this is a sublist of original "all file list".
	 */
	struct linked_list *rzip_files;

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
 */
void files_addFile(struct rzip_files *rzip, char *path);

/**
 * Close all files.
 */
void closeFiles(struct rzip_files *rzip_files);

/**
 * Deallocate memory objects.
 */
void cleanupFiles(struct rzip_files *rzip_files);

//void mmapinput(rzip_control *control, i64 offset, i64 len);
//void mmapinput(rzip_control *control, struct rzip_files_buffer *buffer);
//
//void munmapinput(rzip_control *control, i64 offset, i64 len);

/**
 * Get a single byte of input data on a offset `offset` using a `buffer`.
 * If needed a `buffer` is remapped.
 */
uchar files_getBufferByte(rzip_control *control,
		struct rzip_files_buffer *buffer, i64 offset);

uchar files_getByte(rzip_control *control, i64 offset);

/**
 * copy input data range of `offset` and `len` to a buffer `buf`
 */
void files_copyRange(rzip_control *control, unsigned char *buf, i64 offset,
		i64 len);

struct rzip_files_buffer* files_init_rzip_files_buffer(
		struct rzip_files *rzip_files);

bool files_isinBuffer(rzip_control *control, struct rzip_files_buffer *buffer,
		i64 offset);

void files_mmapOffset(rzip_control *control, struct rzip_files_buffer *buffer,
		i64 offset);

uchar files_getDirectBufferByte(rzip_control *control,
		struct rzip_files_buffer *buffer, i64 offset);

#endif /* SRC_FILES_FILES_H_ */
