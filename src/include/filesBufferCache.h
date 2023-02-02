/**
 * File buffer cache
 */
#ifndef SRC_FILES_BUFFER_CACHE_H_
#define SRC_FILES_BUFFER_CACHE_H_

#include "lrzip_private.h"
#include "files.h"
#include <stdbool.h>

extern uint64_t fileCache_readRange_count;

void fileCache_init(struct rzip_files *rzip_files);


uint8_t fileCache_getByte(struct rzip_files *rzip_files, int64_t offset);

/**
 * copy input data range of `offset` and `len` to a buffer `destinationBuffer`
 */
int64_t fileCache_readRange(rzip_control *control,
		uint8_t *destinationBuffer, int64_t offset, int64_t len);

int64_t fileCache_writeRange(struct rzip_files *rzip_files,
		uint8_t *sourceBuffer, int64_t len);


struct rzip_files_buffer* fileCache_remapBuffer(struct rzip_files *rzip_files, int64_t offset);

/**
 * Get a byte on a `offset`
 * `direct` - true, direct access without checking a buffer range
 * 			- false, check a buffer range and find a new buffer if needed
 */
uint8_t fileCache_getBufferByte(struct rzip_files_buffer *buffer, int64_t offset, bool direct);

#endif /* SRC_FILES_BUFFER_CACHE_H_ */
