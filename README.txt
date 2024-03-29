ap2040 - Anish Patel / hm569 - Haris Malik 

Systems Programming Project 1: My Little Malloc

This library uses improved versions of the C standard library functions such as malloc() and free(). These versions check for errors that cannot
be checked using the standard library. 

To run the program, call:

make 
./memgrind

memgrind.c serves as performance test for mymalloc. 

To use the improved versions of these standard C library functions, replace all instances of "memgrind" in Makefile with the name of
the .c file that you would like to use mymalloc for.

The following headers are needed in order for these functions to run,  and should be included at the top each code file:
  #include <stdlib.h>
  THEN use #include "mymalloc.h" afterwards
  <stdlib.h> must be implemented before mymalloc.h or else the function will not run.


Heap size is 4096 bytes. Metadata size is 8 bytes.  To change the
heap size, go to mymalloc.c and change the value of MEMLENGTH to whatever you would like.

Error Handling:

My Little Malloc is able to handle 3 error instances that are not covered by StdLib functions. 

    1. When free() is called on an address that was not returned by malloc()

    2. When free() is called on an address of a pointer that is not at the start of its memory block

    3. When free() is called on an address that has already been freed


Performance Test 4: This function tests if objects can be freed when there is no free blocks next to
                    them, when 1 block is next to them, and when both blocks are free next to them
    
    1. Allocates 120 objects on heap.
    2. Frees every third individual memory block (starting from 0)
    3. Frees every third individual memory block (starting from 1)
    4. Frees every third individual memory block (starting from 2)

Performance Test 5: This function tests to see if data larger than 1 (int) can be malloc'd and freed
    
    1. Allocates 1 int
    2. Frees the int


Test Plan:

Compile all test programs using make all 
Run them using
./testNUMBER

Step by step description of each test:

Test 1:

This tests that calling free() on a freed memory block will print an error message.
1. Allocates memory of pointer i using the malloc function. 
2. Frees i
3. Frees i again
4. Will output an error as it is not possible to free a free'd pointer

This function tests to see if double free is detected as an error

Test 2:

1. Allocates memory using the malloc function. 
2. Frees this memory
3. Re-malloc() the same memory

This function tests to see free and malloc are working as intended

Test 3: 

1. Allocates a set of objects using malloc().
2. Populates each object with a distinct sequence of bytes.
3. Iterates through the objects again to confirm that each one contains the expected byte sequence.
4. If all byte sequences are accurate, it indicates that the memory blocks do not overlap.

This tests whether adjacent memory blocks allocated by malloc() are non-overlapping

Test 4: 

1. Allocates memory for two double variables i and y using the malloc function.
2. Checks if i and j are adjacent in memory by comparing i+1 with j.
3. Frees the memory allocated for i and j using the free function.
4. Allocates memory for a new variable k using  malloc . It then checks if k and i point to the same memory address by comparing k with i. 
5. Frees the memory allocated for z using the free function and returns

This tests to see if adjacent blocks converge once they are freed

Test 5: 

1. Allocates memory not using mymalloc - declares int i
2. Attempts to free i
3. Returns an error as free can only be used on memory allocated by mymalloc

This function tests to see that an error message will print when freeing memory that was not allocated by malloc

