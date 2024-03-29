#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

#define MEMLENGTH 512
#define HEADERSIZE 8
#define startMem (Metadata*) &memory[0]
#define endMem (Metadata*) &memory[MEMLENGTH]

static double memory[MEMLENGTH];
int first = 1;

size_t roundSize (size_t size) {
    return (size + (HEADERSIZE-1)) & ~(HEADERSIZE-1);
}

void initialize () {
    Metadata *meta = startMem;
    *meta = (Metadata) { .free = 1, .chunkSize = MEMLENGTH*8-HEADERSIZE };
}

int coalesce(Metadata *meta) {
    /*Metadata *next = meta + 1 + ((meta->chunkSize)/HEADERSIZE);
    Metadata *cur = meta;
    Metadata *temp = meta;
    int size = 0;
    while (!(next >= endMem) || next->free) {*/
    // we first check the next block is viable to coalesce
    // if not then we simply return the size of the chunk + HEADERSIZE
    // if we can coalesce, then we update size and repeat on next
    // there will only ever be 3 free chunks next to each other so we do not need to check rest
    //printf("start coalesce");
    int size = 0;
    Metadata *cur = meta;
    Metadata *next = meta+1+((meta->chunkSize)/HEADERSIZE);
    if (next >= endMem || !(next->free)) {
        return HEADERSIZE + meta->chunkSize;
    } else { 
        size += HEADERSIZE + meta->chunkSize;
        cur = next;
    }
    next = next+1+((next->chunkSize)/HEADERSIZE);
    if (next >= endMem || !(next->free)) {
        return size + HEADERSIZE + cur->chunkSize;
    } else { 
        size += HEADERSIZE + cur->chunkSize;
        cur = next;
        return size + cur->chunkSize + HEADERSIZE;
    }
    return size;
}

void *mymalloc (size_t size, char *file, int line) {
    //printf("start malloc");
    if (size%HEADERSIZE) {
        size = roundSize(size);
    }
    
    if (size == 0) {
        printf("malloc: size must be > 0\n");
        return NULL;
    }

    if (first) {
        initialize();
        first = 0;
    }
    
    // for each chunk that is either not free or not big enough for the payload
    // we add the current chunk to our meta pointer to go to the next one
    // we will stop at a viable chunk or at the end of memory
    Metadata *meta = startMem;

    for (; meta < endMem; meta += ((meta->chunkSize) / HEADERSIZE) + 1) {
        if ((meta->free) && meta->chunkSize >= size) {
            break;
        }
    }

    // no free memory
    if (meta >= endMem) {
        printf("malloc: no availible memory\n");
        return NULL;
    }

    // set chunk to allocated
    meta->free = 0;

    // if big enough to split
    // will split into 2 chunks, first will have given size, other will be remainder
    if (meta->chunkSize > size + HEADERSIZE) {
        int old = meta->chunkSize;
        meta->chunkSize = size;
        Metadata *newHeader = 1+meta+((meta->chunkSize)/HEADERSIZE);
        *newHeader = (Metadata) { .free = 1, .chunkSize = old - size - HEADERSIZE };
    }
    return meta + 1;
}

void myfree (void *ptr, char *file, int line) {
    //printf("start free");
    // checks if ptr is in memory
    if (ptr < (void*) startMem || ptr >= (void*) endMem) {
        printf("free: address out of bounds (%s:%d)\n", file, line);
        return;
    }
    
    // Iteratively searches for ptr
    Metadata *meta = startMem;
    Metadata *lag = startMem;
    while (meta < endMem) {
        if (meta + 1 == ptr) {
            break;
        }
        lag = meta;
        meta += 1 + (meta->chunkSize)/HEADERSIZE;
    }
    if (meta >= endMem) {
        printf("free: address not at the start of a memory chunk (%s:%d)\n", file, line);
        return;
    }
    if (meta->free){
        printf("free: double free (%s:%d)\n", file, line);
        return;
    }
    
    // Set chunk to free
    meta->free = 1;
    
    // Coalesce chunks if needed
    // Subtract HEADERSIZE because coalesce() will always include HEADERSIZE length in the returned value
    if (lag->free) {
        lag->chunkSize = coalesce(lag) - HEADERSIZE;
    }
    else {
        meta->chunkSize = coalesce(meta) - HEADERSIZE;
    }
}