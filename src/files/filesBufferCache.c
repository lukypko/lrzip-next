/*
 * filesBufferCache.c
 *
 *  Created on: Oct 18, 2022
 *      Author: luky
 */

#include "filesBufferCache.h"

void fileCache_init(struct rzip_files *rzip_files) {

	rzip_files->lowBuffer = files_init_rzip_files_buffer(rzip_files);
	rzip_files->lowBuffer->name = "low";

	rzip_files->highBuffer = files_init_rzip_files_buffer(rzip_files);
	rzip_files->highBuffer->name = "high";
}

static inline struct rzip_files_buffer* remapBuffer(rzip_control *control,
		i64 offset) {

	if (files_isinBuffer(control, control->rzip_files->lowBuffer, offset)) {
		return control->rzip_files->lowBuffer;
	} else {

		files_mmapOffset(control, control->rzip_files->highBuffer, offset);
		return control->rzip_files->highBuffer;
	}
}

inline uchar fileCache_getByte(rzip_control *control, i64 offset) {

	struct rzip_files_buffer *buffer = remapBuffer(control, offset);
	return files_getDirectBufferByte(control, buffer, offset);
}

i64 fileCache_copyRange_count = 0;
/**
 * copy input data range of `offset` and `len` to a buffer `destinationBuffer`
 */
void fileCache_copyRange(rzip_control *control,
		unsigned char *destinationBuffer, i64 offset, i64 len) {

// TODO: this is a low performance implementation

	fileCache_copyRange_count++;

//	memcpy(buf + n, srcbuf, m);
	i64 i;

//	i64 index;
//	for (i = 0; i < len; i++) {
//
//		index = offset + i;
//
//		struct rzip_files_buffer *buffer = remapBuffer(control, index);
//		destinationBuffer[i] = files_getDirectBufferByte(control, buffer,
//				index);
//	}

	i64 sourceAddr;
	for (i = 0; i < len;) {

		sourceAddr = offset + i;
		struct rzip_files_buffer *buffer = remapBuffer(control, sourceAddr);

		i64 start = sourceAddr - buffer->offset;
		i64 availableBuffer = MIN(buffer->end - sourceAddr, len - i);

		memcpy(destinationBuffer + i, buffer->buffer + start, availableBuffer);
		i += availableBuffer;
	}

}
