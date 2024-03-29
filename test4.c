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

// coalesce works

int main(int argc, char **argv) {
    double* i = malloc(sizeof(int));
    double* j = malloc(sizeof(int));
    if (i+1+HEADERSIZE/sizeof(double) == j) {
        printf("i and j are adjacent\n");
    }
    free(i);
    free(j);
    void* k = malloc(16);
    if (k == i) {
        printf("r and j point to same address\n");
    }
    return EXIT_SUCCESS;
}