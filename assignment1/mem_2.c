
#include "mem_2.h"

int fib(int n) { 
    if (n <= 1) 
        return n; 
    return fib(n-1) + fib(n-2); 
} 

int min(int a, int b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}

void printMemRegions(struct memregion *regions, unsigned int size, int actualSize) {
    int loopSize = min(size, actualSize); // return the minimum of the size we expected and the actual size
    for (int i = 0; i < loopSize; i++) {
        if (regions[i].mode == 0) {
            printf("0x%08X-0x%08X RW\n", (unsigned int) regions[i].from, (unsigned int) regions[i].to);
        } else if (regions[i].mode == 1) {
            printf("0x%08X-0x%08X RO\n", (unsigned int) regions[i].from, (unsigned int) regions[i].to);
        } else if (regions[i].mode == 2) {
            printf("0x%08X-0x%08X NO\n", (unsigned int) regions[i].from, (unsigned int) regions[i].to);
        }
    }
}

int main() {

    int size = 30;
    int actualSize;

    // initialize struct array pointer, and set first mem region
    struct memregion *regions = (struct memregion *) calloc(size, sizeof(struct memregion));
    regions[0].from = (void*) 0x00000000;
    regions[0].to = NULL; // set mode intially to RW
    regions[0].mode = 10; // set mode to one that doesnt exist

    // before driver code manipulation
    printf("\n--------------Before Drive Code Added-----------------\n");
    actualSize = get_mem_layout(regions, size);
    printf("\npage size = %d\n", USER_PAGE_SIZE);
    printf("Estimated Region Size: %d\n", size);
    printf("Actual Region Size: %d\n", actualSize);
    printMemRegions(regions, size, actualSize);
    printf("------------------------------------------------------\n");

    // call recursive function for driver 2 program
    fib(30);

    struct memregion *regions2 = (struct memregion *) calloc(size, sizeof(struct memregion));
    regions2[0].from = (void*) 0x00000000;
    regions2[0].to = NULL; // set mode intially to RW
    regions2[0].mode = 10; // set mode to one that doesnt exist

    // after driver code manipulation
    printf("\n--------------After Drive Code Added-----------------\n");
    actualSize = get_mem_layout(regions2, size);
    printf("\npage size = %d\n", USER_PAGE_SIZE);
    printf("Estimated Region Size: %d\n", size);
    printf("Actual Region Size: %d\n", actualSize);
    printMemRegions(regions2, size, actualSize);
    printf("------------------------------------------------------\n");

    free(regions);
    free(regions2);
    return 0;
}

