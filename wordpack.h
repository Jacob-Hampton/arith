#ifndef WORDPACK
#define WORDPACK

#include "datastructs.h"

void pack_block(Block  bp);


void unpack_block( Block  bp);

uint64_t get_bite(uint64_t word, int i);

uint64_t put_bite(uint64_t word, uint64_t byte, int i);


#endif