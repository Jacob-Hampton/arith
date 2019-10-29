#ifndef DECOMPPRESS_READER
#define DECOMPPRESS_READER

#include "pnm.h"
#include <stdio.h>
#include <stdlib.h>
#include <a2methods.h>
#include <a2plain.h>

Pnm_ppm decompress_read(FILE *);
void decompress_write(Pnm_ppm image, FILE *);

#endif
