// Implement Malloc
// - No cheating (try to avoid looking at the actual source library for malloc)
// - Read through man pages of brk and sbrk
// LOL --> "Avoid  using brk() and sbrk(): the malloc(3) memory allocation package is the portable and comfortable way of allocating memory."

/**

HISTORY
V0.1     | simple allocation, returned pointer with sbrk. No idea how to free the memory.
V0.2     | Implemented metadata, allowing program to track allocation ... but still not sure how to return memory to OS.
V0.21    | Read about and added pointer arithmetic -> automatic type size scaling! Super cool.
V0.3     | Added linked list structure for managing multiple blocks of memory.
V0.4     | Added simple testing and output and print memory function.

 */

#include <unistd.h>
#include <stdbool.h>
#include <stdio.h> 
#include <string.h> 

typedef struct archMetaData {
    size_t size;
    bool free;
    struct archMetaData *next; // Pointer to next block of memory.
} archMetaData;

static archMetaData *head = NULL; // Head of linked list of mem blocks.


void *joshGive(size_t size) { 

    // Used to traverse available memory blocksAssignments for 
    archMetaData *current = head;
    archMetaData *previous = NULL;

    while (current) {
        if (current->free && current->size >= size) {
            current->free = false;
            return (void*)(current + 1); // Return pointer to user data area.
        }
        previous = current;
        current = current->next; // Standard list traversal to find free memory block.
    }
    
    // If return was not hit above, need to request more memory from the OS -> move the program break up for new metadata + userdata.
    archMetaData *memBlock = sbrk(sizeof(archMetaData) + size); // Assign enough space for metadata AND for user-data.
    
    // Init props
    memBlock->size = size;
    memBlock->free = false;
    memBlock->next = NULL;

    // Add the new block to the end of the list
    if (head == NULL) {
        head = memBlock;
    } else {
        previous->next = memBlock;
    }

    // return (void*)((char*)memBlock + sizeof(archMetaData)); 
    return (void*)(memBlock + 1); // Return void pointer to user area that is just in front of the metadata area.

}

void joshTake(void *memPointer) {
    
    // Using pointer arithmetic to go back one archMetaData length.
    archMetaData *memBlock = ((archMetaData*)memPointer) - 1;
    
    // Mark as free
    memBlock->free = true;

    // !! Memory is still not returned to the OS. Though from what I am understanding it doesn't necessarily need to be (not optimal to do this??)

}

void printMemoryMap() {
    archMetaData *current = head;
    int i = 0;
    
    printf("\n--- MEMORY MAP ---\n");
    while (current) {
        printf("Block %d: address=%p, size=%zu, free=%s\n", 
               i++, 
               (void*)(current + 1),
               current->size, 
               current->free ? "true" : "false");
        current = current->next;
    }
    printf("-----------------\n\n");
}

int main() {
    
    printf("=== Testing Type Allocations ===\n");
    
    // Allocate different types of memory
    int *nums = (int*)joshGive(3 * sizeof(int));
    char *str = (char*)joshGive(20);
    double *dbl = (double*)joshGive(sizeof(double));
    
    // Use the memory
    nums[0] = 100;
    nums[1] = 200;
    nums[2] = 300;
    
    strcpy(str, "Hello mario");

    *dbl = 1.111111;
    
    // Print values
    printf("nums: %d, %d, %d\n", nums[0], nums[1], nums[2]);
    printf("str: %s\n", str);
    printf("dbl: %f\n", *dbl);
    
    // Show memory map
    printMemoryMap();
    
    // Free in different order to test the free list
    joshTake(nums);
    joshTake(dbl);
    joshTake(str);
    
    printf("All memory freed\n");
    printMemoryMap();

    return 0;
}