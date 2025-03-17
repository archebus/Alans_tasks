// Implement Malloc
// - No cheating (try to avoid looking at the actual source library for malloc)
// - Read through man pages of brk and sbrk
// LOL --> "Avoid  using brk() and sbrk(): the malloc(3) memory allocation package is the portable and comfortable way of allocating memory."

/**

HISTORY
V1.0 | simple allocation, returned pointer with sbrk. No idea how to free the memory.
V2.0 | Implemented metadata, allowing program to track allocation ... but still not sure how to return memory to OS.
V2.1 | Read about pointer arithmetic 

 */

#include <unistd.h>
#include <stdbool.h>

typedef struct archMetaData {
    size_t size;
    bool free;
} archMetaData;



void *joshGive(size_t size) { 

    archMetaData *memBlock = sbrk(sizeof(archMetaData) + size); // Assign enough space for metadata AND for user-data.

    memBlock->size = size;
    memBlock->free = false;

    // return (void*)((char*)memBlock + sizeof(archMetaData)); 
    return (void*)(memBlock + 1); // Return void pointer to user area that is just in front of the metadata area.

}

void joshTake(void *memPointer) {

    if (memPointer == NULL) {
        return; // Nothing to free
    }
    
    // Using pointer arithmetic to go back one archMetaData structure
    archMetaData *memBlock = ((archMetaData*)memPointer) - 1;
    
    // Mark as free
    memBlock->free = true;

}

int main() {
    // Allocate space for 5 integers
    int *numbers = (int*)joshGive(5 * sizeof(int));
    
    // Use the allocated memory
    for (int i = 0; i < 5; i++) {
        numbers[i] = i * 10;
    }
    
    // Print the values to verify
    for (int i = 0; i < 5; i++) {
        printf("numbers[%d] = %d\n", i, numbers[i]);
    }
    
    // Should probably have a function to free the memory here....
    
    return 0;
}