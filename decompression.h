#include <stdlib.h>
#include "compress40.h"
#include "datastructs.h"
#include <a2methods.h>
#include <a2plain.h>
#include <pnm.h>
#include "uarray2.h"

Pnm_ppm decompress(UArray2_T blocks);
//Takes a compressed image and returns the decompressed version as a Pnm_ppm image

void decompress_block (Block bp);

void inverse_pavg(Block bp);
//Takes a block of pixels and performs the decompression steps on the data

void inverse_dct(Block bp);
//Takes a block of pixels and performs the inverse DCT math on the data

UArray2_T write_to_video (UArray2_T blocks);
//Takes a 2D array of 2x2 blocks of pixels into an array of component video pixels

//Pnm_rgb_float video_to_rgb_float(UArray2_T pixel_video);
//Takes an array of pixel_video pixels, converts them to RGB, and writes them to a Pnm_rgb_float struct

Pnm_ppm write_to_image(UArray2_T Pnm_rgb_float, float denominator);
//Takes an array of Pnm_rgb_floats, quantizes the values, and writes to Pnm_rgb structs in a Pnm_ppm image
