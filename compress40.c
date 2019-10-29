#include "compress40.h"
#include "decomprdr.h"
#include "pnm.h"
#include "compression.h"
#include "decompression.h"
#include "comprdr.h"


extern void compress40(FILE *fp)
{
        Pnm_ppm image = decompress_read(fp);
        UArray2_T blocks = compress(image);

        int width = UArray2_width(blocks);
        int height = UArray2_height(blocks);


        compress_write(blocks, width *2, height * 2 );


         // Pnm_ppm image2 = decompress(blocks);

         // decompress_write(image2, stdout);

}

extern void decompress40(FILE *fp)
{
        UArray2_T blocks = compress_read(fp);

        Pnm_ppm image = decompress(blocks);
        decompress_write(image, stdout);
}
