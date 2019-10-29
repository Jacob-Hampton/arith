
#include "wordpack.h"
#include "bitpack.h"





void pack_block(Block  bp){

     uint64_t word = 0;
     
     //printBits(sizeof(uint64_t), &word);

     word = Bitpack_newu(word, 9, 23, bp->a);

     // printBits(sizeof(uint64_t), &(bp->a));     

     // printBits(sizeof(uint64_t), &word);

     word = Bitpack_news(word, 5, 18, bp->b);

     // printBits(sizeof(uint64_t), &(bp->b)); 

     // printBits(sizeof(uint64_t), &word);

     word = Bitpack_news(word, 5, 13, bp->c);


     // printBits(sizeof(uint64_t), &(bp->c)); 

     // printBits(sizeof(uint64_t), &word);

     word = Bitpack_news(word, 5, 8, bp->d);

     // printBits(sizeof(uint64_t), &(bp->d)); 

     // printBits(sizeof(uint64_t), &word);

      

     word = Bitpack_newu(word, 4, 4, bp->pb_avg);

     // printBits(sizeof(uint64_t), &(bp->pb_avg));

     // printBits(sizeof(uint64_t), &word);

     word = Bitpack_newu(word, 4, 0, bp->pr_avg);


     // printBits(sizeof(uint64_t), &(bp->pr_avg));

     // printBits(sizeof(uint64_t), &word);


    // fprintf(stderr, "Unpacked a: %lu b: %li c: %li d: %li \n", bp->a, bp->b,bp->c,bp->d);
     

     bp->word = word;


}

uint64_t get_bite(uint64_t word, int i){

    return Bitpack_getu(word, 8, 8*i);
}

uint64_t put_bite(uint64_t word, uint64_t byte, int i){

    return Bitpack_newu(word, 8, 8*i, byte);
}



void unpack_block( Block  bp){

        bp->a = Bitpack_getu(bp->word, 9 , 23);

        bp->b = Bitpack_gets(bp->word, 5 , 18);

        bp->c = Bitpack_gets(bp->word, 5 , 13);

        bp->d = Bitpack_gets(bp->word, 5 , 8);

        bp->pb_avg = Bitpack_getu(bp->word, 4 , 4);

        bp->pr_avg = Bitpack_getu(bp->word, 4 , 0);


       //  fprintf(stderr, "Unpacked a: %lu b: %li c: %li d: %li \n", bp->a, bp->b,bp->c,bp->d);

}



