#include "decompression.h"
#include "quantizer.h"
#include "wordpack.h"


void decompress_blocks(int i, int j, UArray2_T array, void * element, void * cl){

        (void)i;
        (void)j;
        (void)array;
        (void)cl;


        Block block = element;
   
         unpack_block(block);
         inverse_dct(block);
         inverse_pavg(block);



}


Pnm_ppm decompress(UArray2_T blocks){




         UArray2_map_row_major(blocks, decompress_blocks, NULL);


        UArray2_T vpixels = write_to_video(blocks);

        Pnm_ppm image2 = write_to_image(vpixels, 100);



       
        return image2;

}


void inverse_dct(Block bp){

      float a = bp->a / 511.0f ;
      
      float b =  bcd_unquantize(bp->b);
      float c = bcd_unquantize(bp->c);
      float d = bcd_unquantize(bp->d);


      // fprintf(stderr, "Unquantized: a: %f b: %f c: %f d: %f\n", a, b, c, d );




        bp->pixel_block[0]->y = a - b - c + d;
        bp->pixel_block[1]->y = a - b + c - d;
        bp->pixel_block[2]->y = a + b - c - d;
        bp->pixel_block[3]->y = a + b + c + d;

}



void inverse_pavg(Block bp){

    float pb_avg = p_unquantize(bp->pb_avg);
    float pr_avg = p_unquantize(bp->pr_avg);
    
    // fprintf(stderr, "PB UNQUANT: %f\n", pb_avg );
    // fprintf(stderr, "PR UNQUANT: %f\n",pr_avg );


        bp->pixel_block[0]->pb = pb_avg;
        bp->pixel_block[1]->pb = pb_avg;
        bp->pixel_block[2]->pb = pb_avg;
        bp->pixel_block[3]->pb = pb_avg;


        bp->pixel_block[0]->pr = pr_avg;
        bp->pixel_block[1]->pr = pr_avg;
        bp->pixel_block[2]->pr = pr_avg;
        bp->pixel_block[3]->pr = pr_avg;




}




Pnm_ppm write_to_image(UArray2_T videopixels, float denominator)
{

        fprintf(stderr, "%s\n", "write_to_image" );
        const float RGBy = 1.0;

const float Rb = 0.0;
const float Rr = 1.402;

const float Gb = -0.344136;
const float Gr = -0.714136;

const float Bb = 1.772;
const float Br = 0.0;

        int width = UArray2_width(videopixels);
        int height = UArray2_height(videopixels);
        UArray2_T rgbpix = UArray2_new(width, height, sizeof(struct Pnm_rgb));
        float y, pb, pr;

        for (int row = 0; row < width; row++){
                for (int col = 0; col < height; col++){
                        Vpixel curr = (Vpixel)UArray2_at(videopixels, row, col);
                        Pnm_rgb pix = (Pnm_rgb)UArray2_at(rgbpix, row, col);
                        y = curr->y;
                        pb = curr->pb;
                        pr = curr->pr; 

                        float red = (RGBy*y + Rb*pb + Rr*pr);
                        float green = (RGBy*y + Gb*pb + Gr*pr);
                        float blue = (RGBy*y + Bb*pb + Br*pr);
                        if (red > 1){
                            red = 1.0;
                        }
                        if (green > 1){
                            green = 1.0;
                        }
                        if (blue > 1){
                            blue = 1.0;
                        }
                        if (red < -1){
                            red = -1.0;
                        }
                        if (green < -1){
                            green = -1.0;
                        }
                        if (blue < -1){
                            blue = -1.0;
                        }


                        pix->red =   denominator*red;
                        pix->green = denominator*green;
                        pix->blue = denominator*blue;

                       
                        if(pix->red > denominator)
                            pix->red = denominator;
                        if(pix->green > denominator)
                            pix->green = denominator;
                        if(pix->blue > denominator)
                            pix->blue = denominator;

                        // fprintf(stderr,"y: %f, pb: %f, pr: %f\n", y, pb, pr);
                        // fprintf(stderr, "r: %d, g: %d, b: %d\n", pix->red, pix->green, pix->blue);

                }
        }
        Pnm_ppm pixmap = malloc(sizeof(struct Pnm_ppm));
        pixmap->width = width;
        pixmap->height = height;
        pixmap->denominator = denominator;
        pixmap->pixels = rgbpix;
        pixmap->methods = uarray2_methods_plain;

        //pixmap = { .width = width, .height = height, .denominator = denominator, .pixels = rgbpix, .methods = uarray2_methods_plain};
        return pixmap;
}

UArray2_T write_to_video (UArray2_T blocks){

         fprintf(stderr, "%s\n", "write_to_video" );
        int width = UArray2_width(blocks)*2;
        int height = UArray2_height(blocks)*2;
        UArray2_T videopixels = UArray2_new(width, height, sizeof(struct Vpixel));

        for (int row = 0; row < width/2; row++){
                for (int col = 0; col < height/2; col++){
                        Block b = (Block)UArray2_at(blocks, row, col);

                       
                        // Vpixel v2 =  (Vpixel) UArray2_at(videopixels, row*2, col*2+1);
                        // Vpixel v3 = (Vpixel) UArray2_at(videopixels, row*2+1, col*2);
                        // Vpixel v4 =  (Vpixel) UArray2_at(videopixels, row*2+1, col*2+1);


                       // fprintf(stderr, "%f\n", b->pixel_block[0]->y);
                        

                        *(Vpixel)UArray2_at(videopixels, row*2, col*2) =  * b->pixel_block[0];
                         *(Vpixel)UArray2_at(videopixels, row*2, col*2+1) =  *b->pixel_block[1];
                          *(Vpixel)UArray2_at(videopixels, row*2+1, col*2) =  *b->pixel_block[2];
                           *(Vpixel)UArray2_at(videopixels, row*2+1, col*2+1) =  *b->pixel_block[3];
                        // v3 =  b->pixel_block[2];
                        // v4 =  b->pixel_block[3];


                }
        }

        return videopixels;


}



//Pnm_rgb_float video_to_rgb_float(UArray2_T pixel_video);