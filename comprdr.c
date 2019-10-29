/*

 * COMP40 HW4

 * Claire Boals & Ethan Oliver

 *

 * comprdr.c

 */


#include "comprdr.h"
#include "datastructs.h"
#include "wordpack.h"

void readin(int i, int j, UArray2_T image, void *elem, void *fp);
void write(int i, int j, UArray2_T image, void *elem, void *fp);

/* Apply function that builds words byte by byte and prepares video
   pixel array in each block */
void readin(int i, int j, UArray2_T image, void *elem, void *fp)
{
        (void)i;
        (void)j;
        (void)image;

        uint64_t word = 0;
        for(int i = 3; i >= 0; i--){

               word = put_bite(word, getc(fp),  i);
        }
        Block block = elem;
        block->pixel_block[0] = malloc(sizeof(struct Vpixel));
        block->pixel_block[1] = malloc(sizeof(struct Vpixel));
        block->pixel_block[2] = malloc(sizeof(struct Vpixel));
        block->pixel_block[3] = malloc(sizeof(struct Vpixel));
        block->word = word;
}

/* Apply function that writes words byte by byte */
void write(int i, int j, UArray2_T image, void *elem, void *cl)
{
        (void)i;
        (void)j;
        (void)image;
        (void)cl;
        Block curr = elem;

        uint64_t word = curr->word;


        for(int i = 3; i >= 0; i--){

                putchar(get_bite(word, i));
        }
}

/* Driver for reading compressed images into an array of 2x2 blocks of pixels */
UArray2_T compress_read(FILE *fp)
{
        unsigned width, height;
        int read = fscanf(fp, "COMP40 Compressed image format 2\n%u %u",
                                &width, &height);
        assert(read == 2);
        int c = getc(fp);
        assert(c == '\n');

        UArray2_T blocks = UArray2_new(width/2, height/2, sizeof(struct Block));
        UArray2_map_row_major(blocks, readin, fp);

        return blocks;
}

/* Driver for writing compressed images */
void compress_write(UArray2_T blocks, int width, int height)
{
        printf("COMP40 Compressed image format 2\n%d %d\n", width, height);
        UArray2_map_row_major(blocks, write, NULL);

}
