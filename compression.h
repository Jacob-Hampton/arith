#include <stdlib.h>
#include "compress40.h"
#include "datastructs.h"
#include <a2methods.h>
#include <pnm.h>
#include "uarray2.h"

UArray2_T compress(Pnm_ppm image);
//Takes a Pnm_ppm image and returns the compressed version of that image.

UArray2_T trim_convert(Pnm_ppm image);
//Takes a Pnm_ppm image, trims it if necessary,
//and puts Y, Pb, and Pr values into a 2D array of pixels

UArray2_T write_to_blocks (UArray2_T pixelvideo);
//Takes a 2D array of pixels (Y, Pb, and Pr values) and returns an array
//of block structs that contain 2x2 arrays of pixels

void compress_block (Block bp);
//Takes a block struct (2x2 of pixels)
//and modifies the block by calling the compression functions

void dct(Block bp);
//Takes a block struct and modifies the block with its DCT values

void average_p(Block bp);
//Takes a block and modifies the block with
//its Pb and Pr values for each pixel averaged

Vpixel rgb_to_video(Pnm_rgb pixel);
//Takes a Pnm_rgb struct and returns a
//struct with the component video conversion
