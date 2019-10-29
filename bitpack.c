#include "bitpack.h"
#include <stdio.h>
#include <assert.h>
#include "except.h"


void check_inputs(unsigned width, unsigned lsb);
 Except_T Bitpack_Overflow = {"Overflow packing bits"};



void print_Bits(size_t const size, void const * const ptr);

bool Bitpack_fitsu(uint64_t n, unsigned width){


        //print_Bits(sizeof(uint64_t), &n);

        check_inputs(width, 0);

         if(width == 64){
                return true;
        }

        if(width == 0){
                return n == 0;
        }


        uint64_t one = 1;
        uint64_t mask = (one<<(width));

        //  print_Bits(sizeof(uint64_t), &mask);

          //mask = mask << width;

         // print_Bits(sizeof(uint64_t), &mask);
          mask = ~(mask -1);



       //  print_Bits(sizeof(uint64_t), &mask);

        
         //print_Bits(sizeof(uint64_t), &anded);
         return !(mask & n);

}

bool Bitpack_fitss( int64_t n, unsigned width){

        check_inputs(width, 0);


         if(width == 64){
                return true;
        }

         if(width == 0){
                return n == 0;
        }


        if(n >= 0){
                return Bitpack_fitsu(n, width);
        }
        else{
                return Bitpack_fitsu(n*-2, width);
        }

}

uint64_t Bitpack_getu(uint64_t word, unsigned width, unsigned lsb){

        check_inputs(width, lsb);

        return (uint64_t) (word >> lsb  & ((1<<width)-1));
}  


 int64_t Bitpack_gets(uint64_t word, unsigned width, unsigned lsb){

       check_inputs(width, lsb);

       uint64_t extracted_word = ( word >> lsb  & ((1<<width)-1));

       if(extracted_word & 1<<(width-1)){
       // printf("%s\n", "NEGATIVE" );

        uint64_t mask = ~((1<<width) -1);

        return extracted_word | mask;
       }


        return  extracted_word;

 }



uint64_t Bitpack_newu(uint64_t word, unsigned width, unsigned lsb, uint64_t value){


        check_inputs(width, lsb);

           if(!Bitpack_fitsu(value, width)){

          RAISE(Bitpack_Overflow);

           }

         uint64_t masked =  ( ((1<<width)-1) << lsb);

        word = word & ~masked;

        uint64_t aligned_value = (value & ((1<<width)-1)) << lsb;



return word | aligned_value;

}


uint64_t Bitpack_news(uint64_t word, unsigned width, unsigned lsb,  int64_t value){

        check_inputs(width, lsb);

        if(!Bitpack_fitss(value, width)){

          RAISE(Bitpack_Overflow);

        }


        uint64_t masked =  ( ((1<<width)-1) << lsb);

        word = word &  ~masked;

        uint64_t aligned_value = (value & ((1<<width)-1)) << lsb;



        return word | aligned_value;


}

//assumes little endian
void print_Bits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i=size-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}


void check_inputs(unsigned width, unsigned lsb){

        assert(width <= 64);

        assert(width+lsb <= 64);


}
