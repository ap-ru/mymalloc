#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


// Compile with -DREALMALLOC to use the real malloc() instead of mymalloc()
#ifndef REALMALLOC
#include "mymalloc.h"
#endif

#define MEMSIZE 4096
#define HEADERSIZE 8
#define OBJECTS 4
#define OBJSIZE (MEMSIZE / OBJECTS - HEADERSIZE)

// malloc() reserves unallocated memory.
// free() deallocates memory

int main(int argc, char **argv) {
    int* i = malloc(sizeof(int));
    free(i);
    int* j = malloc(sizeof(int));
    
    return EXIT_SUCCESS;
}