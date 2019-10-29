#ifndef QUANTIZER
#define QUANTIZER

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <arith40.h>


int64_t bcd_quantize(float num);
//Takes a float, quantizes it, and returns a 5 bit signed integer
float bcd_unquantize(int64_t num);
//Takes a signed integer, unquantizes it, and returns a float


uint64_t a_quantize(float num);
//Takes a float, quantizes it, and returns a 9 bit unsigned integer
float a_unquantize(uint64_t num);
//Takes an unsiged integer, unquantizes it, and returns a float

uint64_t p_quantize(float num);
//Calls the Arith40_index_of_chroma function on float. Returns 4 bit value
float p_unquantize(uint64_t num);
//Calls the Arith40_chroma_of_index function on unsigned integer

int quantize_rgb(float rgb, int denominator);
//Takes an r/g/b value as a float and the denominator of the image and quantizes the
//number depending on the denominator


#endif
