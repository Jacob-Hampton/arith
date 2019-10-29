#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <bitpack.h>

void printBits(size_t const size, void const * const ptr);

int main()
{

        uint64_t word = 0x12345678;
        // printBits(sizeof(uint64_t), &word );

        uint64_t value = 5;

        printBits (sizeof(int64_t), &value );

        

        if(Bitpack_fitsu(value, 3 )){

                printf("%s\n", "FITS" );

        }
        else{
                 printf("%s\n", " DOESNT FIT" );
        }


       // word = Bitpack_news(word, 4, 10, value);

        printBits(sizeof(uint64_t), &word );

        // int64_t extracted = Bitpack_gets(word, 4, 10);
        // printBits (sizeof(int64_t), &extracted );

        // printf("%li\n", extracted );



    //    printf("%li\n", Bitpack_newu(0x12345678d, 8, 0, 0x48 ));
}


//assumes little endian
void printBits(size_t const size, void const * const ptr)
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