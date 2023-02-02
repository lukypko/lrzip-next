/*
 * filesBufferCache.c
 *
 *  Created on: Oct 18, 2022
 *      Author: luky
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "linkedList.h"
#include "filesBufferCache.h"

void fileCache_init(struct rzip_files *rzip_files) {

	rzip_files->lowBuffer = files_init_rzip_files_buffer(rzip_files);
	rzip_files->lowBuffer->name = "low";

	rzip_files->highBuffer = files_init_rzip_files_buffer(rzip_files);
	rzip_files->highBuffer->name = "high";


	rzip_files->bufferMatchLen1 = files_init_rzip_files_buffer(rzip_files);
	rzip_files->bufferMatchLen2 = files_init_rzip_files_buffer(rzip_files);
	rzip_files->bufferMatchLen3 = files_init_rzip_files_buffer(rzip_files);
	rzip_files->bufferMatchLen4 = files_init_rzip_files_buffer(rzip_files);

	rzip_files->bufferReadRange= files_init_rzip_files_buffer(rzip_files);

	rzip_files->bufferNextTag1= files_init_rzip_files_buffer(rzip_files);
	rzip_files->bufferNextTag2= files_init_rzip_files_buffer(rzip_files);

	rzip_files->bufferFullTag= files_init_rzip_files_buffer(rzip_files);
}

inline struct rzip_files_buffer* fileCache_remapBuffer(struct rzip_files *rzip_files, int64_t offset) {

	if (files_isinBuffer(rzip_files->lowBuffer, offset)) {
		return rzip_files->lowBuffer;
	} else {

		files_mmapOffset(rzip_files->highBuffer, offset);
		return rzip_files->highBuffer;
	}
}

inline uint8_t fileCache_getByte(struct rzip_files *rzip_files, int64_t offset) {

	struct rzip_files_buffer *buffer = fileCache_remapBuffer(rzip_files, offset);
	return files_getDirectBufferByte(buffer, offset);
}

uint64_t fileCache_readRange_count = 0;

/**
 * read (copy) input data range of `offset` and `len` to a buffer `destinationBuffer`
 */
int64_t fileCache_readRange(rzip_control *control,
		uint8_t *destinationBuffer, int64_t offset, int64_t len) {

	//struct rzip_files *rzip_files=control->rzip_files;
	fileCache_readRange_count++;


//	memcpy(buf + n, srcbuf, m);
	int64_t i;

//	i64 index;
//	for (i = 0; i < len; i++) {
//
//		index = offset + i;
//
//		struct rzip_files_buffer *buffer = remapBuffer(control, index);
//		destinationBuffer[i] = files_getDirectBufferByte(control, buffer,
//				index);
//	}

	uint64_t sourceAddr;
	for (i = 0; i < len;) {

		sourceAddr = offset + i;
		files_mmapOffset(control->rzip_files->bufferReadRange, sourceAddr);
		//struct rzip_files_buffer *buffer = fileCache_remapBuffer(rzip_files, sourceAddr);

		int64_t start = sourceAddr - control->rzip_files->bufferReadRange->offset;
		int64_t availableBuffer = files_min(control->rzip_files->bufferReadRange->end - sourceAddr, len - i);
		if(availableBuffer==0) {
			printf("fileCache_readRange: availableBuffer==0\n");
		}

		memcpy(destinationBuffer + i, control->rzip_files->bufferReadRange->buffer + start, availableBuffer);
		i += availableBuffer;
	}

	return i;
}

/*

static i64 sliding_full_tag2_count=0;
static tag sliding_full_tag3(rzip_control *control, struct rzip_state *st,
		i64 p) {
	tag ret = 0;
	int i;
	uint8_t u;

	sliding_full_tag2_count++;
	for (i = 0; i < MINIMUM_MATCH; i++) {
		struct rzip_files_buffer *buffer = fileCache_remapBuffer(control->rzip_files,
				p + i);
		int64_t availableBuffer = files_min(buffer->end - p, MINIMUM_MATCH - i);
		for (; availableBuffer > 0; availableBuffer--) {

			u = files_getDirectBufferByte(buffer, p + i);
			ret ^= st->hash_index[u];
			i++;
		}
	}

	return ret;
}
*/



/**
 * read (copy) input data range of `offset` and `len` to a buffer `destinationBuffer`
 */
int64_t fileCache_readRange2(struct rzip_files *rzip_files,
		uint8_t *destinationBuffer, int64_t offset, int64_t len) {

// TODO: this is a low performance implementation

	fileCache_readRange_count++;

	int64_t i;

	uint64_t sourceAddr;
	for (i = 0; i < len;) {

		sourceAddr = offset + i;
		struct rzip_files_buffer *buffer = fileCache_remapBuffer(rzip_files, sourceAddr);

		int64_t start = sourceAddr - buffer->offset;
		int64_t availableBuffer = files_min(buffer->end - sourceAddr, len - i);

		memcpy(destinationBuffer + i, buffer->buffer + start, availableBuffer);
		i += availableBuffer;
	}

	return i;

}


uint64_t fileCache_writeRange_count = 0;

/**
 * write (copy) input data range to contiguous output file of length `len`
 */
int64_t fileCache_writeRange(struct rzip_files *rzip_files,
		uint8_t *sourceBuffer, int64_t len) {

	fileCache_writeRange_count++;

	int64_t lengthToWrite;
	int64_t written=0;

	struct rzip_file *rzip_file;

	while (len > 0) {

		rzip_file = rzip_files->decompressingItem->item;
		lengthToWrite = files_min(rzip_file->dataEndByte - rzip_files->tmpOffset, len);

		if (lengthToWrite > 0) {

			//write
			if (write(rzip_file->fileHandle, sourceBuffer, lengthToWrite)
					!= lengthToWrite) {
				printf("Failed to write a data to a file '%s'\n",
						rzip_file->filePath);
				exit(1);
			}

			sourceBuffer += lengthToWrite;
			len -= lengthToWrite;
			written+=lengthToWrite;
			rzip_files->tmpOffset+=lengthToWrite;

		} else {

			// move to next file
			rzip_files->decompressingItem = rzip_files->decompressingItem->next;
		}
	}

	return written;

}

inline uint8_t fileCache_getBufferByte(struct rzip_files_buffer *buffer, int64_t offset, bool direct) {

	// lower buffer is not remapped, when a value is not in a provided buffer,
	// then buffer is remapped as higher buffer

	if(!(direct || files_isinBuffer(buffer, offset))) {

		files_mapCached(buffer, offset);
	}

	if (!files_isinBuffer(buffer, offset)) {

		printf("Out of buffer index!!!\n");
		exit(1);
	}

	return buffer->buffer[offset - buffer->offset];
}
