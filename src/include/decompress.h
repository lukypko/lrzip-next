/*
 * files.h
 *
 *  Created on: Sep 24, 2022
 *      Author: luky
 */

#ifndef SRC_DECOMPRESS_H_
#define SRC_DECOMPRESS_H_

#include <stdbool.h>
#include <files.h>

#include "lrzip_private.h"


/**
 * Add list of files/folder/regexp which have to be extracted from the archive
 */
void decompress_addFilter(struct rzip_files *rzip, char *filterElement);

#endif /* SRC_DECOMPRESS_H_ */
