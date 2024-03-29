memgrind: memgrind.c mymalloc.c mymalloc.h
	$(CC) $(CFLAGS) $^ -o $@

all: test1 test2 test3 test4 test5

CC = gcc
CFLAGS = -g -Wall -std=c99 -fsanitize=address,undefined

test1: test1.c mymalloc.c mymalloc.h
	$(CC) $(CFLAGS) $^ -o $@

test2: test2.c mymalloc.c mymalloc.h
	$(CC) $(CFLAGS) $^ -o $@

test3: test3.c mymalloc.c mymalloc.h
	$(CC) $(CFLAGS) $^ -o $@

test4: test4.c mymalloc.c mymalloc.h
	$(CC) $(CFLAGS) $^ -o $@
	
test5: test5.c mymalloc.c mymalloc.h
	$(CC) $(CFLAGS) $^ -o $@
