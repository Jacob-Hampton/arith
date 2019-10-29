#include "compression.h"
#include "datastructs.h"
#include "decompression.h"
#include "quantizer.h"
#include "wordpack.h"
#include <math.h>


void compress_blocks(int i, int j, UArray2_T array, void * element, void * cl){

        (void)i;
        (void)j;
        (void)array;
        (void)cl;
        

         Block block = (element);

        // (void)block;
         dct(block);
         average_p(block);

        pack_block(block);

}




UArray2_T compress(Pnm_ppm image)
{

        UArray2_T videopixels = trim_convert(image);

        UArray2_T blocks = write_to_blocks(videopixels);

        UArray2_map_row_major(blocks, compress_blocks, NULL);


        //(void)videopixels;
        //UArray2_T blocks = write_to_blocks(videopixels);
        //UArray2_map on blocks to call math functions and call Wordpack functions
        //return blocks;
        return blocks;
}






//Takes a Pnm_ppm image and returns the compressed version of that image.

const float Ry = 0.299;
const float Gy = 0.587;
const float By = 0.114;

const float Rb = -0.168736;
const float Gb = -0.331264;
const float Bb = 0.5;

const float Rr = 0.5;
const float Gr = -0.418688;
const float Br = -0.081312;

UArray2_T trim_convert(Pnm_ppm image)
{
         fprintf(stderr, "%s\n", "trim" );
        int width = image->width;
        int height = image->height;
        if (image->width % 2 != 0){
                width = image->width - 1;
        }
        if (image->height % 2 != 0){
                height = image->height - 1;
        }

        UArray2_T vimage = UArray2_new(width, height, sizeof(struct Vpixel));
        float red, green, blue;
        float denominator = image->denominator;

        for (int row = 0; row < width; row++){
                for (int col = 0; col < height; col++){
                        Pnm_rgb curr = image->methods->at(image->pixels, row, col);
                        Vpixel pix = (Vpixel)UArray2_at(vimage, row, col);
                        red = (float)curr->red /denominator;
                        green = (float)curr->green / denominator;
                        blue = (float)curr->blue/ denominator; 



                        pix->y = Ry*red + Gy*green + By*blue;
                        pix->pb = Rb*red + Gb*green + Bb*blue;
                        pix->pr = Rr*red + Gr*green + Br*blue;

                    

                        // fprintf(stderr,"y: %f, pb: %f, pr: %f\n", pix->y, pix->pb, pix->pr);
                        // fprintf(stderr,"r: %f, g: %f, b: %f\n", red, green, blue);

                }
        }
        return vimage;
}
//Takes a Pnm_ppm image, trims it if necessary,
//and puts Y, Pb, and Pr values into a 2D array of pixels

UArray2_T write_to_blocks (UArray2_T pixelvideo)
{

         fprintf(stderr, "%s\n", "write_to_blocks" );
        int width = UArray2_width(pixelvideo)/2;
        int height = UArray2_height(pixelvideo)/2;
        UArray2_T blocks = UArray2_new(width, height, sizeof(struct Block));

        for (int row = 0; row < width; row++){
                for (int col = 0; col < height; col++){
                        Block b = (Block)UArray2_at(blocks, row, col);

                        b->pixel_block[0] = (Vpixel) UArray2_at(pixelvideo, row*2, col*2);
                        b->pixel_block[1] = (Vpixel) UArray2_at(pixelvideo, row*2, col*2+1);
                        b->pixel_block[2] = (Vpixel) UArray2_at(pixelvideo, row*2+1, col*2);
                        b->pixel_block[3] = (Vpixel) UArray2_at(pixelvideo, row*2+1, col*2+1);

                //          fprintf(stderr, "Pixel block: %f\n", b->pixel_block[0]->y);
                }
        }

        return blocks;
}
//Takes a 2D array of pixels (Y, Pb, and Pr values) and returns an array
//of block structs that contain 2x2 arrays of pixels
const float DIV = 4.0;

void dct(Block bp)
{
        

        float y1 = bp->pixel_block[0]->y;
        float y2 = bp->pixel_block[1]->y;
        float y3 = bp->pixel_block[2]->y;
        float y4 = bp->pixel_block[3]->y;

        // fprintf(stderr, " Unquantized a: %f b: %f c: %f d: %f \n",(y4 + y3 + y2 + y1)/DIV,
         //   (y4 + y3 - y2 - y1)/DIV,  (y4 - y3 + y2 - y1)/DIV, (y4 - y3 - y2 + y1)/DIV  );


        bp->a = round(511.0f *  (y4 + y3 + y2 + y1)/DIV);
        bp->b =  bcd_quantize((y4 + y3 - y2 - y1)/DIV);
        bp->c = bcd_quantize((y4 - y3 + y2 - y1)/DIV);
        bp->d = bcd_quantize((y4 - y3 - y2 + y1)/DIV);

        // fprintf(stderr, "Quantized a: %lu b: %li c: %li d: %li \n", bp->a, bp->b,bp->c,bp->d  );
 
}
//Takes a block struct and modifies the block with its DCT values

void average_p(Block bp)
{
       float pb1 = bp->pixel_block[0]->pb;
        float pb2 = bp->pixel_block[1]->pb;
        float pb3 = bp->pixel_block[2]->pb;
        float pb4 = bp->pixel_block[3]->pb;


         float pr1 = bp->pixel_block[0]->pr;
        float pr2 = bp->pixel_block[1]->pr;
        float pr3 = bp->pixel_block[2]->pr;
        float pr4 = bp->pixel_block[3]->pr;



    float pb_avg = (pb1 + pb2 + pb3  + pb4)/DIV;
    float pr_avg = (pr1 + pr2 + pr3  + pr4)/DIV;

    // fprintf(stderr, "PB float: %f\n", pb_avg );
    // fprintf(stderr, "PR float: %f\n",pr_avg );

    bp->pb_avg = p_quantize(pb_avg);
    bp->pr_avg = p_quantize(pr_avg);

     //    fprintf(stderr, "PB Quant: %li\n", bp->pb_avg  );
     // fprintf(stderr, "PR Quant: %li\n",bp->pr_avg  );


}
// //Takes a block and modifies the block with
// //its Pb and Pr values for each pixel averaged

// Vpixel rgb_to_video(Pnm_rgb pixel)
// {

// }
// Takes a Pnm_rgb struct and returns a
// struct with the component video conversion
