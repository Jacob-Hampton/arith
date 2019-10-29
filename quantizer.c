#include "quantizer.h"
#include <assert.h>

const float BCD_DIFF = 0.02f;

int64_t bcd_quantize(float num)
{
        int64_t answer;
        if (num > 0.3){
                num = 0.3;
        }
        else if (num < -0.3){
                num = -0.3;
        }

        num /= BCD_DIFF;
       // printf("num = %f\n", num);
        answer = (int64_t)num;
        return answer;

}
// {-15, -14, -13,...0,...,13, 14, 15}

float bcd_unquantize(int64_t num)
{
        assert((num < 16) && (num > -16));
        float answer = num * BCD_DIFF;
        return answer;
}

uint64_t p_quantize(float num)
{
        return Arith40_index_of_chroma(num);
}

float p_unquantize(uint64_t num)
{
        return Arith40_chroma_of_index(num);
}

int quantize_rgb(float rgb, int denominator)
{
        (void)rgb;
        (void)denominator;
        return 0;
}
