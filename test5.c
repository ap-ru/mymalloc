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

// Calling free() with an address not obtained from malloc()

int main(int argc, char **argv) {
    int i = 3;
    free(&i);
    return EXIT_SUCCESS;
}