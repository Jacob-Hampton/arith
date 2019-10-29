#include "decomprdr.h"
#include "pnm.h"

Pnm_ppm decompress_read(FILE *fp)
{
        return Pnm_ppmread(fp, uarray2_methods_plain);
}

void decompress_write(Pnm_ppm image, FILE *fp)
{
        Pnm_ppmwrite(fp, image);
}
