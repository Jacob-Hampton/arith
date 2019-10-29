#ifndef STRUCTS
#define STRUCTS

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>



typedef struct Vpixel {

        float y;
        float pb;
        float pr;
} *Vpixel;


typedef struct Block {

        Vpixel pixel_block[4];

        uint64_t pb_avg;
        uint64_t pr_avg;

        uint64_t a;
        int64_t b, c, d;


        uint64_t word;


} *Block;




#endif
