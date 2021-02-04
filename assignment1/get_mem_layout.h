
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h>
#include <stdbool.h>

#define MEM_RW 0
#define MEM_RO 1
#define MEM_NO 2

#ifndef USER_PAGE_SIZE
const unsigned int USER_PAGE_SIZE = 4096;
#endif


struct memregion {
 void *from;
 void *to;
 unsigned char mode; /* MEM_RW, or MEM_RO, or MEM_NO */
};

void handleMemoryAccessError(int sig);
int get_mem_layout(struct memregion *regions, unsigned int size);
