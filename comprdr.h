/*

 * COMP40 HW4

 * Claire Boals & Ethan Oliver

 *

 * comprdr.h

 */


#ifndef COMPPRESS_READER
#define COMPPRESS_READER

#include "pnm.h"
#include <stdio.h>
#include <stdlib.h>
#include "uarray2.h"
#include <stdint.h>
#include <assert.h>

void compress_write(UArray2_T blocks, int width, int height);

UArray2_T compress_read(FILE *fp);



#endif
