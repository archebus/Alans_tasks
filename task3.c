// Implement Malloc
// - No cheating (try to avoid looking at the actual source library for malloc)
// - Read through man pages of brk and sbrk
// LOL --> "Avoid  using brk() and sbrk(): the malloc(3) memory allocation package is the portable and comfortable way of allocating memory."

/**
Reading through how memory is actually allocation I can see the below structure when a program is initially loaded into memory:

Lower addresses
+----------------+
| Text (code)    |
+----------------+
| Data           |
+----------------+
| BSS            |
+----------------+
| Heap           | <- Initially small or empty
|                |
+----------------+ <- Program break (brk point) <---- this is what is moved when calling sbrk.
| Unused memory  |
|                |
+----------------+
| Stack          | <- Grows downward from high addresses
+----------------+
Higher addresses

 */

#include <unistd.h>

void *archGive(size_t size) {

    void *memPointer = sbrk(size);

    return memPointer;

}

void archTakeAway(void *ptr) {

    // How do I free ....>>!>!>!>!>
    (void)ptr;
}

int main() {
    // Allocate space for 5 integers
    int *numbers = (int*)archGive(5 * sizeof(int));
    
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