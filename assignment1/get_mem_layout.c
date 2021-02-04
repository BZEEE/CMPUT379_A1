
#include "get_mem_layout.h"

jmp_buf buffer;

void handleMemoryAccessError(int sig) {
    // pass back the value of indicating that an error occurred when returning to the set jump
    longjmp(buffer, 1);
};

int get_mem_layout(struct memregion *regions, unsigned int size) {
    unsigned int memoryStart = 0x00000000;
    unsigned int memoryEnd = 0xFFFFFFFF;
    // unsigned int pageSize = 4096;
    unsigned int ratio = memoryEnd / USER_PAGE_SIZE;

    unsigned int pageCounter = 0;
    int count = 1; 
    unsigned char previousMemRegionMode = 15; // set to som mode that doesnt exist, just for initialization purposes
    
    // loop over all pages n memory and try to acces the the first byte in each page
    bool firstMemBlockAssign = false;
    while (pageCounter < ratio) {
        (void) signal(SIGSEGV, handleMemoryAccessError); // handle read and write memory errors, set the signal at every beginning of the loop
        (void) signal(SIGBUS, handleMemoryAccessError);  // handle Bus Errors, accessing memory that has not been physically mapped

        // keep track of jump result if a handler returns a value
        int jumpResult;

        // pointer to that specific memory address
        unsigned int *p = (unsigned int *) memoryStart;
        
        unsigned char memRegionMode;
        char readData;
        // a jump result return value of 1 will indicate a read/write error was thrown
        jumpResult = setjmp(buffer); // returns 0 automatically when initialized, therefore no error was thrown
        // attempt to read memory, throws signal error if we cant
        if (jumpResult == 0) { 
            memRegionMode = MEM_NO;
            readData = p[0];
        }
        
        // attempt to write same value back to same spot in memory, throws signal error if we cant
        if (jumpResult == 0) {
            memRegionMode = MEM_RO;
            p[0] = readData;
        }

        // we were able to successfully read and write to that memory region, then the region is both readable and writable
        if (jumpResult == 0) {
            memRegionMode = MEM_RW;
        }

        // Edge case, if the mem region is the first one then we set previousMemRegionMode
        if (count == 1 && !firstMemBlockAssign) {
            regions[count-1].mode = memRegionMode;
            previousMemRegionMode = memRegionMode;
            firstMemBlockAssign = true;
        }

        // check if current mem region mode is the same as previous mem region mode
        // if it isnt then we end the previous mem region struct
        // and start a new mem region struct
        if (memRegionMode != previousMemRegionMode) {
            // only the first (size) regions will be added to the mem region struct array
            if (count < size) {
                // close off the previous mem region
                regions[count-1].to = (void *) (memoryStart - USER_PAGE_SIZE);
                // start the next region in memory
                regions[count].from = (void *) memoryStart;
                // printf("mode =  %u\n", regions[count-1].mode);
                regions[count].mode = memRegionMode;
            } else if (count == size) {
                // close of the section if it ends before 
                regions[count-1].to = (void *) (memoryStart - USER_PAGE_SIZE);
            }
            // found a new region so we increase the count and set the new previous mem region to compare the next set of memory after this
            count++;
            previousMemRegionMode = memRegionMode;
        }
        // go to next page
        memoryStart = memoryStart + USER_PAGE_SIZE;
        pageCounter++;
    }

    // edges case, count never reached size, therefore we close off the range of the last section
    if (count <= size) {
        regions[count-1].to = (void *) (0xFFFFFFFF); // address of last page in previous mem region
    }
    //  returns the actual number of memory regions located in the process's address space, even if it is larger than input paramter (size) 
    return count;

}