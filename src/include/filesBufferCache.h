/**
 * File buffer cache
 */
#ifndef SRC_FILES_BUFFER_CACHE_H_
#define SRC_FILES_BUFFER_CACHE_H_

#include "lrzip_private.h"
#include "files.h"


extern i64 fileCache_copyRange_count;

void fileCache_init(struct rzip_files *rzip_files);


uchar fileCache_getByte(rzip_control *control, i64 offset);

/**
 * copy input data range of `offset` and `len` to a buffer `destinationBuffer`
 */
void fileCache_copyRange(rzip_control *control, unsigned char *destinationBuffer, i64 offset, i64 len);


#endif /* SRC_FILES_BUFFER_CACHE_H_ */
